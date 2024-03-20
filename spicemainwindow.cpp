#include "spicemainwindow.h"
#include "ui_spicemainwindow.h"

SpiceMainWindow::SpiceMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpiceMainWindow)
{
    ui->setupUi(this);
}

SpiceMainWindow::~SpiceMainWindow()
{
    delete ui;
}
