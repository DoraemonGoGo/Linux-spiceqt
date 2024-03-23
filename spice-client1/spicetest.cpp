#include "spicetest.h"
#include "ui_spicetest.h"

SpiceTest::SpiceTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpiceTest)
{
    ui->setupUi(this);
}

SpiceTest::~SpiceTest()
{
    delete ui;
}
