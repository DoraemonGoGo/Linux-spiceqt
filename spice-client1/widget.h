#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QLineEdit>
#include <spicemainwindow.h>

namespace Ui {
class Widget;
}

class SpiceQt;
class SpiceMianWindow;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

//public Q_SLOTS:
//    void connectSpice();

private Q_SLOTS:
    void on_connbtn_clicked();

protected:
    void keyPress(QKeyEvent *event);

private:
//    QLineEdit *ipedit;
//    QLineEdit *portedit;
//    SpiceMainWindow *smw;

private:
    Ui::Widget *ui;
    //Ui::SpiceMainWindow spiceui;
    QList<SpiceMainWindow*> spiceWindows;  // 管理多个实例
};

#endif // WIDGET_H
