#ifndef SPICEMAINWINDOW_H
#define SPICEMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SpiceMainWindow;
}

class SpiceMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpiceMainWindow(QWidget *parent = nullptr);
    ~SpiceMainWindow();

private:
    Ui::SpiceMainWindow *ui;
};

#endif // SPICEMAINWINDOW_H
