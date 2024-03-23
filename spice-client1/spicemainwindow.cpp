#include "QHBoxLayout"
#include "QMouseEvent"
#include "spicemainwindow.h"
#include "ui_spicemainwindow.h"
#include "spiceqt.h"
#include "QTimer"

SpiceMainWindow::SpiceMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpiceMainWindow)
{
    ui->setupUi(this);

    //设置instance的嵌入和布局
    QHBoxLayout *layout = new QHBoxLayout();
    spicewindow = new SpiceQt();
    QWidget *central = new QWidget();
    setCentralWidget(central);
    spicewindow = SpiceQt::getSpice();
    layout->addWidget(spicewindow, 1);
    spicewindow->spiceResize(1000, 1000);
    central->setLayout(layout);

    spicewindow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->actionToolBar->setChecked(true);
    ui->actionStatusBar->setChecked(true);

//    connect(ui->actiontoolclose, &QAction::trigger, this, &SpiceMainWindow::close);
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


//    spicewindow->resize(2000, 2400);
//    ui->layout->addWidget(widget1);


//    setCentralWidget();
//    ui->layout->setContentsMargins(0, 0, 0, 0);
//    ui->layout->setSpacing(0);
//    ui->widget1->setLayout(layout);
//    ui->layout->setStretch(0, 1);
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
    qDebug() << spiceheight << " , " << spicewidth << endl;
    spicewindow->show();
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
    qDebug() << "hhhhhh" <<endl;
    resdia = new ResDialog(this);
    resdia->show();
}

//工具栏close按钮关闭主窗口
void SpiceMainWindow::on_actiontoolclose_triggered()
{
    this->close();
}
