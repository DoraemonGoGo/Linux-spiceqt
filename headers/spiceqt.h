#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QAudioOutput>
#include <QAudioInput>
#include <QBuffer>
#include <spice/vd_agent.h>
//文件传输
#include <QTimer>
#include <QMessageBox>
#include <gio/gio.h>                // GFile, GError 相关
#include <spice-client.h>           // spice_main_file_copy_async() 和其他主通道函数
#include <spice-channel.h>          // SpiceMainChannel 类型
#include <QProgressBar>

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
//#include <X11/XKBlib.h>
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
#include <spice-audio.h>
};

#include "spice-widget.h"

#define MAX_MONITORS 2 // 定义最大显示器数量

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
    void redirect_usb_device(const QStringList &devices);
    void disconnectUsbDevices(const QStringList &devices);
//    void redirectUsbDevice(gchar *device_description);
//    void stopUsbRedirect(gchar *device_description);

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


    //多显示器功能
//    void configureMonitors();
    void initializeMultiMonitor();
    int detectDisplays();
    void enableMonitor(int monitorId);
    void initializeWithSession(SpiceSession *session, int monitorId);
//    void createDisplayWindow(int displayId);

    void updateResolution(int width, int height);
    //文件传输
    void startFileTransfer(const QStringList &sourceFilePaths);
    // 文件传输进度回调
    static void onFileTransferProgress(goffset current_num_bytes, goffset total_num_bytes, gpointer user_data);
    // 文件传输完成回调s
    static void onFileTransferFinished(GObject *source_object, GAsyncResult *res, gpointer user_data);
    void handleFileTransferFinished(SpiceFileTransferTask *task, GError *error);

    // 获取指定 channel-id 的显示器
    SpiceDisplay* getSpiceDisplayById(int channel_id);
    // 添加新的显示器
    void addSpiceDisplay(SpiceDisplay* display, int channel_id);
    QSet<QString> getRedirectedDevices() const { return redirectedDevices; }

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

public Q_SLOTS:
    void onClipboardDataChanged();
    //文件传输
    //void updateFileTransferProgress(SpiceFileTransferTask *task);  // 用于更新进度
    void cancelFileTransfer();
    void onResizeTimeout();
//    void emitUsbDeviceAdded(const QString &description);   // 声明为槽函数


Q_SIGNALS:
    void imageSize(int, int);
    void resolutionChanged(int width, int height);
    //文件传输
    void fileTransferProgress(double progress);  // 文件传输进度信号
    void fileTransferCompleted();  // 文件传输完成信号
    void fileTransferCancelled();  //取消传输信号
    //USB设备添加和删除
    void usbDeviceAdded(const QString &description);
    void usbDeviceRemoved(const QString &description);

private:
    static QMap<int, int> * getKeymap();
    void prepareMouseData();
//    static SpiceQt *instance;
    SpiceSession * SGsession;
    SpiceDisplay * display;
    SpiceDisplayPrivate * d;
    SpiceAudio   * audio;
    SpiceMainChannel *mainChannel;
    int            monitor_id;//显示器id
    QList<SpiceDisplayMonitorConfig> monitorConfigs;
    SpiceDisplayChannel *display_channel;//显示通道
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
    //文件传输
    SpiceFileTransferTask *fileTransferTask;
    QTimer *progressTimer;  // 新增成员变量：用于定期检查传输进度
    QStringList pendingFileTransfers;  // 用于存储待传输的文件列表
    //QProgressBar *progressBar; //用于显示进度

    bool sizeAdjusted; // 标志位，判断是否已调整大小
    bool imageUpdateLock; // 用于控制图像更新的锁
    QTimer *resizeTimer;
    bool resizingInProgress = false;
    QImage tempImg;
    // 添加一个映射来管理每个显示通道的图像
    QMap<int, QImage> displayImages;
    std::map<int, SpiceDisplay*> displays;  // 存储 channel-id 和 SpiceDisplay 的映射

    QSet<QString> redirectedDevices; // 追踪已重定向的设备

};

#endif SPICEQT_H
