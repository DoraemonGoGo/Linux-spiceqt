#ifndef SPICEMAINWINDOW_H
#define SPICEMAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include <resdialog.h>
#include <spice-client.h>
#include <spice-channel.h>
#include <libusb.h>

namespace Ui {
class SpiceMainWindow;
}

class ResizeTo;
class SpiceQt;


class SpiceMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpiceMainWindow(QWidget *parent = nullptr);
    ~SpiceMainWindow();
    void showspice(QString ip, QString port);
    void fullscreen(bool full);
    void initializeUsbRedirection();

protected:
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);

private Q_SLOTS:
    void on_actionToolBar_toggled(bool arg1);
    void on_actionStatusBar_toggled(bool arg1);
    void on_actionFullscreen_triggered(bool checked);
    void on_actiontoolfullscreen_triggered();
    void on_actionResize_to_triggered();
    void on_actiontoolclose_triggered();
    void on_action_usbredir_triggered();
    void updateSpiceWindow();
//    void handleResizeTimeout();
//    void onUsbDeviceAdded(SpiceUsbDevice *device);
//    void onUsbDeviceRemoved(SpiceUsbDevice *device);

//    void on_actiontoolpaste_triggered();

private:
    Ui::SpiceMainWindow *ui;
    SpiceQt *spicewindow;
    ResizeTo *res;
    ResDialog *resdia;
    QSet<QString> whiteList;
    QSet<QString> blackList;
//    QTimer *resizeTimer; // 新增 QTimer 成员变量
//    static void on_usb_device_added(SpiceUsbDeviceManager *manager, SpiceUsbDevice *device, gpointer user_data);
//    static void on_usb_device_removed(SpiceUsbDeviceManager *manager, SpiceUsbDevice *device, gpointer user_data);
//    static void usb_connect_callback(GObject *source_object, GAsyncResult *res, gpointer user_data);
//    static void usb_disconnect_callback(GObject *source_object, GAsyncResult *res, gpointer user_data);
//    bool isDeviceAllowed(SpiceUsbDevice *device);
};

#endif // SPICEMAINWINDOW_H
