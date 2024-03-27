#ifndef SPICEMAINWINDOW_H
#define SPICEMAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include <resdialog.h>

namespace Ui {
class SpiceMainWindow;
}

class ResizeTo;
class SpiceQt;


class SpiceMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpiceMainWindow(QWidget *parent = nullptr);
    ~SpiceMainWindow();
    void showspice(QString ip, QString port);
    void fullscreen(bool full);


protected:
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);

private Q_SLOTS:
    void on_actionToolBar_toggled(bool arg1);

    void on_actionStatusBar_toggled(bool arg1);

    void on_actionFullscreen_triggered(bool checked);

    void on_actiontoolfullscreen_triggered();


    void on_actionResize_to_triggered();

    void on_actiontoolclose_triggered();

private:
    Ui::SpiceMainWindow *ui;
    SpiceQt *spicewindow;
    ResizeTo *res;
    ResDialog *resdia;
};

#endif // SPICEMAINWINDOW_H
