extern "C" 
{
#include "spice-widget.h"
#include "spice-widget-priv.h"
#include <channel-display.h>
}

#include "spiceqt.h"
#include <QClipboard>
#include <QApplication>
#include <QByteArray>
#include <QString>

G_DEFINE_TYPE(SpiceDisplay, spice_display, SPICE_TYPE_CHANNEL);

//extern SpiceDisplay * global_display;
static void disconnect_main(SpiceDisplay *display);
static void disconnect_display(SpiceDisplay *display);
static void channel_new(SpiceSession *s, SpiceChannel *channel, gpointer data);
static void channel_destroy(SpiceSession *s, SpiceChannel *channel, gpointer data);
static void callbackInvalidate(SpiceDisplayPrivate *d, gint x, gint y, gint w, gint h);
static void callbackSettingsChanged(SpiceDisplay *display, gint width, gint height, gint bpp);
static void sync_keyboard_lock_modifiers(SpiceDisplay *display, guint32 modifiers);

/* ---------------------------------------------------------------- */

static void callbackInvalidate(SpiceDisplayPrivate *d, gint x, gint y, gint w, gint h)
{
//    qDebug() << "callbackInvalidate: Checking if cursor is initialized...";
    if (!d->cursor_init_done) {
        qDebug() << "Error: Cursor not initialized!";
        return;
    }

    uchar *img = static_cast<uchar*>(d->data);
    //SpiceQt::getSpice()->updateImage(img, x, y, w, h);
    d->spiceQtInstance->updateImage(img, x, y, w, h);
}

// OpenGL 绘图函数
static void draw_gl(SpiceDisplay *display) {
    SpiceDisplayChannel *channel = SPICE_DISPLAY_CHANNEL(display);
    const SpiceGlScanout *scanout = spice_display_channel_get_gl_scanout(channel);
    if (scanout) {
        GLuint texture_id = scanout->texture_id;  // 假设 id 是正确的成员变量名
        glBindTexture(GL_TEXTURE_2D, texture_id);
        
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
        glEnd();
        
        spice_display_gl_draw_done(channel);
    }
}

static void callbackSettingsChanged(SpiceDisplay *display, gint width, gint height, gint bpp)
{
    //SpiceQt::getSpice()->settingsChanged(width, height, bpp);

    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
//    SpiceDisplayPrivate *d = static_cast<SpiceDisplayPrivate*>(instance);
    if (d->spiceQtInstance) {
        d->spiceQtInstance->settingsChanged(width, height, bpp);
    }
}

static void spice_display_dispose(GObject *obj)
{
    SpiceDisplay *display = SPICE_DISPLAY(obj);
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);

    SPICE_DEBUG("spice display dispose");

    disconnect_main(display);
    disconnect_display(display);
    //disconnect_cursor(display);

    //if (d->clipboard) {
    //    g_signal_handlers_disconnect_by_func(d->clipboard, G_CALLBACK(clipboard_owner_change),
    //                                         display);
    //    d->clipboard = NULL;
    //}

    //if (d->clipboard_primary) {
    //    g_signal_handlers_disconnect_by_func(d->clipboard_primary, G_CALLBACK(clipboard_owner_change),
    //                                         display);
    //    d->clipboard_primary = NULL;
    //}

/*
    void *a = static_cast<void*>(channel_new);
    void *b = static_cast<void*>(channel_destroy);
    if (d->session) {
        g_signal_handlers_disconnect_by_func(d->session, G_CALLBACK(a),
                                             display);
        g_signal_handlers_disconnect_by_func(d->session, G_CALLBACK(b),
                                             display);
        g_object_unref(d->session);
        d->session = NULL;
    }
*/
}


static void spice_display_finalize(GObject *obj)
{
    SPICE_DEBUG("Finalize spice display");
    G_OBJECT_CLASS(spice_display_parent_class)->finalize(obj);
}


static void spice_display_class_init(SpiceDisplayClass *klass)
{
    g_type_class_add_private(klass, sizeof(SpiceDisplayPrivate));
}

static void spice_display_init(SpiceDisplay *display)
{
    //global_display = display;
    SpiceDisplayPrivate *d;

    d = display->priv = SPICE_DISPLAY_GET_PRIVATE(display);
    memset(d, 0, sizeof(*d));
    d->have_mitshm = TRUE;
    d->mouse_last_x = -1;
    d->mouse_last_y = -1;

    d->cursor_init_done = FALSE;  // 初始化 cursor_init_done
    d->cursor_width = 0;          // 初始化 cursor_width
    d->cursor_height = 0;         // 初始化 cursor_height
    d->cursor_hot_x = 0;          // 初始化 cursor_hot_x
    d->cursor_hot_y = 0;          // 初始化 cursor_hot_y
    d->cursor_x = 0;              // 初始化 cursor_x
    d->cursor_y = 0;              // 初始化 cursor_y
    d->cursor_visible = FALSE;    // 初始化 cursor_visible
    d->cursor_data = NULL;        // 初始化 cursor_data
//    SpiceQt::getSpice()->initializeCursor(d);
}


gint get_display_id(SpiceDisplay *display)
{
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);

    /* supported monitor_id only with display channel #0 */
    if (d->channel_id == 0 && d->monitor_id >= 0)
        return d->monitor_id;

    g_return_val_if_fail(d->monitor_id <= 0, -1);

    return d->channel_id;
}

/* ---------------------------------------------------------------- */

static void update_mouse_mode(SpiceChannel *channel, gpointer data)
{
    SpiceDisplay *display = static_cast<SpiceDisplay*>(data);
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
    if (!d)
        return;
    g_object_get(channel, "mouse-mode", &d->mouse_mode, NULL);
}

/* ---------------------------------------------------------------- */

static void clipboardSelection(SpiceMainChannel *channel, guint selection, guint type, gpointer data, guint size, gpointer user_data)
{
    SpiceQt *client = static_cast<SpiceQt *>(user_data);
    client->handleClipboardSelection(selection, type, data, size);
}

static gboolean clipboardSelectionGrab(SpiceMainChannel *channel, guint selection, gpointer types, guint ntypes, gpointer user_data)
{
    SpiceQt *client = static_cast<SpiceQt *>(user_data);
    return client->handleClipboardSelectionGrab(channel, selection, types, ntypes);
}

static void clipboardSelectionRelease(SpiceMainChannel *channel, guint selection, gpointer user_data)
{
    SpiceQt *client = static_cast<SpiceQt *>(user_data);
    client->handleClipboardSelectionRelease(selection);
}

static gboolean clipboardSelectionRequest(SpiceMainChannel *channel, guint selection, guint type, gpointer user_data)
{
    SpiceQt *client = static_cast<SpiceQt *>(user_data);
    return client->handleClipboardSelectionRequest(channel, selection, type);
}

void SpiceQt::handleClipboardSelection(guint selection, guint type, gpointer data, guint size)
{
    qDebug() << "Clipboard data from guest";
    QByteArray clipboardData(reinterpret_cast<const char*>(data), static_cast<int>(size));
    QString clipboardText = QString::fromUtf8(clipboardData);
    qDebug() << "Clipboard text received: " << clipboardText;

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(clipboardText, QClipboard::Clipboard);
}

gboolean SpiceQt::handleClipboardSelectionGrab(SpiceMainChannel *channel, guint selection, gpointer types, guint ntypes)
{
    qDebug() << "Clipboard grab from guest";
    guint32 type = VD_AGENT_CLIPBOARD_UTF8_TEXT;
    spice_main_channel_clipboard_selection_request(channel, selection, type);//将虚拟机剪贴板发送到主机
//    request_clipboard_data(channel);
    return TRUE; // Returning TRUE to indicate successful handling
}

void SpiceQt::handleClipboardSelectionRelease(guint selection)
{
    qDebug() << "Clipboard released";
    // Implement logic to handle clipboard release if necessary
}

gboolean SpiceQt::handleClipboardSelectionRequest(SpiceMainChannel *channel, guint selection, guint type)
{
    qDebug() << "Clipboard request from guest";
    QClipboard *clipboard = QApplication::clipboard();
    QString clipboardText = clipboard->text();
    QByteArray data = clipboardText.toUtf8();
    qDebug() << "Clipboard text: " << clipboardText;
    qDebug() << "Clipboard data size: " << data.size();
//    qDebug() << "Main channel: " << mainChannel;
    qDebug() << "Clipboard request from guest";
    if (channel) {
        spice_main_channel_clipboard_selection_notify(channel, selection, type,
                                              reinterpret_cast<const guchar *>(data.data()), static_cast<size_t>(data.size()));
        qDebug() << "Clipboard data sent to SPICE";
    } else {
        qDebug() << "Main channel is null";
        return FALSE; // Returning FALSE to indicate unsuccessful handling
    }

    return TRUE; // Returning TRUE to indicate successful handling
}


/*--------------------------------------------------------------------------------------*/

void send_key(SpiceDisplay *display, int scancode, int down)
{
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
    uint32_t i, b, m;

    if (!d || !d->inputs)
        return;

    i = scancode / 32;
    b = scancode % 32;
    m = (1 << b);
    g_return_if_fail(i < SPICE_N_ELEMENTS(d->key_state));

    if (down) {
        spice_inputs_key_press(d->inputs, scancode);
        d->key_state[i] |= m;
    } else {
        if (!(d->key_state[i] & m)) {
            return;
        }
        spice_inputs_key_release(d->inputs, scancode);
        d->key_state[i] &= ~m;
    }
}

/* ---------------------------------------------------------------- */

static void primary_create(SpiceChannel *channel, gint format, gint width, gint height, gint stride, gint shmid, gpointer imgdata, gpointer data) {

    SpiceDisplay *display = static_cast<SpiceDisplay*>(data);
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);

    // TODO: For now, don't do anything for secondary monitors
    if (get_display_id(display) > 0) {
        return;
    }

    d->format = static_cast<SpiceSurfaceFmt>(format);
    d->stride = stride;
    d->shmid = shmid;
    d->width = width;
    d->height = height;
    d->data_origin = d->data = imgdata;
    callbackSettingsChanged(display, width, height, 4);
}

static void primary_destroy(SpiceChannel *channel, gpointer data) {
    SpiceDisplay *display = SPICE_DISPLAY(data);
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
    if (!d)
        return;

    d->format = static_cast<SpiceSurfaceFmt>(0);
    d->width  = 0;
    d->height = 0;
    d->stride = 0;
    d->shmid  = 0;
    d->data   = 0;
    d->data_origin = 0;
}

static void invalidate(SpiceChannel *channel,
                       gint x, gint y, gint w, gint h, gpointer data) {
    SpiceDisplay *display = static_cast<SpiceDisplay*>(data);
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
    if (!d)
        return;
    if (x + w > d->width || y + h > d->height) {
        ;
    } else {
        callbackInvalidate(d, x, y, w, h);
    }
}

static void mark(SpiceChannel *channel, gint mark, gpointer data) {
    SpiceDisplay *display = static_cast<SpiceDisplay*>(data);
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
    if (!d)
        return;
    d->mark = mark;
    spice_main_set_display_enabled(d->main, d->channel_id, d->mark != 0);
}

static void cursor_invalidate(SpiceDisplay *display)
{
}

static void cursor_move(SpiceCursorChannel *channel, gint x, gint y, gpointer data)
{
    SpiceDisplay *display = SPICE_DISPLAY(data);
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
    qDebug()<<"光标移动！";
    if (!d || !d->cursor_init_done) {
        SPICE_DEBUG("Cursor channel not initialized");
        return;
    }
    //SpiceQt::getSpice()->updateCursor(x, y);
    d->spiceQtInstance->updateCursor(x, y);
}

static void cursor_reset(SpiceCursorChannel *channel, gpointer data)
{
    SpiceDisplay *display = SPICE_DISPLAY(data);
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);

    if (!d || !d->cursor_init_done) {
        SPICE_DEBUG("Cursor channel not initialized");
        return;
    }
    d->cursor_visible = TRUE;
    //SpiceQt::getSpice()->showCursor(true);
    d->spiceQtInstance->showCursor(true);
}

static void cursor_set(SpiceCursorChannel *channel,
                       gint width, gint height, gint hot_x, gint hot_y,
                       gpointer rgba, gpointer data)
{
    SpiceDisplay *display = SPICE_DISPLAY(data);
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);

    if (!d || !d->cursor_init_done) {
        SPICE_DEBUG("Cursor channel not initialized");
        return;
    }
//    qDebug()<<"光标位置设置！";
    d->cursor_width = width;// + hot_x;
    d->cursor_height = height;// + hot_y;
    d->cursor_hot_x = hot_x;
    d->cursor_hot_y = hot_y;

    // 将光标图像数据复制到 d->cursor_data
    if (d->cursor_data) {
        g_free(d->cursor_data);
    }
    d->cursor_data = g_malloc(width * height * 4);
    memcpy(d->cursor_data, rgba, width * height * 4);

    d->cursor_visible = TRUE;
    d->cursor_init_done = TRUE;

    QImage cursorImage(reinterpret_cast<const uchar*>(rgba), width, height, QImage::Format_RGBA8888);
    QCursor cursor(QPixmap::fromImage(cursorImage), hot_x, hot_y);
    QApplication::setOverrideCursor(cursor);

    //SpiceQt::getSpice()->showCursor(true);
    d->spiceQtInstance->showCursor(true);

}

static void cursor_hide(SpiceCursorChannel *channel, gpointer data)
{
    SpiceDisplay *display = SPICE_DISPLAY(data);
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);

    if (!d || !d->cursor_init_done) {
        SPICE_DEBUG("Cursor channel not initialized");
        return;
    }
    d->cursor_visible = FALSE;
    //SpiceQt::getSpice()->showCursor(false);
    d->spiceQtInstance->showCursor(true);
}

static void disconnect_main(SpiceDisplay *display)
{
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);

    if (d->main == NULL)
        return;
    d->main = NULL;
}

static void disconnect_display(SpiceDisplay *display)
{
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);

    if (d->display == NULL)
        return;
    d->display = NULL;
}

static void channel_new(SpiceSession *s, SpiceChannel *channel, gpointer data)
{
    SpiceDisplay *display = static_cast<SpiceDisplay*>(data);
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
    if (!d)
    {
        qDebug() << "Failed to get SpiceDisplayPrivate";
        return;
    }
    int id;

    g_object_get(channel, "channel-id", &id, NULL);
    if (SPICE_IS_MAIN_CHANNEL(channel)) {
        d->main = SPICE_MAIN_CHANNEL(channel);
        //SpiceQt::getSpice()->setMainChannel(SPICE_MAIN_CHANNEL(channel));
        d->spiceQtInstance->setMainChannel(SPICE_MAIN_CHANNEL(channel));
        g_signal_connect(channel, "main-mouse-update",
                                      G_CALLBACK(update_mouse_mode), display);
        update_mouse_mode(channel, display);
        g_signal_connect(channel, "main-clipboard-selection",
                                      G_CALLBACK(clipboardSelection), 0);
        g_signal_connect(channel, "main-clipboard-selection-grab",
                                      G_CALLBACK(clipboardSelectionGrab), 0);
        g_signal_connect(channel, "main-clipboard-selection-release",
                                      G_CALLBACK(clipboardSelectionRelease), 0);
        g_signal_connect(channel, "main-clipboard-selection-request",
                                      G_CALLBACK(clipboardSelectionRequest), 0);
        return;
    }

    if (SPICE_IS_DISPLAY_CHANNEL(channel)) {
        if (id != d->channel_id)
            return;
        d->display = channel;
        g_signal_connect(channel, "display-primary-create",
                         G_CALLBACK(primary_create), display);
        g_signal_connect(channel, "display-primary-destroy",
                         G_CALLBACK(primary_destroy), display);
        g_signal_connect(channel, "display-invalidate",
                         G_CALLBACK(invalidate), display);
        g_signal_connect(channel, "display-mark",
                         G_CALLBACK(mark), display);

        spice_channel_connect(channel);
        return;
    }

    if (SPICE_IS_CURSOR_CHANNEL(channel)) {
        if (id != d->channel_id)
            return;
        d->cursor = SPICE_CURSOR_CHANNEL(channel);
        d->cursor_init_done = TRUE;
        g_signal_connect(channel, "cursor-set",
                         G_CALLBACK(cursor_set), display);
        g_signal_connect(channel, "cursor-move",
                         G_CALLBACK(cursor_move), display);
        g_signal_connect(channel, "cursor-hide",
                         G_CALLBACK(cursor_hide), display);
        g_signal_connect(channel, "cursor-reset",
                         G_CALLBACK(cursor_reset), display);
        qDebug()<<"光标初始化完成!";
        spice_channel_connect(channel);
        return;
    }

    if (SPICE_IS_INPUTS_CHANNEL(channel)) {
        d->inputs = SPICE_INPUTS_CHANNEL(channel);
        if (d->disable_inputs)
            return;
        spice_channel_connect(channel);
        guint32 modifiers;
        //modifiers = SpiceQt::getSpice()->getKeyboardLockModifiers();
        modifiers = d->spiceQtInstance->getKeyboardLockModifiers();
        sync_keyboard_lock_modifiers(display, modifiers);
        return;
    }

#ifdef USE_SMARTCARD
    if (SPICE_IS_SMARTCARD_CHANNEL(channel)) {
        d->smartcard = SPICE_SMARTCARD_CHANNEL(channel);
        spice_channel_connect(channel);
        return;
    }
#endif

    return;
}

static void channel_destroy(SpiceSession *s, SpiceChannel *channel, gpointer data)
{
    SpiceDisplay *display = static_cast<SpiceDisplay*>(data);
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
    int id;

    g_object_get(channel, "channel-id", &id, NULL);
    SPICE_DEBUG("channel_destroy %d", id);

    if (SPICE_IS_MAIN_CHANNEL(channel)) {
        disconnect_main(display);
        return;
    }

    if (SPICE_IS_DISPLAY_CHANNEL(channel)) {
        if (id != d->channel_id)
            return;
        disconnect_display(display);
        return;
    }

    if (SPICE_IS_INPUTS_CHANNEL(channel)) {
        d->inputs = NULL;
        return;
    }

#ifdef USE_SMARTCARD
    if (SPICE_IS_SMARTCARD_CHANNEL(channel)) {
        d->smartcard = NULL;
        return;
    }
#endif

    return;
}

/**
 * spice_display_new:
 * @session: a #SpiceSession
 * @id: the display channel ID to associate with #SpiceDisplay
 *
 * Returns: a new #SpiceDisplay widget.
 **/
SpiceDisplay *spice_display_new(SpiceSession *session, int id, SpiceQt *instance)
{
    SpiceDisplay *display;
    SpiceDisplayPrivate *d;
    GList *list;
    GList *it;

    display = static_cast<SpiceDisplay*>(g_object_new(SPICE_TYPE_DISPLAY, NULL));
    d = SPICE_DISPLAY_GET_PRIVATE(display);
    d->session = static_cast<SpiceSession*>(g_object_ref(session));
    d->channel_id = id;
    d->spiceQtInstance = instance;
    SPICE_DEBUG("channel_id:%d",d->channel_id);

    g_signal_connect(session, "channel-new",
                     G_CALLBACK(channel_new), display);
    g_signal_connect(session, "channel-destroy",
                     G_CALLBACK(channel_destroy), display);
    list = spice_session_get_channels(session);
    for (it = g_list_first(list); it != NULL; it = g_list_next(it)) {
        channel_new(session, static_cast<SpiceChannel*>(it->data), (gpointer*)display);
    }
    g_list_free(list);

    return display;
}

static void sync_keyboard_lock_modifiers(SpiceDisplay *display, guint32 modifiers)
{
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
    if (!d)
        return;

    if (d->disable_inputs)
        return;

    if (d->inputs)
        spice_inputs_set_key_locks(d->inputs, modifiers);
}
