#include "widget.h"
#include "ui_widget.h"
#include "spiceqt.h"
#include "QHBoxLayout"
#include "spicemainwindow.h"

Widget::Widget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->ipedit->setText("127.0.0.1");
    ui->portedit->setText("5900");
//    connect(ui->connbtn, SIGNAL(clicked()), this, SLOT(connectSpice()));
}

//void Widget::connectSpice()
//{
//    _spiceWidget = SpiceQt::getSpice();
//    qDebug() << ui->ipedit->text() << "  ,  " << ui->portedit->text() << endl;
//    qDebug() << _spiceWidget;
//    smw.setCentralWidget(_spiceWidget);
//    smw.show();
//    _spiceWidget->show();
//    _spiceWidget->connectToGuest(ui->ipedit->text(), ui->portedit->text());
//}


void Widget::on_connbtn_clicked()
{
    QString ip = ui->ipedit->text();
    QString port = ui->portedit->text();
    SpiceMainWindow *smw = new SpiceMainWindow();
    smw->setWindowTitle("SpiceConnection");
    qDebug()<<"______________________________";
    smw->showspice(ip, port);
    smw->show();

    spiceWindows.append(smw);  // 将新创建的实例添加到列表中
}

Widget::~Widget()
{
    // 清除所有 SpiceMainWindow 实例
    for (SpiceMainWindow* smw : spiceWindows) {
        if (smw) {
            smw->close();  // 确保断开与虚拟机的连接
            delete smw;  // 释放内存
        }
    }
    delete ui;

    // 删除所有创建的窗口实例
//    qDeleteAll(spiceWindows);
}
