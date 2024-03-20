#ifndef SPICEWIDGET_H
#define SPICEWIDGET_H

#include <QMainWindow>
//#include <ui_spicewidget.h>

namespace Ui {
class SpiceWidget;
}

class SpiceWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpiceWidget(QWidget *parent = nullptr);
    ~SpiceWidget();

private:
    Ui::SpiceWidget *ui;
};

#endif // SPICEWIDGET_H
