#ifndef RESIZETO_H
#define RESIZETO_H

#include <QWidget>

namespace Ui {
class ResizeTo;
}

class ResizeTo : public QWidget
{
    Q_OBJECT

public:
    explicit ResizeTo(QWidget *parent = nullptr);
    ~ResizeTo();

private:
    Ui::ResizeTo *ui;
};

#endif // RESIZETO_H
