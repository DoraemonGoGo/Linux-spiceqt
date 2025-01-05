#ifndef SPICEMAINWINDOW_H
#define SPICEMAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
//#include <resdialog.h>
#include <spice-client.h>
#include <spice-channel.h>
#include <libusb.h>
#include <QListWidget>

namespace Ui {
class SpiceMainWindow;
}

class ResizeTo;
class SpiceQt;
class MenuWindow;
class SmallMenuWidget;
//文件传输
class TransferWindow;

class SpiceMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpiceMainWindow(QWidget *parent = nullptr);
    ~SpiceMainWindow();

    void showspice(QString ip, QString port);
    void fullscreen(bool full);
    void initializeUsbRedirection();
    void NotFullScreen();
    void onResolutionChanged(int width, int height);
    void createDisplayWindow(int displayId);
    void addUsbDeviceToList(const QString &description);
    void removeUsbDeviceFromList(const QString &description);
    void updateUsbDeviceList(); // 声明一个私有函数用于更新 USB 列表

protected:
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

public Q_SLOTS:
    void on_actionToolBar_toggled(bool arg1);
    void on_actionFullscreen_triggered(bool checked);
    void on_actiontoolfullscreen_triggered();
    void on_actiontoolclose_triggered();
    void updateSpiceWindow();
    void handleShortcutAction();

    void on_action_1_triggered();
    //文件传输
    void on_actionFile_input_triggered(); // 新增的槽函数
    void on_actionmulti_screen_triggered();
    void addDisplay_triggered();
    //USB设备添加和删除
    void onUsbDeviceAdded(const QString &description);
    void onUsbDeviceRemoved(const QString &description);
    void on_action_usbredir_triggered();
    void disconnectUsbDevices(const QStringList &devices); // 新增槽函数

public:
    SpiceQt *spicewindow;  

private:
    Ui::SpiceMainWindow *ui;
//    SpiceQt *spicewindow;
    ResizeTo *res;
//    ResDialog *resdia;
    QSet<QString> whiteList;
    QSet<QString> blackList;
//    MenuWindow *SmallMenu;
    SmallMenuWidget *smallMenu;
    QListWidget *usbListWidget; // 添加 USB 列表窗口
    QSet<QString> currentUsbDevices;
    QList<QMainWindow *> monitorWindows;  // 用于存储多个显示窗口
    //文件传输
    TransferWindow *transferWindow;
};

#endif // SPICEMAINWINDOW_H
