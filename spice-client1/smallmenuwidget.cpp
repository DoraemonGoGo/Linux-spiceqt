#include "smallmenuwidget.h"
#include "ui_smallmenuwidget.h"
#include <QMenu>
#include <QDebug>
#include <spicemainwindow.h>
#include <spiceqt.h>

SmallMenuWidget::SmallMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmallMenuWidget)
{
    ui->setupUi(this);
    setStyleSheet("background-color: white;");

    // 设置窗口为无边框窗口
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    // 创建快捷键对应的 QAction
    QAction *actionF1 = new QAction("Ctrl+Alt+Delete", this);
    actionF1->setObjectName("Ctrl_Alt_F3");

    QAction *actionF2 = new QAction("Ctrl+Alt+Space", this);
    actionF2->setObjectName("Ctrl_Alt_F3");

    QAction *actionF3 = new QAction("Ctrl+Alt+F1", this);
    actionF3->setObjectName("Ctrl_Alt_F1");  // 设置 objectName

    QAction *actionF4 = new QAction("Ctrl+Alt+F2", this);
    actionF4->setObjectName("Ctrl_Alt_F2");

    QAction *actionF5 = new QAction("Ctrl+Alt+F3", this);
    actionF5->setObjectName("Ctrl_Alt_F3");

    QAction *actionF6 = new QAction("Ctrl+Alt+F4", this);
    actionF6->setObjectName("Ctrl_Alt_F4");

    QAction *actionF7 = new QAction("Ctrl+Alt+F5", this);
    actionF7->setObjectName("Ctrl_Alt_F5");

    QAction *actionF8 = new QAction("Ctrl+Alt+F6", this);
    actionF8->setObjectName("Ctrl_Alt_F6");

    QAction *actionF9 = new QAction("Ctrl+Alt+F7", this);
    actionF9->setObjectName("Ctrl_Alt_F7");

    QAction *actionF10 = new QAction("Ctrl+Alt+F8", this);
    actionF10->setObjectName("Ctrl_Alt_F8");

    QAction *actionF11 = new QAction("Ctrl+Alt+F9", this);
    actionF11->setObjectName("Ctrl_Alt_F9");

    QAction *actionF12 = new QAction("Ctrl+Alt+F10", this);
    actionF12->setObjectName("Ctrl_Alt_F10");

    QAction *actionF13 = new QAction("Ctrl+Alt+F11", this);
    actionF13->setObjectName("Ctrl_Alt_F11");

    QAction *actionF14 = new QAction("Ctrl+Alt+F12", this);
    actionF14->setObjectName("Ctrl_Alt_F12");

    QMenu *menu = new QMenu(this);
    menu->addAction(actionF1);
    menu->addAction(actionF2);
    menu->addAction(actionF3);
    menu->addAction(actionF4);
    menu->addAction(actionF5);
    menu->addAction(actionF6);
    menu->addAction(actionF7);
    menu->addAction(actionF8);
    menu->addAction(actionF9);
    menu->addAction(actionF10);
    menu->addAction(actionF11);
    menu->addAction(actionF12);
    menu->addAction(actionF13);
    menu->addAction(actionF14);
    //    menu->addAction("Ctrl+Alt+Delete");
    //    menu->addAction("Ctrl+Alt+F1");
    //    menu->addAction("Ctrl+Alt+F2");
    //    menu->addAction("Ctrl+Alt+F3");
    //    menu->addAction("Ctrl+Alt+F4");
    //    menu->addAction("Ctrl+Alt+F5");
    //    menu->addAction("Ctrl+Alt+F6");
    //    menu->addAction("Ctrl+Alt+F7");
    //    menu->addAction("Ctrl+Alt+F8");
    //    menu->addAction("Ctrl+Alt+F9");
    //    menu->addAction("Ctrl+Alt+F10");
    //    menu->addAction("Ctrl+Alt+F11");
    //    menu->addAction("Ctrl+Alt+F12");

    //将快捷键菜单项连接到处理函数
    QList<QAction*> actions = menu->actions();
    for (QAction* action : actions) {
        connect(action, &QAction::triggered, this, &SmallMenuWidget::handleShortcutAction);
    }

    connect(ui->MenuBtn, &QPushButton::clicked, [this, menu]() {
        menu->exec(ui->MenuBtn->mapToGlobal(QPoint(0, ui->MenuBtn->height())));
    });



    // 将按钮的点击信号连接到槽函数



    connect(ui->CloseBtn, &QPushButton::clicked, this, &SmallMenuWidget::onCloseButtonClicked);
//    connect(ui->MenuBtn, &QPushButton::clicked, this, &SmallMenuWidget::onMenuButtonClicked);
    connect(ui->NotFullBtn, &QPushButton::clicked, this, &SmallMenuWidget::onFullscreenButtonClicked);
    connect(ui->USBBtn, &QPushButton::clicked, this, &SmallMenuWidget::onUsbButtonClicked);
}

void SmallMenuWidget::onCloseButtonClicked() {
    // 处理关闭按钮的点击事件
    qDebug() << "Close button clicked";
    // 添加关闭逻辑，比如关闭主窗口
    SpiceMainWindow *mainWindow = qobject_cast<SpiceMainWindow*>(this->parentWidget());
    mainWindow->close();
}

void SmallMenuWidget::onMenuButtonClicked() {
    // 处理菜单按钮的点击事件
    qDebug() << "Menu button clicked";
    // 添加菜单逻辑
}

void SmallMenuWidget::onFullscreenButtonClicked() {
    // 处理全屏按钮的点击事件
    qDebug() << "Fullscreen button clicked";
    // 添加全屏切换逻辑
    SpiceMainWindow *mainWindow = qobject_cast<SpiceMainWindow*>(this->parentWidget());
    mainWindow->NotFullScreen();
}

void SmallMenuWidget::onUsbButtonClicked() {
    // 处理 USB 按钮的点击事件
    qDebug() << "USB button clicked";
    // 添加 USB 相关逻辑
    SpiceMainWindow *mainWindow = qobject_cast<SpiceMainWindow*>(this->parentWidget());
    mainWindow->on_action_usbredir_triggered();
}

void SmallMenuWidget::handleShortcutAction()
{
    SpiceMainWindow *mainWindow = qobject_cast<SpiceMainWindow*>(this->parentWidget());
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;

    QString shortcut = action->objectName().remove("action");
    shortcut.replace("_", "+");

    qDebug() << "Shortcut clicked:" << shortcut;

    if (mainWindow->spicewindow) {
        mainWindow->spicewindow->sendShortcut(shortcut);
    }
}

SmallMenuWidget::~SmallMenuWidget()
{
    delete ui;
}
