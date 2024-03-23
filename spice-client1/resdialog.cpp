#include "resdialog.h"
#include "ui_resdialog.h"

ResDialog::ResDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResDialog)
{
    ui->setupUi(this);
}

ResDialog::~ResDialog()
{
    delete ui;
}
