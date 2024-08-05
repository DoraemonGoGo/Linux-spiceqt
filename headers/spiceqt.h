#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QAudioOutput>
#include <QAudioInput>
#include <QBuffer>
#include <spice/vd_agent.h>
extern "C" {
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <glib-object.h>
#include <spice-client.h>
#include <spice-session.h>
#include <channel-main.h>
#include <channel-display.h>
#include <channel-inputs.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <spice-audio.h>
};

#include "spice-widget.h"


#ifndef SPICEQT_H
#define SPICEQT_H

class SpiceQt : public QWidget
{
    Q_OBJECT
public:
    explicit SpiceQt(QWidget *parent = NULL);
    ~SpiceQt() override;
//    static SpiceQt *getSpice(QWidget *parent = NULL);
    SpiceSession *getSession();
    SpiceDisplay* getDisplay() const;
    SpiceDisplayPrivate* getSpiceDisplayPrivate();
    void initializeCursor(SpiceDisplayPrivate *d);
    SpiceMainChannel *getMainChannel(){return mainChannel; }
    QSize spiceSize() { return QSize(dataWidth, dataHeight); }
    void connectToGuest(const QString &host, const QString &port);
    void disconnectFromGuest();
    void clearImage();
//    void initialize_usb_redirection(SpiceSession *session);
    void setMainChannel(SpiceMainChannel* channel) { mainChannel = channel; }
    SpiceAudio *spiceAudioGLib() { return audio; }
    void setSpiceAudioGLib(SpiceAudio *sa);
    SpiceDisplay *spiceDisplayGLib() { return display; }
    void setSpiceDisplayGLib(SpiceDisplay *sd);
    void updateImage(uchar *data, int x, int y, int width, int height);
    void settingsChanged(int width, int height, int bpp);
    void setKbdModifiers(int m);
    void spiceResize(int w, int h);
    void resizeEvent(QResizeEvent *event) override;
    //发送快捷键
    void sendShortcut(const QString &shortcut);
//    int convertKeyStringToQtKey(const QString &keyString);

    void showCursor(bool visible)
    {
//        if (visible)
//            setCursor(Qt::ArrowCursor);
//        else
//            setCursor(Qt::BlankCursor);
        cursorVisible = visible;
    }
    bool isCursorVisible() const {
        return cursorVisible;
    }

    int getCursorX() const {
        return cursorX;
    }

    int getCursorY() const {
        return cursorY;
    }
    bool isWindowFocused() {
        QWindow *window = windowHandle();
        return window && window->isActive();
    }
    void updateCursor(int x, int y);
    bool isCursorChannelInitialized();
    quint32 getKeyboardLockModifiers();
    void setAgentConnected(bool connected) { agentConnected = connected; }
    bool getAgentConnected() { return agentConnected; }

    bool isRunning(){return true;}
    void redirect_usb_device();
    void redirectUsbDevice(gchar *device_description);
    void stopUsbRedirect(gchar *device_description);

    void request_clipboard_data(SpiceMainChannel *channel);
    gboolean handleClipboardSelectionGrab(SpiceMainChannel *channel, guint selection, gpointer types, guint ntypes);
    gboolean handleClipboardSelectionRequest(SpiceMainChannel *channel, guint selection, guint type);
    void handleClipboardSelectionRelease(guint selection);
    void handleClipboardSelection(guint selection, guint type, gpointer data, guint size);

    void initializePlaybackChannel(SpicePlaybackChannel *channel);
//    void initializeRecordChannel(SpiceRecordChannel *channel);
    //公共方法获取私有音频变量
    void writeAudioOutput(const char* data, int size);
    void startAudioOutput(const QAudioFormat &format);
    void stopAudioOutput();
    void startAudioInput(const QAudioFormat &format);
    void stopAudioInput();
    void sendRecordedData();

protected:
    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    bool x11Event(XEvent *event);

//    bool eventFilter(QObject *obj, QEvent *event) override;

public Q_SLOTS:
      void onClipboardDataChanged();


Q_SIGNALS:
    void imageSize(int, int);

private:
    static QMap<int, int> * getKeymap();
    void prepareMouseData();
//    static SpiceQt *instance;
    SpiceSession * SGsession;
    SpiceDisplay * display;
    SpiceDisplayPrivate * d;
    SpiceAudio   * audio;
    SpiceMainChannel *mainChannel;
    SpiceUsbDeviceManager *usb_device_manager;
    uchar        * buf;
    QImage         img;
    int            dataWidth;
    int            dataHeight;
    double         rate;
    bool           scrollLock;
    bool           numLock;
    bool           capsLock;
    bool           agentConnected;
    QTimer resizeTimer;    // 用于延迟更新的定时器
    QImage tempImg;        // 拉伸过程中使用的临时图像
    bool resizing = false; // 标识是否正在拉伸窗口

    static QMap<int, int>* keymap;

    bool           cursorVisible;
    int            cursorX;
    int            cursorY;

    SpicePlaybackChannel *playback_channel;
    SpiceRecordChannel *record_channel;
    QAudioOutput *audioOutput;
    QIODevice *audioOutputDevice;
    QAudioInput *audioInput;
    QBuffer *audioInputBuffer;
};

#endif SPICEQT_H
