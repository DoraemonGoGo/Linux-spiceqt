#ifndef SPICETEST_H
#define SPICETEST_H

#include <QMainWindow>

namespace Ui {
class SpiceTest;
}

class SpiceTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpiceTest(QWidget *parent = nullptr);
    ~SpiceTest();

private:
    Ui::SpiceTest *ui;
};

#endif // SPICETEST_H
