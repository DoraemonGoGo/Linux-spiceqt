#include "QHBoxLayout"
#include "QMouseEvent"
#include <QPushButton>
#include <QListWidget>
#include "spicemainwindow.h"
#include "ui_spicemainwindow.h"
#include <spice-client.h>
#include "spiceqt.h"
#include "spice-widget.h"
#include "spice-widget-priv.h"
#include "../common/mem.h"
#include "../common/messages.h"
#include "../common/marshaller.h"
#include "QTimer"


SpiceMainWindow::SpiceMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpiceMainWindow)
//    resizeTimer(new QTimer(this))
{
    ui->setupUi(this);

    //设置instance的嵌入和布局
//    QHBoxLayout *layout = new QHBoxLayout();
//    spicewindow = new SpiceQt();
//    QWidget *central = new QWidget();
//    setCentralWidget(central);
//    spicewindow = SpiceQt::getSpice();

    spicewindow = SpiceQt::getSpice();

    ui->layout->addWidget(spicewindow);
//    central->setLayout(layout);


    spicewindow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->actionToolBar->setChecked(true);
    ui->actionStatusBar->setChecked(true);

    // 使用定时器定期更新显示窗口
//    connect(resizeTimer, &QTimer::timeout, this, &SpiceMainWindow::handleResizeTimeout);
//    resizeTimer->setSingleShot(true);

    qDebug()<<"------------------------------------------------------";
    //设置状态栏获取鼠标指向位置
    auto acts = ui->menubar->actions();
    for (auto i : acts)
    {
        auto menu = i->menu();

        QList<QAction *> actions;

        // 当没有菜单时
        if (!menu)
        {
            actions.push_back(i);
        }
        else
        {
            actions = menu->actions();
        }
        for (auto a : actions)
        {
            QWidget *w;
            if (a->isSeparator())
            {

                auto line = new QWidget();
                line->setFixedWidth(1);
                line->setStyleSheet("background:rgb(177,177,177)");
                w = line;
            }
            else
            {
                //QWidget::addAction(a);
                //this->addAction(a)

                a->setToolTip(a->text());
                a->setStatusTip(a->text());

            }
        }
    }

}

SpiceMainWindow::~SpiceMainWindow()
{
    delete ui;
}

void SpiceMainWindow::showspice(QString ip, QString port)
{
    qDebug() << ip << "  ,  " << port << endl;
    qDebug() << spicewindow;
//    int height = widget1->height();
//    int width = widget1->width();
    int spiceheight = spicewindow->height();
    int spicewidth = spicewindow->width();
//    qDebug() << height << " , " << width << endl;
//    qDebug() << spiceheight << " , " << spicewidth << endl;
//    spicewindow->show();
    spicewindow->connectToGuest(ip, port);
}

//主窗口键盘事件重写，全屏后识别退出
void SpiceMainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape && isFullScreen())
    {
        ui->toolBar->setVisible(true);
        ui->statusBar->setVisible(true);
        ui->menubar->setVisible(true);
        showNormal();
    }
}

void SpiceMainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    QRect contentRect = this->layout()->geometry();
    int newWidth = contentRect.width();
    int newHeight = contentRect.height();
    spicewindow->resizeEvent(event);
}

//设置工具栏显示
void SpiceMainWindow::on_actionToolBar_toggled(bool arg1)
{
    ui->toolBar->setVisible(ui->actionToolBar->isChecked());
}

//设置状态栏显示
void SpiceMainWindow::on_actionStatusBar_toggled(bool arg1)
{
    ui->statusBar->setVisible(ui->actionStatusBar->isChecked());
}

//菜单中虚拟机全屏显示
void SpiceMainWindow::fullscreen(bool full)
{
;
    ui->toolBar->setVisible(!full);
    ui->statusBar->setVisible(!full);
    ui->menubar->setVisible(!full);
    ui->actionFullscreen->setShortcut(  full ? QKeySequence("Esc") : QKeySequence("Ctrl+F"));

    static bool maximized = false;// 记录当前状态
    if ( full )
    {
        maximized = isFullScreen();
    }
    else if ( maximized && isFullScreen() )
    {
        return;
    }

    if ( full && !isFullScreen() || !full && isFullScreen() )
    {
        if (isFullScreen())
        {
            showNormal();
        }
        else
            showFullScreen();
    }
}

void SpiceMainWindow::on_actionFullscreen_triggered(bool checked)
{
    this->addAction(ui->actionFullscreen);
    fullscreen(checked);
}

//工具栏中全屏操作
void SpiceMainWindow::on_actiontoolfullscreen_triggered()
{
   auto full = isFullScreen();
   ui->toolBar->setVisible(full);
   ui->statusBar->setVisible(full);
   ui->menubar->setVisible(full);

   if(full)
   {
       showNormal();
   }
   else {
       showFullScreen();
    }
}

//工具栏Resize to按钮设置窗口大小
void SpiceMainWindow::on_actionResize_to_triggered()
{
    resdia = new ResDialog(this);
    resdia->show();
}

//工具栏close按钮关闭主窗口
void SpiceMainWindow::on_actiontoolclose_triggered()
{
    this->close();
}

//void SpiceMainWindow::usb_connect_callback(GObject *source_object, GAsyncResult *res, gpointer user_data) {
//    GError *error = nullptr;

//    // 将 source_object 转换为 SpiceUsbDeviceManager
//    SpiceUsbDeviceManager *manager = SPICE_USB_DEVICE_MANAGER(source_object);

//    // 检查异步操作的结果
//    gboolean success = spice_usb_device_manager_connect_device_finish(manager, res, &error);

//    if (!success) {
//        // 处理错误
//        qWarning() << "Failed to connect USB device:" << error->message;
//        g_error_free(error);
//    } else {
//        // 连接成功
//        qDebug() << "USB device connected successfully.";
//    }
//}

//void SpiceMainWindow::usb_disconnect_callback(GObject *source_object, GAsyncResult *res, gpointer user_data) {
//    GError *error = nullptr;
//    SpiceUsbDeviceManager *manager = SPICE_USB_DEVICE_MANAGER(source_object);
//    gboolean success = spice_usb_device_manager_disconnect_device_finish(manager, res, &error);

//    SpiceMainWindow *mainWindow = static_cast<SpiceMainWindow*>(user_data);

//    if (!success) {
//        qWarning() << "Failed to disconnect USB device:" << error->message;
//        g_error_free(error);
//    } else {
//        qDebug() << "USB device disconnected successfully.";
//    }
//}

//void SpiceMainWindow::onUsbDeviceAdded(SpiceUsbDevice *device)
//{
//    gchar *format = "%s %s %s at %d-%d";
//    qDebug() << "USB device added:" << spice_usb_device_get_description(device, format);

//    if (isDeviceAllowed(device)) {
//        // 连接 USB 设备
//        spicewindow = SpiceQt::getSpice();
//        SpiceSession *session = spicewindow->getSession();
//        SpiceUsbDeviceManager *usb_manager = spice_usb_device_manager_get(session, nullptr);
//        spice_usb_device_manager_connect_device_async(usb_manager, device, nullptr, usb_connect_callback, this);
//    } else {
//        qWarning() << "USB device is not allowed to be redirected.";
//    }
//}

//void SpiceMainWindow::onUsbDeviceRemoved(SpiceUsbDevice *device) {
//    gchar *format = "%s %s %s at %d-%d";
//    qDebug() << "USB device removed:" << spice_usb_device_get_description(device, format);
//    // 断开 USB 设备
//    spicewindow = SpiceQt::getSpice();
//    SpiceSession *session = spicewindow->getSession();
//    SpiceUsbDeviceManager *usb_manager = spice_usb_device_manager_get(session, nullptr);
//    spice_usb_device_manager_disconnect_device_async(usb_manager, device, nullptr, usb_disconnect_callback, this);;
//}

//bool SpiceMainWindow::isDeviceAllowed(SpiceUsbDevice *device)
//{
//    struct libusb_device *libusb_dev = (struct libusb_device *)spice_usb_device_get_libusb_device(device);
//    if (!libusb_dev) {
//        qWarning() << "Failed to get libusb device.";
//        return false;
//    }

//    struct libusb_device_descriptor desc;
//    int ret = libusb_get_device_descriptor(libusb_dev, &desc);
//    if (ret != LIBUSB_SUCCESS) {
//        qWarning() << "Failed to get device descriptor:" << libusb_error_name(ret);
//        return false;
//    }

//    QString device_id = QString::number(desc.idVendor, 16).rightJustified(4, '0') + ":" + QString::number(desc.idProduct, 16).rightJustified(4, '0');

//    if (blackList.contains(device_id))
//    {
//        return false;
//    }
//    if (whiteList.contains(device_id))
//    {
//        return true;
//    }

//    // 如果设备不在黑名单且在白名单中，则允许重定向
//    return true;
//}

//void SpiceMainWindow::on_usb_device_added(SpiceUsbDeviceManager *manager, SpiceUsbDevice *device, gpointer user_data) {
//    SpiceMainWindow *mainWindow = static_cast<SpiceMainWindow*>(user_data);
//    mainWindow->onUsbDeviceAdded(device);
//}

//void SpiceMainWindow::on_usb_device_removed(SpiceUsbDeviceManager *manager, SpiceUsbDevice *device, gpointer user_data) {
//    SpiceMainWindow *mainWindow = static_cast<SpiceMainWindow*>(user_data);
//    mainWindow->onUsbDeviceRemoved(device);
//}

//void SpiceMainWindow::initializeUsbRedirection()
//{
//    spicewindow = SpiceQt::getSpice();
//    SpiceSession *session = spicewindow->getSession();

//    // 配置 USB 设备管理
//    SpiceUsbDeviceManager *usb_manager = spice_usb_device_manager_get(session, nullptr);
//    g_signal_connect(usb_manager, "device-added", G_CALLBACK(on_usb_device_added), this);
//    g_signal_connect(usb_manager, "device-removed", G_CALLBACK(on_usb_device_removed), this);
//    qDebug()<<"USB初始化完成！";
//}

void SpiceMainWindow::on_action_usbredir_triggered()
{
//    spicewindow = SpiceQt::getSpice();
    SpiceSession *session = spicewindow->getSession();
    SpiceUsbDeviceManager *usb_device_manager = spice_usb_device_manager_get(session, NULL);
    GPtrArray *DeviceList = spice_usb_device_manager_get_devices(usb_device_manager);
    QListWidget *listWidget = new QListWidget;
    if(DeviceList)
    {
        // 将 GPtrArray 中的字符串添加到 QListWidget
        for (guint i = 0; i < DeviceList->len; i++) {
            SpiceUsbDevice *device = (SpiceUsbDevice *)g_ptr_array_index(DeviceList, i);
            gchar *format = "%s %s %s at %d-%d";
            gchar *description = spice_usb_device_get_description(device, format);
            qDebug() << description;
            listWidget->addItem(description);
            g_free(description); // 释放描述字符串
        }
        qDebug()<<"length is"<<DeviceList->len;
        // 显示窗口
        listWidget->setWindowTitle("USB Redirection List");
        listWidget->resize(400, 300);
        listWidget->show();
        // 清理 GPtrArray
        g_ptr_array_free(DeviceList, TRUE);
    }
    else {
        qDebug()<<"USB Device Manager is NULL";
    }
}

void SpiceMainWindow::updateSpiceWindow()
{
    if (spicewindow)
    {
        spicewindow->update();
    }
}
