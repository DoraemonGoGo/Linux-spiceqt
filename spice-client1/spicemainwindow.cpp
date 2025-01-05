#include "QHBoxLayout"
#include "QMouseEvent"
#include <QPushButton>
#include <QDesktopWidget>
#include <QCheckBox>
#include "spicemainwindow.h"
#include "ui_spicemainwindow.h"
#include <smallmenuwidget.h>
#include <spice-client.h>
#include "spiceqt.h"
#include "spice-widget.h"
#include "spice-widget-priv.h"
#include "../common/mem.h"
#include "../common/messages.h"
#include "../common/marshaller.h"
#include "QTimer"
//文件传输
#include "transferwindow.h"
#include "usbredirdialog.h"


SpiceMainWindow::SpiceMainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::SpiceMainWindow),
    spicewindow(new SpiceQt(this)),
    usbListWidget(new QListWidget(nullptr)) // 初始化 USB 列表窗口
{
    ui->setupUi(this);

    // 连接 SpiceQt 的分辨率变化信号到窗口调整槽
    connect(spicewindow, &SpiceQt::resolutionChanged, this, &SpiceMainWindow::onResolutionChanged);

    smallMenu = new SmallMenuWidget(this);
    smallMenu->setAttribute(Qt::WA_NoSystemBackground, true);

    setMouseTracking(true);  // 启用主窗口的鼠标跟踪
    centralWidget()->setMouseTracking(true);  // 启用中心组件的鼠标跟踪

    // 将刘海窗口移动到屏幕顶部中间，并隐藏
    smallMenu->move((QApplication::desktop()->width() - smallMenu->width()) / 2, 0);
    smallMenu->hide();

    ui->layout->addWidget(spicewindow);
//    setCentralWidget(spicewindow);
//    central->setLayout(layout);


    spicewindow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->actionToolBar->setChecked(true);
//    ui->actionStatusBar->setChecked(true);

    //将快捷键菜单项连接到处理函数
    QList<QAction*> actions = ui->menuInput->actions();
    for (QAction* action : actions) {
        connect(action, &QAction::triggered, this, &SpiceMainWindow::handleShortcutAction);
    }
    // 连接文件传输功能
    connect(ui->actionFile_input, &QAction::triggered, this, &SpiceMainWindow::on_actionFile_input_triggered);

    connect(ui->actionaddDisplay, &QAction::triggered, this, &SpiceMainWindow::addDisplay_triggered);

    // 初始化 USB 列表窗口
    usbListWidget->setWindowTitle("USB Redirection List");
    usbListWidget->resize(400, 300);
    usbListWidget->hide(); // 初始隐藏

    // 连接 SpiceQt 的 USB 设备添加和移除信号到槽函数
    connect(spicewindow, &SpiceQt::usbDeviceAdded, this, &SpiceMainWindow::onUsbDeviceAdded);
    connect(spicewindow, &SpiceQt::usbDeviceRemoved, this, &SpiceMainWindow::onUsbDeviceRemoved);
    // 初始化 USB 设备列表
//    updateUsbDeviceList();
}

void SpiceMainWindow::onResolutionChanged(int width, int height) {
    // 调整主窗口大小
    this->resize(width, height);
    qDebug() << "主窗口大小调整为: " << width << "x" << height;
}

void SpiceMainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (!isFullScreen()) {
        // 如果不是全屏模式，直接返回，不做任何操作
        return;
    }

    int mouseX = event->globalX();
    int mouseY = event->globalY();
    qDebug()<<mouseX<<"  "<<mouseY;
    // 获取屏幕宽度
    int screenWidth = QApplication::desktop()->screenGeometry(this).width();
    int startX = (screenWidth - 300) / 2;  // 菜单宽度假设为300像素
    int endX = startX + 300;
    qDebug()<<startX<<" "<<endX;
    // 检查鼠标是否在顶部中间区域
    if (mouseX >= startX && mouseX <= endX && mouseY <= 20) { // 顶部5像素内
        if (!smallMenu->isVisible()) {  // 如果菜单未显示
            smallMenu->move((screenWidth - smallMenu->width()) / 2, 0);
            smallMenu->show();  // 在鼠标位置显示菜单
        }
    }
    else {
        // 延迟隐藏菜单栏，给用户时间移动鼠标
        QTimer::singleShot(500, this, [this]() {
            if (smallMenu->isVisible()) {
                smallMenu->hide();
                qDebug() << "smallMenu hidden after delay";
            }
        });
       }
}

void SpiceMainWindow::handleShortcutAction()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;

    QString shortcut = action->objectName().remove("action");
    shortcut.replace("_", "+");

    qDebug() << "Shortcut clicked:" << shortcut;

    if (spicewindow) {
        spicewindow->sendShortcut(shortcut);
    }
}

SpiceMainWindow::~SpiceMainWindow()
{
    delete ui;

    // 确保在关闭窗口时断开连接并释放资源
    if (spicewindow) {
        spicewindow->disconnectFromGuest();
        delete spicewindow;
    }

    // 释放 USB 列表窗口
    if (usbListWidget) {
        delete usbListWidget;
    }
}

void SpiceMainWindow::closeEvent(QCloseEvent *event)
{
    // 确保在窗口关闭时断开虚拟机连接
    if (spicewindow) {
        spicewindow->disconnectFromGuest();
    }
    event->accept();
}

void SpiceMainWindow::showspice(QString ip, QString port)
{
    qDebug() << ip << "  ,  " << port << endl;
    qDebug() << spicewindow;
//    int height = widget1->height();
//    int width = widget1->width();
    setWindowTitle(QString("SpiceConnection - %1:%2").arg(ip).arg(port));
    int spiceheight = spicewindow->height();
    int spicewidth = spicewindow->width();
    spicewindow->show();
    spicewindow->connectToGuest(ip, port);
    resize(spicewidth, spiceheight);
}

//主窗口键盘事件重写，全屏后识别退出
void SpiceMainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape && isFullScreen())
    {
        ui->toolBar->setVisible(true);
//        ui->statusBar->setVisible(true);
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
    qDebug()<<"窗口大小改变！"<<":"<<newWidth<<","<<newHeight;

//    spicewindow->spiceResize(event->size().width(), event->size().height());
}

//设置工具栏显示
void SpiceMainWindow::on_actionToolBar_toggled(bool arg1)
{
    ui->toolBar->setVisible(ui->actionToolBar->isChecked());
}

//菜单中虚拟机全屏显示
void SpiceMainWindow::fullscreen(bool full)
{

    ui->toolBar->setVisible(!full);
//    ui->statusBar->setVisible(!full);
    ui->menubar->setVisible(!full);
    ui->actionFullscreen->setShortcut(  full ? QKeySequence("Esc") : QKeySequence("Ctrl+F"));

    static bool maximized = false;// 记录当前状态
    if (full) {
            // 记录是否最大化状态
            maximized = isMaximized();
            showFullScreen();
            // 将刘海窗口移动到屏幕顶部中间
            int screenWidth = QApplication::desktop()->screenGeometry(this).width();
            smallMenu->move((screenWidth - smallMenu->width()) / 2, 0);
            smallMenu->show();
        } else {
            if (maximized) {
                showMaximized();
            } else {
                showNormal();
            }
        }
    //在全屏状态下需要获取到窗口的大小和分辨率，然后调整显示窗口的大小
    // 确保窗口在进入全屏和退出全屏后调整大小
    QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    QRect contentRect = this->geometry();
    int newWidth = full ? screenWidth : contentRect.width();
    int newHeight = full ? screenHeight : contentRect.height();
    qDebug() << "New dimensions: " << newWidth << "x" << newHeight;

    // 调整spicewindow的大小
    if (spicewindow) {
        spicewindow->resize(newWidth, newHeight);
        spicewindow->spiceResize(newWidth, newHeight);
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
//   ui->statusBar->setVisible(full);
   ui->menubar->setVisible(full);

   if(full)
   {
       showNormal();
   }
   else {
       showFullScreen();
    }
}

void SpiceMainWindow::NotFullScreen()
{
    showNormal();
    ui->toolBar->setVisible(true);
 //   ui->statusBar->setVisible(full);
    ui->menubar->setVisible(true);
    if (smallMenu->isVisible()) {
        smallMenu->hide();
        qDebug() << "smallMenu hidden after delay";
    }
}

//工具栏close按钮关闭主窗口
void SpiceMainWindow::on_actiontoolclose_triggered()
{
    spicewindow->disconnectFromGuest();
}

void SpiceMainWindow::onUsbDeviceAdded(const QString &description)
{
    qDebug() << "USB Device Added:" << description;
    addUsbDeviceToList(description);
//    updateUsbDeviceList();
}

void SpiceMainWindow::onUsbDeviceRemoved(const QString &description)
{
    qDebug() << "USB Device Removed:" << description;
    removeUsbDeviceFromList(description);
//    updateUsbDeviceList();
}

void SpiceMainWindow::addUsbDeviceToList(const QString &description)
{
    if (!currentUsbDevices.contains(description)) {
        usbListWidget->addItem(description);
        currentUsbDevices.insert(description);
    }
}

void SpiceMainWindow::removeUsbDeviceFromList(const QString &description)
{
    if (currentUsbDevices.contains(description)) {
        QList<QListWidgetItem *> items = usbListWidget->findItems(description, Qt::MatchExactly);
        for (QListWidgetItem *item : items) {
            delete usbListWidget->takeItem(usbListWidget->row(item));
            currentUsbDevices.remove(description);
        }
    }
}

//void SpiceMainWindow::updateUsbDeviceList()
//{
//    // 清空现有的 USB 列表
//    usbListWidget->clear();
//    SpiceSession *session = spicewindow->getSession();
//    SpiceUsbDeviceManager *usb_device_manager = spice_usb_device_manager_get(session, NULL);
//    GPtrArray *DeviceList = spice_usb_device_manager_get_devices(usb_device_manager);
//    if(DeviceList)
//    {
//        // 将 GPtrArray 中的字符串添加到 QListWidget
//        for (guint i = 0; i < DeviceList->len; i++) {
//            SpiceUsbDevice *device = (SpiceUsbDevice *)g_ptr_array_index(DeviceList, i);
//            gchar *format = "%s %s %s at %d-%d";
//            gchar *description = spice_usb_device_get_description(device, format);
//            qDebug() << description;
//            usbListWidget->addItem(description);
//            currentUsbDevices.insert(description);
//            g_free(description); // 释放描述字符串
//        }
//        qDebug()<<"length is"<<DeviceList->len;

//        // 清理 GPtrArray
//        g_ptr_array_free(DeviceList, TRUE);
//    }
//    else {
//        qDebug()<<"USB Device Manager is NULL";
//    }
//    usbListWidget->setUpdatesEnabled(true);
//}

void SpiceMainWindow::updateUsbDeviceList()
{
    usbListWidget->setUpdatesEnabled(false);
    usbListWidget->clear();
    currentUsbDevices.clear();

    SpiceSession *session = spicewindow->getSession();
    if (!session) {
        qDebug() << "SpiceSession is NULL";
        QMessageBox::warning(this, tr("Error"), tr("Failed to retrieve Spice session."));
        usbListWidget->setUpdatesEnabled(true);
        return;
    }

    SpiceUsbDeviceManager *usb_device_manager = spice_usb_device_manager_get(session, NULL);
    if (!usb_device_manager) {
        qDebug() << "Failed to get SpiceUsbDeviceManager";
        QMessageBox::warning(this, tr("Error"), tr("Failed to retrieve USB Device Manager."));
        usbListWidget->setUpdatesEnabled(true);
        return;
    }

    GPtrArray *DeviceList = spice_usb_device_manager_get_devices(usb_device_manager);
    if(DeviceList)
    {
        const gchar *USB_DESCRIPTION_FORMAT = "%s %s %s at %d-%d";
        for (guint i = 0; i < DeviceList->len; i++) {
            SpiceUsbDevice *device = (SpiceUsbDevice *)g_ptr_array_index(DeviceList, i);
            gchar *description_c = spice_usb_device_get_description(device, USB_DESCRIPTION_FORMAT);
            if (description_c) {
                QString description = QString::fromUtf8(description_c);
                qDebug() << description;
                usbListWidget->addItem(description); // 使用成员变量
                currentUsbDevices.insert(description);
                g_free(description_c);
            } else {
                qDebug() << "Failed to get device description for device index:" << i;
                QMessageBox::warning(this, tr("Warning"), tr("Failed to retrieve description for a USB device."));
            }
        }
        qDebug() << "Total USB devices:" << DeviceList->len;
        g_ptr_array_free(DeviceList, TRUE);
    }
    else {
        qDebug() << "No USB devices found or USB Device Manager returned NULL";
        QMessageBox::information(this, tr("Info"), tr("No USB devices are currently connected."));
    }

    usbListWidget->setUpdatesEnabled(true);
}

void SpiceMainWindow::on_action_usbredir_triggered()
{
    // 获取当前的 USB 设备列表
    QStringList usbDevices;
    for (int i = 0; i < usbListWidget->count(); ++i) { // 使用成员变量
        QListWidgetItem *item = usbListWidget->item(i);
        usbDevices << item->text();
    }

    // 获取当前已重定向的设备列表
    QSet<QString> redirectedDevices = spicewindow->getRedirectedDevices();

    // 创建并显示 USB 重定向选择对话框
    UsbRedirDialog dialog(usbDevices, redirectedDevices, this); // 传递 redirectedDevices

    // 连接 SpiceQt 的信号到 dialog 的槽
    connect(spicewindow, &SpiceQt::usbDeviceAdded, &dialog, &UsbRedirDialog::UsbAdded, Qt::QueuedConnection);
    connect(spicewindow, &SpiceQt::usbDeviceRemoved, &dialog, &UsbRedirDialog::UsbRemoved, Qt::QueuedConnection);

    if (dialog.exec() == QDialog::Accepted) {
        QStringList selectedDevices = dialog.getSelectedDevices();
        // 计算需要连接和断开的设备
        QStringList devicesToConnect;
        QStringList devicesToDisconnect;

        // 设备需要连接的条件：被选中且尚未重定向
        for (const QString &device : selectedDevices) {
            if (!redirectedDevices.contains(device)) {
                devicesToConnect << device;
            }
        }

        // 设备需要断开的条件：之前已重定向但未被选中
        for (const QString &device : redirectedDevices) {
            if (!selectedDevices.contains(device)) {
                devicesToDisconnect << device;
            }
        }

        // 处理断开设备
        if (!devicesToDisconnect.isEmpty()) {
            disconnectUsbDevices(devicesToDisconnect);
        }

        // 处理连接设备
        if (!devicesToConnect.isEmpty()) {
            spicewindow->redirect_usb_device(devicesToConnect);
        }

        // 可选：根据实际操作结果显示消息
//        if (devicesToConnect.isEmpty() && devicesToDisconnect.isEmpty()) {
//            QMessageBox::information(this, tr("Info"), tr("未对 USB 设备进行任何更改。"));
//        } else {
//            QMessageBox::information(this, tr("Info"), tr("USB 设备重定向已更新。"));
//        }
    }

    // 断开信号连接，以避免潜在的重复连接
//        disconnect(spicewindow, &SpiceQt::usbDeviceAdded, &dialog, &UsbRedirDialog::UsbAdded);
//        disconnect(spicewindow, &SpiceQt::usbDeviceRemoved, &dialog, &UsbRedirDialog::UsbRemoved);
}

void SpiceMainWindow::disconnectUsbDevices(const QStringList &devices)
{
    if (devices.isEmpty()) {
        qDebug() << "没有设备被选择进行断开。";
        return;
    }

    // 调用 SpiceQt 的方法，断开选定的设备
    spicewindow->disconnectUsbDevices(devices);
}


void SpiceMainWindow::updateSpiceWindow()
{
    if (spicewindow)
    {
        spicewindow->update();
    }
}

void SpiceMainWindow::on_action_1_triggered()
{
    int screenWidth = QApplication::desktop()->screenGeometry(this).width();
//            smallMenu->resize(330, 65);  // 假设smallMenu宽300，高50
    smallMenu->move((screenWidth - smallMenu->width()) / 2, 100);
    smallMenu->show();
}

//文件传输按钮
void SpiceMainWindow::on_actionFile_input_triggered()
{
    TransferWindow *transferWindow = new TransferWindow(spicewindow, this);
    transferWindow->setAttribute(Qt::WA_DeleteOnClose);  // 确保关闭时释放内存
    transferWindow->open();  // 使用 open 打开对话框
}

void SpiceMainWindow::on_actionmulti_screen_triggered()
{
    int displayCount = spicewindow->detectDisplays();  // 检测显示器数量
    qDebug()<<"显示器数量："<<displayCount<<endl;
    // 创建选择显示器的对话框
    QDialog dialog(this);

    dialog.setWindowTitle("选择显示器");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QList<QCheckBox *> checkboxes;
//        dialog.resize(120, 150); // 设置对话框的宽度为400，高度为300
    // 根据检测的数量创建复选框
    for (int i = 0; i < displayCount; i++) {
        QCheckBox *checkbox = new QCheckBox(QString("显示器 %1").arg(i + 1), &dialog);

        if (i == 0) {
            // 默认选择第一个显示器
            checkbox->setChecked(true);
            // 确保只在开始时显示第一个显示器内容
            spicewindow->enableMonitor(1);  // 显示显示器1
        }
        checkboxes.append(checkbox);
        layout->addWidget(checkbox);
    }

    QPushButton *okButton = new QPushButton("确定", &dialog);
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    if (dialog.exec() == QDialog::Accepted) {
        QList<int> selectedDisplays;

        // 获取选中的显示器ID
        for (int i = 0; i < checkboxes.size(); i++) {
            if (checkboxes[i]->isChecked()) {
                // 用户选择了该显示器，启用它
                spicewindow->enableMonitor(i);
            }
        }
    }
}

void SpiceMainWindow::createDisplayWindow(int displayId) {
    if (displayId >= MAX_MONITORS) {
        qWarning() << "超过支持的最大显示器数量。无法创建更多显示器。";
        return;
    }

    // 获取当前的 SpiceSession
    SpiceSession *currentSession = spicewindow->getSession();  // 获取已有会话

//    SpiceMainWindow *newWindow = new SpiceMainWindow(this);
    QMainWindow *newWindow = new QMainWindow(this);
    SpiceQt *newSpiceQtInstance = new SpiceQt(newWindow);

    // 设置窗口标题和大小
    newWindow->setWindowTitle(QString("显示器 %1").arg(displayId));
    newWindow->resize(1920, 1080);  // 这里可以动态调整大小
    qDebug()<<"开始创建多显示器";
    // 使用相同的 SpiceSession 初始化新的显示器
    newSpiceQtInstance->initializeWithSession(currentSession, displayId);

    qDebug()<<"初始化完成创建多显示器";
    // 将 SpiceQt 嵌入到新的窗口中
    newWindow->setCentralWidget(newSpiceQtInstance);

    // 显示新窗口
    newWindow->show();

    // 保存新创建的窗口
    monitorWindows.append(newWindow);

    qDebug() << "创建新的显示窗口，显示器 ID：" << displayId;
}

void SpiceMainWindow::addDisplay_triggered()
{
    int nextDisplayId = monitorWindows.size();  // 使用当前窗口数量作为新的显示器ID

    if (nextDisplayId >= MAX_MONITORS) {
        QMessageBox::warning(this, tr("添加显示器"), tr("超过最大显示器数量，无法添加更多显示器。"));
        return;
    }

    createDisplayWindow(nextDisplayId);
}
