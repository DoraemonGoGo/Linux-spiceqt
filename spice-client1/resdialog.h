#ifndef RESDIALOG_H
#define RESDIALOG_H

#include <QDialog>

namespace Ui {
class ResDialog;
}

class ResDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResDialog(QWidget *parent = nullptr);
    ~ResDialog();

private:
    Ui::ResDialog *ui;
};

#endif // RESDIALOG_H
