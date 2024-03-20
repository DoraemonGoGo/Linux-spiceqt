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

    central->setLayout(layout);

//    spicewindow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->actionToolBar->setChecked(true);
    ui->actionStatusBar->setChecked(true);

    //设置窗口的全屏和非全屏的切换
    this->addAction(ui->actionFullscreen);
    connect(ui->actionFullscreen, &QAction::triggered, [&]() {

        auto full = ui->actionFullscreen->isChecked();
        menuBar()->setVisible(!full);
        ui->actionFullscreen->setShortcut(  full ? QKeySequence("Esc") : QKeySequence("Ctrl+F"));

        static bool maximized = false;// 记录当前状态
        if ( full )
        {
            maximized = isMaximized();
        }
        else if ( maximized && isMaximized() )
        {
            return;
        }

        if ( full && !isMaximized() || !full && isMaximized() )
        {
            if (isMaximized())
            {
                showNormal();
            }
            else
                showMaximized();
        }
    });

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
                //qDebug() << a->text();

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
