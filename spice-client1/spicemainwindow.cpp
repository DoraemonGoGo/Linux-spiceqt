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
    QWidget *central = new QWidget();
    setCentralWidget(central);
    QHBoxLayout *layout = new QHBoxLayout(central);
    spicewindow = new SpiceQt();

    spicewindow = SpiceQt::getSpice();
    spicewindow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    spicewindow->resize(2000, 2400);
//    ui->layout->addWidget(widget1);
    layout->addWidget(spicewindow);

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
//  spicewindow->show();
    spicewindow->connectToGuest(ip, port);
}
