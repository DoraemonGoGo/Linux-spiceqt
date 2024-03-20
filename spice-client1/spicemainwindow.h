#ifndef SPICEMAINWINDOW_H
#define SPICEMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SpiceMainWindow;
}

class SpiceQt;

class Widget1 : public QWidget
{
    Q_OBJECT
    
};

class SpiceMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpiceMainWindow(QWidget *parent = nullptr);
    ~SpiceMainWindow();
    void showspice(QString ip, QString port);

private Q_SLOTS:
    void on_actionToolBar_toggled(bool arg1);

    void on_actionStatusBar_toggled(bool arg1);

private:
    Ui::SpiceMainWindow *ui;
    SpiceQt *spicewindow;
    QWidget *widget1;
};

#endif // SPICEMAINWINDOW_H
