#include <QApplication>
#include <QDebug>
#include <QPalette>
#include <QPushButton>
#include <QListWidget>
#include "spiceqt.h"
#include "spice-widget.h"
#include "spice-widget-priv.h"
#include "QMainWindow"
#include "QHBoxLayout"


#define SPICE_MAIN_CHANNEL_GET_PRIVATE(obj)                             \
    (G_TYPE_INSTANCE_GET_PRIVATE((obj), SPICE_TYPE_MAIN_CHANNEL, SpiceMainChannelPrivate))

static void main_channel_event(SpiceChannel *channel, SpiceChannelEvent event, gpointer data)
{	
    qDebug()<<"----------------main channel event-------------------";
    SpiceQt *client = static_cast<SpiceQt*>(data);
    qDebug()<<"event:"<<event;
    switch (event) {
    case SPICE_CHANNEL_OPENED:
        qDebug()<<"main channel: connected";
        break;  
    case SPICE_CHANNEL_CLOSED:
        qDebug()<<"main channel: connection lost";
        client->clearImage();
        break;
    case SPICE_CHANNEL_ERROR_CONNECT:
        qDebug()<<"main channel: failed to connect";
        break;
    }
}

static void main_agent_update(SpiceChannel *channel, gpointer data)
{
    SpiceQt *client = static_cast<SpiceQt*>(data);
    bool agent_connected;
    gboolean ac;
    g_object_get(channel, "agent-connected", &ac, NULL);
    agent_connected = ac;
    qDebug()<<"agent is "<<ac;
    if(ac) {
        qDebug()<<"初始化显示器";
        client->initializeMultiMonitor();
    }
    client->setAgentConnected(agent_connected);
}

static void inputs_modifiers(SpiceChannel *channel, gpointer data)
{
   SpiceQt *client = static_cast<SpiceQt*>(data);
    int m;

    g_object_get(channel, "key-modifiers", &m, NULL);
    //SpiceQt::getSpice()->setKbdModifiers(m);
    client->setKbdModifiers(m);
}

/*----------------------------------------------------------------------------*/

void SpiceQt::onClipboardDataChanged()
{
    QClipboard *clipboard = QApplication::clipboard();
    if (clipboard->mimeData()->hasText()) {
        QString clipboardText = clipboard->text();
        QByteArray data = clipboardText.toUtf8();
        guint32 type = VD_AGENT_CLIPBOARD_UTF8_TEXT;

        // Notify SPICE about clipboard data
        spice_main_channel_clipboard_selection_grab(mainChannel, VD_AGENT_CLIPBOARD_SELECTION_CLIPBOARD, &type, 1);
        spice_main_channel_clipboard_selection_notify(mainChannel, VD_AGENT_CLIPBOARD_SELECTION_CLIPBOARD, type,
                                              reinterpret_cast<const guchar *>(data.data()), static_cast<size_t>(data.size()));
        qDebug()<<"发送成功！";
    }
}

/*----------------------------------------------------------------------------*/
//音频播放处理
static void on_playback_data(SpicePlaybackChannel *channel, gpointer data, int size, gpointer user_data)
{
    qDebug()<<"音频播放数据";
    SpiceQt *self = static_cast<SpiceQt*>(user_data);
    self->writeAudioOutput((const char*)data, size);
}

static void on_playback_start(SpicePlaybackChannel *channel, gpointer user_data)
{
    qDebug()<<"音频播放开始";
    SpiceQt *self = static_cast<SpiceQt*>(user_data);
    if(!self)
        qDebug()<<"实例为空！";
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    qDebug()<<"音频播放进行";
    self->startAudioOutput(format);
    qDebug()<<"音频播放完成";
}

static void on_playback_stop(SpicePlaybackChannel *channel, gpointer user_data)
{
    qDebug()<<"音频播放结束";
    SpiceQt *self = static_cast<SpiceQt*>(user_data);
    self->stopAudioOutput();
}

void SpiceQt::initializePlaybackChannel(SpicePlaybackChannel *channel)
{
    playback_channel = channel;
}

/*----------------------------------------------------------------------------*/
// 检查并打印支持的音频格式
void checkSupportedAudioFormats()
{
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    qDebug() << "Default audio output device:" << info.deviceName();

    QList<int> sampleRates = info.supportedSampleRates();
    qDebug() << "Supported sample rates:" << sampleRates;

    QList<int> sampleSizes = info.supportedSampleSizes();
    qDebug() << "Supported sample sizes:" << sampleSizes;

    QList<int> channelCounts = info.supportedChannelCounts();
    qDebug() << "Supported channel counts:" << channelCounts;

    QList<QAudioFormat::Endian> byteOrders = info.supportedByteOrders();
    qDebug() << "Supported byte orders:" << byteOrders;

    QList<QAudioFormat::SampleType> sampleTypes = info.supportedSampleTypes();
    qDebug() << "Supported sample types:" << sampleTypes;

    QList<QString> codecs = info.supportedCodecs();
    qDebug() << "Supported codecs:" << codecs;
}

//公共函数获取私有音频变量
void SpiceQt::writeAudioOutput(const char* data, int size)
{
    audioOutputDevice->write(data, size);
}

void SpiceQt::startAudioOutput(const QAudioFormat &format)
{
    checkSupportedAudioFormats();
    // 检查音频设备是否支持所需的音频格式
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }
    // 添加调试信息
    qDebug() << "Starting audio output with format:" << format;
    audioOutput = new QAudioOutput(format);

    if (!audioOutput) {
        qDebug() << "Failed to create QAudioOutput";
        return;
    }
    qDebug() << "请求请求权请求权请求权请求权";
    QAudio::State state = audioOutput->state();
    qDebug() << "QAudioOutput initial state:" << state;

    audioOutputDevice = audioOutput->start();

    if (!audioOutputDevice) {
            qDebug() << "Failed to start QAudioOutput";
            delete audioOutput;
            audioOutput = nullptr;
            return;
        }

     // 添加调试信息
     qDebug() << "Audio output started successfully";
     state = audioOutput->state();
     qDebug() << "QAudioOutput state after start:" << state;
}

void SpiceQt::stopAudioOutput()
{
    audioOutput->stop();
    delete audioOutputDevice;
    delete audioOutput;
}

void SpiceQt::startAudioInput(const QAudioFormat &format)
{
    audioInputBuffer = new QBuffer();
    audioInputBuffer->open(QIODevice::WriteOnly);

    audioInput = new QAudioInput(format);
    connect(audioInput, &QAudioInput::notify, this, &SpiceQt::sendRecordedData);
    audioInput->start(audioInputBuffer);
}

void SpiceQt::stopAudioInput()
{
    audioInput->stop();
    delete audioInputBuffer;
    delete audioInput;
}

void SpiceQt::sendRecordedData()
{
    if (audioInputBuffer->buffer().size() > 0) {
        spice_record_channel_send_data(record_channel, (gpointer)audioInputBuffer->buffer().data(), audioInputBuffer->buffer().size(), 0);
        audioInputBuffer->buffer().clear();
    }
}

/*----------------------------------------------------------------------------*/
//USB重定向功能实现
static void on_auto_connect_failed(SpiceUsbDeviceManager *manager, SpiceUsbDevice *device, GError *error, gpointer user_data)
{
    qDebug() << "自动连接USB设备失败";
    qDebug() << "设备：" << spice_usb_device_get_description(device, "%1$s %2$s %3$s at %4$d-%5$d");
    qDebug() << "错误信息: " << error->message;
}

static void on_device_error(SpiceUsbDeviceManager *manager, SpiceUsbDevice *device, GError *error, gpointer user_data)
{
    qDebug() << "USB设备错误: " << error->message;
}

static void on_device_added(SpiceUsbDeviceManager *manager, SpiceUsbDevice *device, gpointer user_data)
{
    // 获取设备描述
    gchar *description_c = spice_usb_device_get_description(device, "%1$s %2$s %3$s at %4$d-%5$d");
    QString description = QString::fromUtf8(description_c);
    qDebug() << description << "on_device_added设备已添加";
    SpiceQt *client = static_cast<SpiceQt *>(user_data);
    if(client == nullptr)
    {
        qDebug()<<"USB client为空！";
    }
    // 处理USB设备添加
    Q_EMIT client->usbDeviceAdded(description);
}

static void on_device_removed(SpiceUsbDeviceManager *manager, SpiceUsbDevice *device, gpointer user_data)
{
    // 获取设备描述
    gchar *description_c = spice_usb_device_get_description(device, "%1$s %2$s %3$s at %4$d-%5$d");
    QString description = QString::fromUtf8(description_c);
    qDebug() << description << "设备已移除";
    SpiceQt *client = static_cast<SpiceQt *>(user_data);
    if(client == nullptr)
    {
        qDebug()<<"USB client为空！";
    }
    Q_EMIT client->usbDeviceRemoved(description);

}

static void on_connect_device_async_complete(GObject *source_object, GAsyncResult *res, gpointer user_data) {
    SpiceQt *client = static_cast<SpiceQt *>(user_data);
    if(client == nullptr)
    {
        qDebug() << "USB client为空！";
        return;
    }
    GError *error = NULL;
    gboolean success = spice_usb_device_manager_connect_device_finish(SPICE_USB_DEVICE_MANAGER(source_object), res, &error);
    if (!success) {
        qDebug() << "连接设备时出错：" << (error ? error->message : "未知错误");
        if (error) {
            g_error_free(error);
        }
    } else {
        SpiceUsbDevice *device = (SpiceUsbDevice *)g_async_result_get_user_data(res);
        gchar *description_c = spice_usb_device_get_description(device, "%1$s %2$s %3$s at %4$d-%5$d");
        QString description = QString::fromUtf8(description_c);
        qDebug() << "设备：" << description << "已连接！";
//        Q_EMIT client->usbDeviceAdded(description);
        g_free(description_c);
    }
}

//static void on_disconnect_device_async_complete(GObject *source_object, GAsyncResult *res, gpointer user_data)
//{
//    SpiceQt *client = static_cast<SpiceQt *>(user_data);
//    if (!client) {
//        qDebug() << "USB client为空！";
//        return;
//    }

//    GError *error = NULL;
//    gboolean success = spice_usb_device_manager_disconnect_device_finish(SPICE_USB_DEVICE_MANAGER(source_object), res, &error);

//    if (!success) {
//        qDebug() << "断开设备时出错：" << (error ? error->message : "未知错误");
//        if (error) {
//            g_error_free(error);
//        }
//        // 可以从 redirectedDevices 中移除设备，允许重试
//    } else {
//        qDebug() << "USB 设备已成功断开。";
//        // 发出设备断开信号
//        const gchar *USB_DESCRIPTION_FORMAT = "%s %s %s at %d-%d";
//        SpiceUsbDevice *device = spice_usb_device_manager_disconnect_device_finish(SPICE_USB_DEVICE_MANAGER(source_object), res, &error);
//        if (device) {
//            gchar *description_c = spice_usb_device_get_description(device, USB_DESCRIPTION_FORMAT);
//            if (description_c) {
//                QString description = QString::fromUtf8(description_c);
//                emit client->deviceDisconnected(description);
//                g_free(description_c);
//            }
//        }
//    }
//}

static void on_disconnect_device_async_complete(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
    SpiceQt *client = static_cast<SpiceQt *>(user_data);
    if (!client) {
        qDebug() << "USB client为空！";
        return;
    }

    GError *error = NULL;
    gboolean success = spice_usb_device_manager_disconnect_device_finish(SPICE_USB_DEVICE_MANAGER(source_object), res, &error);

    // 由于我们传递的是设备描述的指针，这里需要先将其转换回 QString*
    QString *descPtr = static_cast<QString *>(user_data);
    if (!descPtr) {
        qDebug() << "设备描述指针为空！";
        return;
    }
    QString description = *descPtr;
    delete descPtr; // 释放内存

    if (!success) {
        qDebug() << "断开设备时出错：" << (error ? error->message : "未知错误");
        if (error) {
            g_error_free(error);
        }
        // 可以从 redirectedDevices 中移除设备，允许重试
    } else {
        qDebug() << "USB 设备已成功断开：" << description;
        // 发出设备断开信号
//        Q_EMIT client->usbDeviceRemoved(description);
    }
}

void SpiceQt::disconnectUsbDevices(const QStringList &devices)
{
    if (devices.isEmpty()) {
        qDebug() << "没有设备被选择进行断开。";
        return;
    }
    SpiceSession *session = getSession();
    if (!session) {
        qDebug() << "SpiceSession is NULL";
        return;
    }

    if (!usb_device_manager) {
        qDebug() << "Failed to get SpiceUsbDeviceManager";
        return;
    }

    const gchar *USB_DESCRIPTION_FORMAT = "%s %s %s at %d-%d";

    GPtrArray *DeviceList = spice_usb_device_manager_get_devices(usb_device_manager);
    if (DeviceList)
    {
        for (guint i = 0; i < DeviceList->len; i++) {
            SpiceUsbDevice *device = (SpiceUsbDevice *)g_ptr_array_index(DeviceList, i);
            gchar *description_c = spice_usb_device_get_description(device, USB_DESCRIPTION_FORMAT);
            if (description_c) {
                QString description = QString::fromUtf8(description_c);
                g_free(description_c);

                if (devices.contains(description) && redirectedDevices.contains(description)) {
                    // 检查设备是否已经连接
                    if (spice_usb_device_manager_is_device_connected(usb_device_manager, device)) {
                        qDebug() << "尝试断开 USB 设备：" << description;
                        // 创建一个新的 QString，作为 user_data 传递给回调
                        QString *descPtr = new QString(description);

                        // 异步断开设备
                        spice_usb_device_manager_disconnect_device_async(usb_device_manager, device, NULL, on_disconnect_device_async_complete, descPtr);
                        qDebug() << "已发起断开请求，等待回调结果...";
                        // 从已重定向设备列表中移除设备
                        redirectedDevices.remove(description);
                    }
                    else {
                        qDebug() << "设备未连接：" << description;
                        // 从已重定向设备列表中移除设备
                        redirectedDevices.remove(description);
                    }
                }
            } else {
                qDebug() << "Failed to get device description for device index:" << i;
            }
        }
        g_ptr_array_free(DeviceList, TRUE);
    }
    else {
        qDebug() << "No USB devices found or USB Device Manager returned NULL";
    }
}


void SpiceQt::redirect_usb_device(const QStringList &devices)
{
    if (devices.isEmpty()) {
        qDebug() << "没有设备被选择进行重定向。";
        return;
    }

    SpiceSession *session = getSession();
    if (!session) {
        qDebug() << "SpiceSession is NULL";
        return;
    }

    SpiceUsbDeviceManager *manager = spice_usb_device_manager_get(session, NULL);
    if (!manager) {
        qDebug() << "Failed to get SpiceUsbDeviceManager";
        return;
    }

    const gchar *USB_DESCRIPTION_FORMAT = "%s %s %s at %d-%d";

    GPtrArray *DeviceList = spice_usb_device_manager_get_devices(manager);
    if(DeviceList)
    {
        for (guint i = 0; i < DeviceList->len; i++) {
            SpiceUsbDevice *device = (SpiceUsbDevice *)g_ptr_array_index(DeviceList, i);
            gchar *description_c = spice_usb_device_get_description(device, USB_DESCRIPTION_FORMAT);
            if (description_c) {
                QString description = QString::fromUtf8(description_c);
                g_free(description_c);

                if (devices.contains(description) && !redirectedDevices.contains(description)) {
                    // 检查设备是否已经连接
                    if (!spice_usb_device_manager_is_device_connected(manager, device)) {
                        qDebug() << "尝试连接 USB 设备：" << description;
                        GError *error = NULL;

                        // 异步连接设备
                        spice_usb_device_manager_connect_device_async(manager, device, NULL, on_connect_device_async_complete, this);
                        if (error) {
                            qDebug() << "连接设备时出错：" << error->message;
                            g_error_free(error);
                        } else {
                            qDebug() << "已发起连接请求，等待回调结果...";
                            // 添加到已重定向设备列表
                            redirectedDevices.insert(description);
                        }
                    }
                    else {
                        qDebug() << "设备已连接：" << description;
                        // 添加到已重定向设备列表
                        redirectedDevices.insert(description);
                    }
                }
            } else {
                qDebug() << "Failed to get device description for device index:" << i;
            }
        }
        g_ptr_array_free(DeviceList, TRUE);
    }
    else {
        qDebug() << "No USB devices found or USB Device Manager returned NULL";
    }
}

/*----------------------------------------------------------------------------*/

SpiceDisplay* SpiceQt::getSpiceDisplayById(int channel_id) {
    auto it = displays.find(channel_id);
    if (it != displays.end()) {
        return it->second;  // 返回对应的显示器
    }
    return nullptr;  // 如果不存在，返回空指针
}

void SpiceQt::addSpiceDisplay(SpiceDisplay* display, int channel_id) {
    displays[channel_id] = display;  // 将显示器与 channel-id 关联
    qDebug() << "SpiceDisplay added for Channel ID:" << channel_id;
}

static void channel_new(SpiceSession *session, SpiceChannel *channel, gpointer data)
{
    SpiceQt *client = static_cast<SpiceQt*>(data);

    int id;
    g_object_get(channel, "channel-id", &id, NULL);
    if (SPICE_IS_MAIN_CHANNEL(channel)) {
        if(client == nullptr)
        {
            qDebug()<<"SpiceQt 为空！！！";
        }
        // 检查主通道是否支持无缝迁移
        if (spice_channel_test_capability(SPICE_CHANNEL(channel), SPICE_MAIN_CAP_SEAMLESS_MIGRATE)) {
            qDebug() << "Main channel supports seamless migration.";
        } else {
            qDebug() << "Main channel does not support seamless migration.";
        }
       qDebug()<<"主通道初始化";
       gboolean can_connect1 = spice_channel_test_common_capability(channel, SPICE_COMMON_CAP_PROTOCOL_AUTH_SELECTION);
       qDebug() << "Channel can connect:" << can_connect1;

       g_signal_connect(channel, "channel-event",
                         G_CALLBACK(main_channel_event), client);
       g_signal_connect(channel, "main-agent-update",
                         G_CALLBACK(main_agent_update), client);
       return;
    }
    if (SPICE_IS_DISPLAY_CHANNEL(channel)) {
        SpiceDisplay *display = client->spiceDisplayGLib();
        if (display)
            return;
        display = spice_display_new(session, id, client);
        client->setSpiceDisplayGLib(display);
    }
    if (SPICE_IS_INPUTS_CHANNEL(channel)) {
        qDebug()<<"输入通道初始化！！";
        g_signal_connect(channel, "inputs-modifiers",
                         G_CALLBACK(inputs_modifiers), client);

    }
    if (SPICE_IS_PLAYBACK_CHANNEL(channel)) {

        //SpiceAudio *audio = SpiceQt::getSpice()->spiceAudioGLib();
        SpiceAudio *audio = client->spiceAudioGLib();
        if (audio)
            return;
        audio = spice_audio_get(session, NULL);
        if(!audio)
            qDebug()<<"音频为空！";
        client->setSpiceAudioGLib(audio);
//        SpiceQt::getSpice()->initializePlaybackChannel(SPICE_PLAYBACK_CHANNEL(channel));
        qDebug()<<"音频播放初始化完成！";
    }
    if (SPICE_IS_RECORD_CHANNEL(channel)) {
        // 初始化录音通道
//        SpiceQt::getSpice()->initializeRecordChannel(SPICE_RECORD_CHANNEL(channel));
    }
}

void SpiceQt::updateCursor(int x, int y)
{
    cursorX = x;
    cursorY = y;
    // 更新光标位置的逻辑
    QCursor cursor = this->cursor();
    cursor.setPos(mapToGlobal(QPoint(x, y)));
    setCursor(cursor);
}

static void channel_destroy(SpiceSession *session, SpiceChannel *channel)
{
}

//SpiceQt * SpiceQt::instance = NULL;
QMap<int, int> * SpiceQt::keymap = NULL;

SpiceQt::SpiceQt(QWidget *parent)
    : QWidget(parent), agentConnected(true), resizeTimer(new QTimer(this)), imageUpdateLock(false)
{

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    display = NULL;
    SGsession = NULL;
    audio = NULL;

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Active, QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);
    setMouseTracking(true);


//    grabMouse();
//    grabKeyboard();与主窗口键盘事件冲突

    QObject::connect(QApplication::clipboard(), &QClipboard::dataChanged, this, &SpiceQt::onClipboardDataChanged);

    // 初始化 QTimer，用于延迟拉伸后的图像更新
    resizeTimer->setSingleShot(true); // 设置为单次触发
    // 连接 QTimer 的超时信号到 onResizeTimeout 槽函数
    connect(resizeTimer, &QTimer::timeout, this, &SpiceQt::onResizeTimeout);
}

SpiceQt::~SpiceQt()
{
    // Cleanup resources
    // 断开与SPICE服务器的连接
    disconnectFromGuest();

    // 释放 QTimer
    if (resizeTimer) {
        delete resizeTimer;
    }

    // 释放显示通道
    if (display) {
        qDebug() << "Releasing display channel";
        g_object_unref(display);  // 释放引用
        display = nullptr;
    }

    // 清理SPICE会话
    if (SGsession) {
        g_object_unref(SGsession);
        SGsession = nullptr;
    }

    // 清理USB设备管理器
    if (usb_device_manager) {
        g_object_unref(usb_device_manager);
        usb_device_manager = nullptr;
    }

    qDebug() << "SpiceQt对象已成功销毁";
}

SpiceDisplay* SpiceQt::getDisplay() const
{
    if(display)
        return display;
}

void SpiceQt::clearImage()
{
    img = QImage(dataWidth, dataHeight, QImage::Format_RGB32);
    if (!img.isNull()) {
        QPainter painter(&img);
        painter.setBrush(QBrush(Qt::black));
        painter.drawRect(0, 0, dataWidth, dataHeight);
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, tr("Connection lost, Please reconnect."));
        painter.end(); 
    }
}

SpiceSession *SpiceQt::getSession()
{
    return SGsession;
}

void SpiceQt::setSpiceAudioGLib(SpiceAudio *sa)
{ 
    audio = sa;
}

void SpiceQt::setSpiceDisplayGLib(SpiceDisplay *sd)
{ 
    display = sd;
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
}

void SpiceQt::disconnectFromGuest()
{
    if (SGsession) {
//        spice_session_disconnect(SGsession);
//        display = NULL;
//        SGsession = NULL;
//        audio = NULL;
        spice_session_disconnect(SGsession);
        g_object_unref(SGsession);
        SGsession = nullptr;
        qDebug() << "Disconnected from guest";
    }
}

void SpiceQt::connectToGuest(const QString &host, const QString &port)
{
//    spice_util_set_debug(true);
    disconnectFromGuest();
    sizeAdjusted = false;  // 每次连接新的虚拟机时重置该标志
    qDebug()<<"ip:"<<host<<" "<<"端口号:"<<port;
    SGsession = spice_session_new();
    g_object_set(SGsession, "host", \
                 host.toLatin1().constData(), NULL);
    g_object_set(SGsession, "port", \
                 port.toLatin1().constData(), NULL);

    g_signal_connect(SGsession, "channel-new",
                                 G_CALLBACK(channel_new), this);
    g_signal_connect(SGsession, "channel-destroy", G_CALLBACK(channel_destroy), this);

    if (!spice_session_connect(SGsession)) {
        qDebug() << "Failed to connect to Spice session";
        g_object_unref(SGsession);
        SGsession = nullptr;
    }
    qDebug()<<"--------------------Spice Get Channel-------------------";
    GList *spice_channel = spice_session_get_channels(SGsession);
    for (GList *it = spice_channel; it != NULL; it = it->next) {
        SpiceChannel *channel = SPICE_CHANNEL(it->data);
        qDebug() << "Channel type:" << G_OBJECT_TYPE_NAME(channel);
        if (SPICE_IS_MAIN_CHANNEL(channel)) {
            qDebug() << "Main channel found!";
        }
    }
    usb_device_manager = spice_usb_device_manager_get(SGsession, NULL);
    if (!usb_device_manager) {
        qDebug() << "Failed to get USB device manager";
        return;
    }
    g_signal_connect(usb_device_manager, "auto-connect-failed", G_CALLBACK(on_auto_connect_failed), this);
    g_signal_connect(usb_device_manager, "device-error", G_CALLBACK(on_device_error), this);
    g_signal_connect(usb_device_manager, "device-added", G_CALLBACK(on_device_added), this);
    g_signal_connect(usb_device_manager, "device-removed", G_CALLBACK(on_device_removed), this);

    // 获取主频道
    GList *channels = spice_session_get_channels(SGsession);
    for (GList *it = channels; it != NULL; it = it->next) {
        SpiceChannel *channel = SPICE_CHANNEL(it->data);
        if (SPICE_IS_MAIN_CHANNEL(channel)) {
            mainChannel = SPICE_MAIN_CHANNEL(channel);
            break;
        }
    }
    g_list_free(channels);

}

// 获取当前远程虚拟机的显示器数量
int SpiceQt::detectDisplays() {
    if (!SGsession) return 0; // 检查是否已经连接到远程会话

    GList *channels = spice_session_get_channels(SGsession);
    int displayCount = 0;

    for (GList *it = channels; it != NULL; it = it->next) {
        SpiceChannel *channel = SPICE_CHANNEL(it->data);
        if (SPICE_IS_DISPLAY_CHANNEL(channel)) {
            displayCount++; // 统计显示器数量
        }
    }
    g_list_free(channels);
    return displayCount;
}

void SpiceQt::initializeMultiMonitor() {
    // 初始化多个显示器的配置
    monitorConfigs.clear();
    for (int i = 0; i < MAX_MONITORS; i++) {
        SpiceDisplayMonitorConfig monitor;
        monitor.id = i;
//        monitor.surface_id = 0; // 假设每个显示器都使用相同的surface
        monitor.x = i * 1920; // 每个显示器的x坐标是前一个显示器宽度的累加
        monitor.y = 0;
        monitor.width = 1920;
        monitor.height = 1080;

        monitorConfigs.push_back(monitor);

        qDebug()<<"monitorConfigs' size:"<<monitorConfigs.size();

        // 调用 SPICE 的主通道更新显示器布局
        spice_main_channel_update_display(mainChannel, monitor.id, monitor.x,
                                          monitor.y, monitor.width, monitor.height, TRUE);
        spice_main_channel_update_display_enabled(mainChannel, monitor.id, TRUE, TRUE);
        qDebug() << "Monitor configured. ID:" << monitor.id
                 << "Resolution:" << monitor.width << "x" << monitor.height
                 << "Position:" << monitor.x << "," << monitor.y;
    }
    // 发送所有显示器配置到虚拟机
    spice_main_channel_send_monitor_config(mainChannel);
    qDebug() << "Multi-monitor configuration applied.";
    qDebug()<<"-------------------------显示器配置完成！！！------------------------";
    // 获取并存储其他显示器信息，等待用户选择后启用
    int numMonitors = detectDisplays(); // 假设你有一个方法来获取总的显示器数量
    qDebug() << "总显示器数: " << numMonitors;

    for (int i = 1; i < numMonitors; i++) {
        // 记录其他显示器信息，但不启用
        SpiceDisplayMonitorConfig monitor;
        monitor.id = i;
        monitorConfigs.push_back(monitor);
    }
}

void SpiceQt::updateResolution(int width, int height) {
    if (!sizeAdjusted) {
        Q_EMIT resolutionChanged(width, height);  // 只发射一次信号
        sizeAdjusted = true;  // 标记窗口已经调整过大小
    }
}

void SpiceQt::initializeWithSession(SpiceSession *session, int monitorId)
{
    if (!session) {
        qWarning() << "SpiceSession is null, cannot initialize SpiceQt.";
        return;
    }
    this->SGsession = session;
    this->monitor_id = monitorId;

    qDebug()<<"--------------开始启用显示器----------------"<<endl;
    // 启用显示器
    enableMonitor(monitorId);

    qDebug()<<"--------------结束启用显示器----------------"<<endl;
    // 获取主通道
        SpiceMainChannel *mainChannel = getMainChannel();
        if (mainChannel) {
            qDebug()<<"--------------initializeWithSession主通道不空----------------"<<endl;
            // 主动设置显示器的初始配置
            SpiceDisplayMonitorConfig monitor_config;
            monitor_config.id = monitorId;       // 每个显示器应有独立的 ID
            monitor_config.surface_id = monitorId; // 使用 monitorId 区分不同的显示器
            monitor_config.x = monitorId * 1920; // 每个显示器的 X 坐标不同（例如，1920 像素偏移）
            monitor_config.y = 0;                // Y 坐标默认设置为 0
            monitor_config.width = 1920;         // 初始宽度
            monitor_config.height = 1080;        // 初始高度

            // 调用 spice_main_channel_update_display 更新显示器配置
            spice_main_channel_update_display(mainChannel, monitor_config.id, monitor_config.x, monitor_config.y, monitor_config.width, monitor_config.height, TRUE);
            spice_main_channel_update_display_enabled(mainChannel, monitor_config.id, TRUE, TRUE);
            // 发送显示器配置到虚拟机
            spice_main_channel_send_monitor_config(mainChannel);

            qDebug() << "Initial display configuration sent for monitor ID:" << monitorId;
        } else {
            qWarning() << "Failed to get SpiceMainChannel, cannot send initial monitor config.";
        }

        qDebug() << "SpiceQt successfully initialized with monitor ID:" << monitorId;
}

void SpiceQt::enableMonitor(int monitorId) {
    SpiceMainChannel *mainChannel = this->getMainChannel();
    qDebug()<<"--------------获取主通道----------------"<<endl;
    if (mainChannel) {
        spice_main_set_display_enabled(mainChannel, monitorId, TRUE);
    }
    else {
        qDebug()<<"--------------主通道为空!--------------"<<endl;
    }
}

SpiceDisplayPrivate* SpiceQt::getSpiceDisplayPrivate()
{
    // Assuming SpiceQt has a method to return the display
    SpiceDisplay *spice_display = spiceDisplayGLib();
    if(!spice_display)
    {
        qDebug()<<"display为空！";
    }    
    return SPICE_DISPLAY_GET_PRIVATE(spice_display);

}
void SpiceQt::initializeCursor(SpiceDisplayPrivate *d)
{
    qDebug() << "Initializing cursor...";
    // Cursor initialization logic
    d->cursor_init_done = TRUE;
    qDebug() << "Cursor initialized";
}

quint32 SpiceQt::getKeyboardLockModifiers()
{
    quint32 modifiers = 0;
    Qt::KeyboardModifiers keyboardModifiers = QApplication::keyboardModifiers();

    if (capsLock)
        modifiers |= SPICE_INPUTS_CAPS_LOCK;
    if (numLock)
        modifiers |= SPICE_INPUTS_NUM_LOCK;
    if (scrollLock)
        modifiers |= SPICE_INPUTS_SCROLL_LOCK;

    return modifiers;
}

void SpiceQt::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    if (!img.isNull())
    {        
        QImage scaledImg = img.scaled(this->size(), Qt::IgnoreAspectRatio);
//        qDebug()<<"scaledImg size:"<<scaledImg.size();
        p.drawImage(0, 0, scaledImg);
    }
}

void SpiceQt::resizeEvent(QResizeEvent *event)
{

    QWidget::resizeEvent(event);

    // 标记拉伸开始
    // 锁定图像更新，防止在拉伸过程中频繁重绘
    imageUpdateLock = true;
    resizingInProgress = true;
    // 如果计时器正在运行，则停止它
    if (resizeTimer->isActive()) {
        resizeTimer->stop();
    }
    int newWidth = event->size().width();
    int newHeight = event->size().height();
    //qDebug() << "spiceQt-rersize: new size:" << newWidth << "x" << newHeight;
    // 更新图像缓冲区大小
    img = img.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    dataWidth = newWidth;
    dataHeight = newHeight;

    // 启动计时器，在 100 毫秒后触发 onResizeTimeout() 槽函数
    resizeTimer->start(100);
//    spiceResize(newWidth, newHeight);
    // 拉伸窗口时调整 img 的大小以适应窗口

//    imageUpdateLock = false; // 解锁
//    update();
}

void SpiceQt::onResizeTimeout() {
    // 拉伸结束后，解除图像更新锁定
    imageUpdateLock = false;

    // 更新远程虚拟机的分辨率，确保在窗口调整稳定后再执行
    int newWidth = this->width();
    int newHeight = this->height();
    qDebug() << "Resize timeout triggered, updating remote resolution to:" << dataWidth << "x" << dataHeight;
    // 调用 spiceResize 函数更新远程虚拟机的分辨率
    spiceResize(dataWidth, dataHeight);

    if (resizingInProgress) {
        resizingInProgress = false; // 标记拉伸结束
        update(); // 在拉伸结束后触发更新
//        repaint();
    }
}

void SpiceQt::spiceResize(int w, int h)
{
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
    if (!d)
        return;

    spice_main_set_display(d->main, d->channel_id, 0, 0, w, h);

}

void SpiceQt::settingsChanged(int w, int h, int bpp)
{
    dataWidth = w;
    dataHeight = h;
    rate = double(height()) / double(dataHeight);
    img = QImage(width(), height(), QImage::Format_RGB32);

//    img.fill(Qt::white);
//    clearImage();
    if (!imageUpdateLock && (w != width() || h != height()))
    {
        spiceResize(width(), height());
    }
    Q_EMIT imageSize(w, h);
//    update();
}

void SpiceQt::updateImage(uchar *data, int x, int y, int w, int h)
{
//    img = QImage(width(), height(), QImage::Format_RGB32);
    if (imageUpdateLock || resizingInProgress) {
        // 如果锁定，则跳过更新
        return;
    }
    uint *source = reinterpret_cast<uint*>(data);
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            // 添加边界检查，确保不越界
            if (i >= 0 && i < img.height() && j >= 0 && j < img.width()) {
                img.setPixel(j, i, source[dataWidth * i + j]);
            }
        }
    }

    update(x, y, w, h);
}

void SpiceQt::setKbdModifiers(int m)
{
    scrollLock = m & SPICE_KEYBOARD_MODIFIER_FLAGS_SCROLL_LOCK;
    capsLock   = m & SPICE_KEYBOARD_MODIFIER_FLAGS_CAPS_LOCK;
    numLock    = m & SPICE_KEYBOARD_MODIFIER_FLAGS_NUM_LOCK;
}

void SpiceQt::mouseMoveEvent(QMouseEvent *event)
{
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);

    if (!d)
        return;
    if (!d->inputs)
        return;
    if (d->disable_inputs)
        return;

    int button_mask = 0;
    if (event->buttons() & Qt::LeftButton)
        button_mask |= SPICE_MOUSE_BUTTON_MASK_LEFT;
    if (event->buttons() & Qt::MidButton)
        button_mask |= SPICE_MOUSE_BUTTON_MASK_MIDDLE;
    if (event->buttons() & Qt::RightButton)
        button_mask |= SPICE_MOUSE_BUTTON_MASK_RIGHT;

    int x, y;
    x = event->x() - d->mx;
    y = event->y() - d->my;

    switch (d->mouse_mode) {
    case SPICE_MOUSE_MODE_CLIENT:
        if (x >= 0 && x < d->width &&
            y >= 0 && y < d->height) {
            spice_inputs_position(d->inputs,
                                  x, y,
                                  d->channel_id,
                                  button_mask);
        }
        break;
    case SPICE_MOUSE_MODE_SERVER:
        break;
    }
}

void SpiceQt::wheelEvent(QWheelEvent *event)
{
    int button;
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);

    if (!d->inputs)
        return;
    if (d->disable_inputs)
        return;
    int delta = event->delta();
    if (delta > 0)
        button = SPICE_MOUSE_BUTTON_UP;
    else if (delta < 0)
        button = SPICE_MOUSE_BUTTON_DOWN;
    else
        return;

    int button_mask = 0;
    if (event->buttons() & Qt::LeftButton)
        button_mask |= SPICE_MOUSE_BUTTON_MASK_LEFT;
    if (event->buttons() & Qt::MidButton)
        button_mask |= SPICE_MOUSE_BUTTON_MASK_MIDDLE;
    if (event->buttons() & Qt::RightButton)
        button_mask |= SPICE_MOUSE_BUTTON_MASK_RIGHT;

    spice_inputs_button_press(d->inputs, button,
                              button_mask);
    spice_inputs_button_release(d->inputs, button,
                                button_mask);
}

void SpiceQt::mousePressEvent(QMouseEvent *event)
{
    grabKeyboard();//防止键盘事件与主窗口冲突
    if (!display)
        return;
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
    if (!d)
        return;

    if (d->disable_inputs)
        return;

    if (d->mouse_mode == SPICE_MOUSE_MODE_SERVER)
        ;
    else
        ;

    if (!d->inputs)
        return;

    int button = 0;
    if (event->button() == Qt::LeftButton)
        button = SPICE_MOUSE_BUTTON_LEFT;
    if (event->button() == Qt::RightButton)
        button = SPICE_MOUSE_BUTTON_RIGHT;
    if (event->button() == Qt::MidButton)
        button = SPICE_MOUSE_BUTTON_MIDDLE;
    if (event->button() == Qt::XButton1)
        button = SPICE_MOUSE_BUTTON_UP;
    if (event->button() == Qt::XButton2)
        button = SPICE_MOUSE_BUTTON_DOWN;

    int button_mask = 0;
    if (event->buttons() & Qt::LeftButton)
        button_mask |= SPICE_MOUSE_BUTTON_MASK_LEFT;
    if (event->buttons() & Qt::MidButton)
        button_mask |= SPICE_MOUSE_BUTTON_MASK_MIDDLE;
    if (event->buttons() & Qt::RightButton)
        button_mask |= SPICE_MOUSE_BUTTON_MASK_RIGHT;

    spice_inputs_button_press(d->inputs,
                              button,
                              button_mask);
}

void SpiceQt::mouseReleaseEvent(QMouseEvent *event)
{
    releaseKeyboard();  // 在鼠标释放时解除键盘输入锁定
    if (!display)
        return;
    SpiceDisplayPrivate *d = SPICE_DISPLAY_GET_PRIVATE(display);
    if (!d)
        return;

    if (d->disable_inputs)
        return;

    if (d->mouse_mode == SPICE_MOUSE_MODE_CLIENT) {
        int x, y;

        /* rule out clicks in outside region */
        x = event->x() - d->mx;
        y = event->y() - d->my;
        if (!(x >= 0 && x < d->width && y >= 0 && y < d->height))
            return;
    }

    if (d->mouse_mode == SPICE_MOUSE_MODE_SERVER)
        ;
    else
        ;

    if (!d->inputs)
        return;

    int button = 0;
    if (event->button() == Qt::LeftButton)
        button = SPICE_MOUSE_BUTTON_LEFT;
    if (event->button() == Qt::RightButton)
        button = SPICE_MOUSE_BUTTON_RIGHT;
    if (event->button() == Qt::MidButton)
        button = SPICE_MOUSE_BUTTON_MIDDLE;
    if (event->button() == Qt::XButton1)
        button = SPICE_MOUSE_BUTTON_UP;
    if (event->button() == Qt::XButton2)
        button = SPICE_MOUSE_BUTTON_DOWN;

    int button_mask = 0;
    if (event->buttons() & Qt::LeftButton)
        button_mask |= SPICE_MOUSE_BUTTON_MASK_LEFT;
    if (event->buttons() & Qt::MidButton)
        button_mask |= SPICE_MOUSE_BUTTON_MASK_MIDDLE;
    if (event->buttons() & Qt::RightButton)
        button_mask |= SPICE_MOUSE_BUTTON_MASK_RIGHT;

    spice_inputs_button_release(d->inputs,
                              button,
                              button_mask);
}

void SpiceQt::enterEvent(QEvent *event)
{
//    XGrabKeyboard(QX11Info::display(), DefaultRootWindow(QX11Info::display()), true,
//                  GrabModeAsync, GrabModeAsync, CurrentTime);
    this->setFocus();
}

void SpiceQt::leaveEvent(QEvent *event)
{
//    XUngrabKeyboard(QX11Info::display(), CurrentTime);
    this->clearFocus();

}

void SpiceQt::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_CapsLock:
            // Toggle Caps Lock state
            capsLock = !capsLock;
            break;
        case Qt::Key_NumLock:
            // Toggle Num Lock state
            numLock = !numLock;
            break;
        case Qt::Key_ScrollLock:
            // Toggle Scroll Lock state
            scrollLock = !scrollLock;
            break;
        default:
            break;
    }
    QMap<int, int> *map = SpiceQt::getKeymap();
    send_key(display, map->value(event->nativeScanCode()), 1);
}

void SpiceQt::keyReleaseEvent(QKeyEvent *event)
{
    QMap<int, int> *map = SpiceQt::getKeymap();
    send_key(display, map->value(event->nativeScanCode()), 0);
}

void SpiceQt::sendShortcut(const QString &shortcut)
{
   static QMap<QString, int> keyMap;
   if (keyMap.isEmpty()) {
       keyMap["Ctrl+Alt+Delete"] = 0x53; // 示例扫描码
       keyMap["Ctrl+Alt+Space"] = 0x39;  // 空格键的扫描码
       keyMap["Ctrl+Alt+F1"] = 0x3B;     // 示例扫描码
       keyMap["Ctrl+Alt+F2"] = 0x3C;     // 示例扫描码
       keyMap["Ctrl+Alt+F3"] = 0x3D;
       keyMap["Ctrl+Alt+F4"] = 0x3E;
       keyMap["Ctrl+Alt+F5"] = 0x3F;
       keyMap["Ctrl+Alt+F6"] = 0x40;
       keyMap["Ctrl+Alt+F7"] = 0x41;
       keyMap["Ctrl+Alt+F8"] = 0x42;
       keyMap["Ctrl+Alt+F9"] = 0x43;
       keyMap["Ctrl+Alt+F10"] = 0x44;
       keyMap["Ctrl+Alt+F11"] = 0x57;
       keyMap["Ctrl+Alt+F12"] = 0x58;
       // 添加更多映射...
   }

   QStringList keys = shortcut.split("+");
   bool ctrlPressed = keys.contains("Ctrl");
   bool altPressed = keys.contains("Alt");
   keys.removeAll("Ctrl");
   keys.removeAll("Alt");

   if (keys.isEmpty()) {
       qWarning() << "Invalid shortcut:" << shortcut;
       return;
   }

   QString key = keys.first();
   if (!keyMap.contains(shortcut)) {
       qWarning() << "Unknown shortcut:" << shortcut;
       return;
   }

   int scancode = keyMap.value(shortcut);

   if (ctrlPressed) {
       send_key(display, 0x1D, 1); // Ctrl 键按下
   }
   if (altPressed) {
       send_key(display, 0x38, 1); // Alt 键按下
   }

   send_key(display, scancode, 1); // 发送对应键码的按下事件
   send_key(display, scancode, 0); // 发送对应键码的抬起事件

   if (altPressed) {
       send_key(display, 0x38, 0); // Alt 键抬起
   }
   if (ctrlPressed) {
       send_key(display, 0x1D, 0); // Ctrl 键抬起
   }
}

void SpiceQt::prepareMouseData()
{
}

QMap<int, int>* SpiceQt::getKeymap()
{
    if (keymap)
        return keymap;
    keymap = new QMap<int, int>;
    keymap->insert(0x9, 0x1);
    keymap->insert(0xa, 0x2);
    keymap->insert(0xb, 0x3);
    keymap->insert(0xc, 0x4);
    keymap->insert(0xd, 0x5);
    keymap->insert(0xe, 0x6);
    keymap->insert(0xf, 0x7);
    keymap->insert(0x10, 0x8);
    keymap->insert(0x11, 0x9);
    keymap->insert(0x12, 0xa);
    keymap->insert(0x13, 0xb);
    keymap->insert(0x14, 0xc);
    keymap->insert(0x15, 0xd);
    keymap->insert(0x16, 0xe);
    keymap->insert(0x17, 0xf);
    keymap->insert(0x18, 0x10);
    keymap->insert(0x19, 0x11);
    keymap->insert(0x1a, 0x12);
    keymap->insert(0x1b, 0x13);
    keymap->insert(0x1c, 0x14);
    keymap->insert(0x1d, 0x15);
    keymap->insert(0x1e, 0x16);
    keymap->insert(0x1f, 0x17);
    keymap->insert(0x20, 0x18);
    keymap->insert(0x21, 0x19);
    keymap->insert(0x22, 0x1a);
    keymap->insert(0x23, 0x1b);
    keymap->insert(0x24, 0x1c);
    keymap->insert(0x25, 0x1d);
    keymap->insert(0x26, 0x1e);
    keymap->insert(0x27, 0x1f);
    keymap->insert(0x28, 0x20);
    keymap->insert(0x29, 0x21);
    keymap->insert(0x2a, 0x22);
    keymap->insert(0x2b, 0x23);
    keymap->insert(0x2c, 0x24);
    keymap->insert(0x2d, 0x25);
    keymap->insert(0x2e, 0x26);
    keymap->insert(0x2f, 0x27);
    keymap->insert(0x30, 0x28);
    keymap->insert(0x31, 0x29);
    keymap->insert(0x32, 0x2a);
    keymap->insert(0x33, 0x2b);
    keymap->insert(0x34, 0x2c);
    keymap->insert(0x35, 0x2d);
    keymap->insert(0x36, 0x2e);
    keymap->insert(0x37, 0x2f);
    keymap->insert(0x38, 0x30);
    keymap->insert(0x39, 0x31);
    keymap->insert(0x3a, 0x32);
    keymap->insert(0x3b, 0x33);
    keymap->insert(0x3c, 0x34);
    keymap->insert(0x3d, 0x35);
    keymap->insert(0x3e, 0x36);
    keymap->insert(0x3f, 0x37);
    keymap->insert(0x40, 0x38);
    keymap->insert(0x41, 0x39);
    keymap->insert(0x42, 0x3a);
    keymap->insert(0x43, 0x3b);
    keymap->insert(0x44, 0x3c);
    keymap->insert(0x45, 0x3d);
    keymap->insert(0x46, 0x3e);
    keymap->insert(0x47, 0x3f);
    keymap->insert(0x48, 0x40);
    keymap->insert(0x49, 0x41);
    keymap->insert(0x4a, 0x42);
    keymap->insert(0x4b, 0x43);
    keymap->insert(0x4c, 0x44);
    keymap->insert(0x4d, 0x45);
    keymap->insert(0x4e, 0x46);
    keymap->insert(0x4f, 0x47);
    keymap->insert(0x50, 0x48);
    keymap->insert(0x51, 0x49);
    keymap->insert(0x52, 0x4a);
    keymap->insert(0x53, 0x4b);
    keymap->insert(0x54, 0x4c);
    keymap->insert(0x55, 0x4d);
    keymap->insert(0x56, 0x4e);
    keymap->insert(0x57, 0x4f);
    keymap->insert(0x58, 0x50);
    keymap->insert(0x59, 0x51);
    keymap->insert(0x5a, 0x52);
    keymap->insert(0x5b, 0x53);
    keymap->insert(0x5c, 0x54);
    keymap->insert(0x5d, 0x76);
    keymap->insert(0x5e, 0x56);
    keymap->insert(0x5f, 0x57);
    keymap->insert(0x60, 0x58);
    keymap->insert(0x61, 0x73);
    keymap->insert(0x62, 0x78);
    keymap->insert(0x63, 0x77);
    keymap->insert(0x64, 0x79);
    keymap->insert(0x65, 0x70);
    keymap->insert(0x66, 0x7b);
    keymap->insert(0x67, 0x5c);
    keymap->insert(0x68, 0x11c);
    keymap->insert(0x69, 0x11d);
    keymap->insert(0x6a, 0x135);
    keymap->insert(0x6b, 0x54);
    keymap->insert(0x6c, 0x138);
    keymap->insert(0x6d, 0x5b);
    keymap->insert(0x6e, 0x147);
    keymap->insert(0x6f, 0x148);
    keymap->insert(0x70, 0x149);
    keymap->insert(0x71, 0x14b);
    keymap->insert(0x72, 0x14d);
    keymap->insert(0x73, 0x14f);
    keymap->insert(0x74, 0x150);
    keymap->insert(0x75, 0x151);
    keymap->insert(0x76, 0x152);
    keymap->insert(0x77, 0x153);
    keymap->insert(0x78, 0x16f);
    keymap->insert(0x79, 0x120);
    keymap->insert(0x7a, 0x12e);
    keymap->insert(0x7b, 0x130);
    keymap->insert(0x7c, 0x15e);
    keymap->insert(0x7d, 0x59);
    keymap->insert(0x7e, 0x14e);
    keymap->insert(0x7f, 0x146);
    keymap->insert(0x80, 0x10b);
    keymap->insert(0x81, 0x7e);
    keymap->insert(0x83, 0x10d);
    keymap->insert(0x84, 0x7d);
    keymap->insert(0x85, 0x15b);
    keymap->insert(0x86, 0x15c);
    keymap->insert(0x87, 0x15d);
    keymap->insert(0x88, 0x168);
    keymap->insert(0x89, 0x105);
    keymap->insert(0x8a, 0x106);
    keymap->insert(0x8b, 0x107);
    keymap->insert(0x8c, 0x10c);
    keymap->insert(0x8d, 0x178);
    keymap->insert(0x8e, 0x64);
    keymap->insert(0x8f, 0x65);
    keymap->insert(0x90, 0x141);
    keymap->insert(0x91, 0x13c);
    keymap->insert(0x92, 0x175);
    keymap->insert(0x93, 0x11e);
    keymap->insert(0x94, 0x121);
    keymap->insert(0x95, 0x66);
    keymap->insert(0x96, 0x15f);
    keymap->insert(0x97, 0x163);
    keymap->insert(0x98, 0x67);
    keymap->insert(0x99, 0x68);
    keymap->insert(0x9a, 0x69);
    keymap->insert(0x9b, 0x113);
    keymap->insert(0x9c, 0x11f);
    keymap->insert(0x9d, 0x117);
    keymap->insert(0x9e, 0x102);
    keymap->insert(0x9f, 0x6a);
    keymap->insert(0xa0, 0x112);
    keymap->insert(0xa1, 0x6b);
    keymap->insert(0xa2, 0x126);
    keymap->insert(0xa3, 0x16c);
    keymap->insert(0xa4, 0x166);
    keymap->insert(0xa5, 0x16b);
    keymap->insert(0xa6, 0x16a);
    keymap->insert(0xa7, 0x169);
    keymap->insert(0xa8, 0x123);
    keymap->insert(0xa9, 0x6c);
    keymap->insert(0xaa, 0x17d);
    keymap->insert(0xab, 0x119);
    keymap->insert(0xac, 0x122);
    keymap->insert(0xad, 0x110);
    keymap->insert(0xae, 0x124);
    keymap->insert(0xaf, 0x131);
    keymap->insert(0xb0, 0x118);
    keymap->insert(0xb1, 0x63);
    keymap->insert(0xb2, 0x70);
    keymap->insert(0xb3, 0x101);
    keymap->insert(0xb4, 0x132);
    keymap->insert(0xb5, 0x167);
    keymap->insert(0xb6, 0x71);
    keymap->insert(0xb7, 0x72);
    keymap->insert(0xb8, 0x108);
    keymap->insert(0xb9, 0x75);
    keymap->insert(0xba, 0x10f);
    keymap->insert(0xbb, 0x176);
    keymap->insert(0xbc, 0x17b);
    keymap->insert(0xbd, 0x109);
    keymap->insert(0xbe, 0x10a);
    keymap->insert(0xbf, 0x5d);
    keymap->insert(0xc0, 0x5e);
    keymap->insert(0xc1, 0x5f);
    keymap->insert(0xc2, 0x55);
    keymap->insert(0xc3, 0x103);
    keymap->insert(0xc4, 0x177);
    keymap->insert(0xc5, 0x104);
    keymap->insert(0xc6, 0x5a);
    keymap->insert(0xc7, 0x74);
    keymap->insert(0xc8, 0x179);
    keymap->insert(0xc9, 0x6d);
    keymap->insert(0xca, 0x6f);
    keymap->insert(0xcb, 0x115);
    keymap->insert(0xcc, 0x116);
    keymap->insert(0xcd, 0x11a);
    keymap->insert(0xce, 0x11b);
    keymap->insert(0xcf, 0x127);
    keymap->insert(0xd0, 0x128);
    keymap->insert(0xd1, 0x129);
    keymap->insert(0xd2, 0x12b);
    keymap->insert(0xd3, 0x12c);
    keymap->insert(0xd4, 0x12d);
    keymap->insert(0xd5, 0x125);
    keymap->insert(0xd6, 0x12f);
    keymap->insert(0xd7, 0x133);
    keymap->insert(0xd8, 0x134);
    keymap->insert(0xd9, 0x136);
    keymap->insert(0xda, 0x139);
    keymap->insert(0xdb, 0x13a);
    keymap->insert(0xdc, 0x13b);
    keymap->insert(0xdd, 0x13d);
    keymap->insert(0xde, 0x13e);
    keymap->insert(0xdf, 0x13f);
    keymap->insert(0xe0, 0x140);
    keymap->insert(0xe1, 0x165);
    keymap->insert(0xe2, 0x142);
    keymap->insert(0xe3, 0x143);
    keymap->insert(0xe4, 0x144);
    keymap->insert(0xe5, 0x145);
    keymap->insert(0xe6, 0x114);
    keymap->insert(0xe7, 0x14a);
    keymap->insert(0xe8, 0x14c);
    keymap->insert(0xe9, 0x154);
    keymap->insert(0xea, 0x16d);
    keymap->insert(0xeb, 0x156);
    keymap->insert(0xec, 0x157);
    keymap->insert(0xed, 0x158);
    keymap->insert(0xee, 0x159);
    keymap->insert(0xef, 0x15a);
    keymap->insert(0xf0, 0x164);
    keymap->insert(0xf1, 0x10e);
    keymap->insert(0xf2, 0x155);
    keymap->insert(0xf3, 0x170);
    keymap->insert(0xf4, 0x171);
    keymap->insert(0xf5, 0x172);
    keymap->insert(0xf6, 0x173);
    keymap->insert(0xf7, 0x174);
    return keymap;
}
//文件传输

void SpiceQt::startFileTransfer(const QStringList &sourceFilePaths) {
    if (!mainChannel) {
            qWarning() << "Main channel is not initialized.";
            return;
        }

        qDebug() << "Starting file transfer for multiple files:" << sourceFilePaths;

        if (!agentConnected) {
            qWarning() << "Agent is not connected. File transfer may fail.";
            return;
        }

        QList<GFile *> files;
        for (const QString &sourceFilePath : sourceFilePaths) {
            GFile *file = g_file_new_for_path(sourceFilePath.toUtf8().constData());
            if (file) {
                files.append(file);
            } else {
                qWarning() << "Failed to create GFile for path:" << sourceFilePath;
            }
        }

        // 将 GFile* 列表转换为 GFile** 数组
        GFile **fileArray = new GFile*[files.size() + 1];  // 多一个 NULL 结束
        for (int i = 0; i < files.size(); ++i) {
            fileArray[i] = files.at(i);
        }
        fileArray[files.size()] = nullptr;  // NULL 终止符

        // 调用异步文件传输函数
        spice_main_file_copy_async(
            mainChannel,
            fileArray,                     // GFile 数组
            G_FILE_COPY_NONE,              // GFileCopyFlags
            nullptr,                       // 可取消对象 (GCancellable)
            onFileTransferProgress,        // 进度回调
            this,                          // 传递当前实例
            onFileTransferFinished,        // 完成回调
            this                           // 传递当前实例
        );

        // 清理
        for (GFile *file : files) {
            g_object_unref(file);
        }
        delete[] fileArray;
}

// 文件传输进度回调
void SpiceQt::onFileTransferProgress(goffset current_num_bytes, goffset total_num_bytes, gpointer user_data) {
    SpiceQt *self = static_cast<SpiceQt *>(user_data);
    double progress = (double)current_num_bytes / (double)total_num_bytes * 100;
    qDebug() << "File transfer progress:" << progress << "% (" << current_num_bytes << "/" << total_num_bytes << " bytes)";

    // 触发进度信号
    Q_EMIT self->fileTransferProgress(progress);
}

// 文件传输完成回调
void SpiceQt::onFileTransferFinished(GObject *source_object, GAsyncResult *res, gpointer user_data) {
    SpiceQt *self = static_cast<SpiceQt *>(user_data);
    GError *error = nullptr;

    if (spice_main_file_copy_finish(SPICE_MAIN_CHANNEL(source_object), res, &error)) {
        qDebug() << "File transfer finished successfully!";
        //触发完成信号
        Q_EMIT self->fileTransferCompleted();
    } else {
        qWarning() << "File transfer failed: " << error->message;
        g_error_free(error);
    }
}

void SpiceQt::cancelFileTransfer() {
    if (fileTransferTask) {
        spice_file_transfer_task_cancel(fileTransferTask);  // 取消文件传输
        progressTimer->stop();  // 停止进度更新的定时器

        // 触发文件传输取消信号
        Q_EMIT fileTransferCancelled();
        qDebug() << "File transfer cancelled.";
    } else {
        qWarning() << "No active file transfer to cancel.";
    }
}


