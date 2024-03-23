#include "resizeto.h"
#include "ui_resizeto.h"

ResizeTo::ResizeTo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResizeTo)
{
    ui->setupUi(this);
    ui->Layout_w->setStretch(0,6);
    ui->Layout_w->setStretch(1,2);
    ui->Layout_w->setStretch(2,2);
}

ResizeTo::~ResizeTo()
{
    delete ui;
}
