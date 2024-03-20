#include "spicewidget.h"
#include "ui_spicewidget.h"
#include "spiceqt.h"
#include "QHBoxLayout"

SpiceWidget::SpiceWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpiceWidget)
{
    ui->setupUi(this);
//    this->addAction(ui->actionFullscreen);
//    connect(ui->actionFullscreen, &QAction::triggered, [&]() {

//        auto full = ui->actionFullscreen->isChecked();
//        menuBar()->setVisible(!full);
//        ui->actionFullscreen->setShortcut(  full ? QKeySequence("Esc") : QKeySequence("Ctrl+F"));

//        static bool maximized = false;// 记录当前状态
//        if ( full )
//        {
//            maximized = isMaximized();
//        }
//        else if ( maximized && isMaximized() )
//        {
//            return;
//        }

//        if ( full && !isMaximized() || !full && isMaximized() )
//        {
//            if (isMaximized())
//            {
//                showNormal();
//            }
//            else
//                showMaximized();
//        }
//    });
}

SpiceWidget::~SpiceWidget()
{
    delete ui;
}
