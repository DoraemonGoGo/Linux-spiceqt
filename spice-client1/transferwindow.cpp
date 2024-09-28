#include "transferwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QProgressBar>
#include "spiceqt.h"

TransferWindow::TransferWindow(SpiceQt *spice, QWidget *parent)
    : QDialog(parent), spiceQt(spice)
{
    setWindowTitle("File Transfer");
    resize(400, 200);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // 添加控件
    QPushButton *cancelButton = new QPushButton("Cancel Transfer", this);
    QPushButton *selectSourceButton = new QPushButton("Select Source Files", this);
    transferButton = new QPushButton("Transfer Files", this);
    closeButton = new QPushButton("Close", this);  // 关闭按钮，传输完成后启用
    closeButton->setEnabled(false);  // 默认禁用

    sourcePathLabel = new QLabel("Source Files: Not selected", this);
    progressBar = new QProgressBar(this);  // 进度条控件
    progressBar->setRange(0, 100);  // 设置进度条的范围
    progressBar->setValue(0);  // 初始值为 0%

    layout->addWidget(selectSourceButton);
    layout->addWidget(cancelButton);
    layout->addWidget(sourcePathLabel);
    layout->addWidget(progressBar);
    layout->addWidget(transferButton);
    layout->addWidget(closeButton);  // 添加关闭按钮

    // 信号和槽的连接
    connect(selectSourceButton, &QPushButton::clicked, this, &TransferWindow::selectSourceFiles);
    connect(cancelButton, &QPushButton::clicked, spiceQt, &SpiceQt::cancelFileTransfer);
    connect(transferButton, &QPushButton::clicked, this, &TransferWindow::startFileTransfer);
    connect(closeButton, &QPushButton::clicked, this, &TransferWindow::close);  // 关闭按钮的槽函数
}

void TransferWindow::selectSourceFiles()
{
    sourceFilePaths = QFileDialog::getOpenFileNames(this, "Select Source Files");
    if (!sourceFilePaths.isEmpty()) {
        sourcePathLabel->setText("Source Files: " + sourceFilePaths.join(", "));
    }
}

void TransferWindow::startFileTransfer()
{
    if (sourceFilePaths.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select at least one source file.");
        return;
    }

    // 禁用传输按钮，防止重复点击
    transferButton->setEnabled(false);

    // 开始文件传输
    connect(spiceQt, &SpiceQt::fileTransferProgress, this, &TransferWindow::updateProgress);  // 连接进度信号
    connect(spiceQt, &SpiceQt::fileTransferCompleted, this, &TransferWindow::transferCompleted);  // 连接完成信号
    connect(spiceQt, &SpiceQt::fileTransferCancelled, this, &TransferWindow::transferCancelled);  // 连接取消信号

    spiceQt->startFileTransfer(sourceFilePaths);
}

void TransferWindow::updateProgress(double progress)
{
    int intProgress = static_cast<int>(progress);  // 直接使用百分比的进度值
    progressBar->setValue(intProgress);  // 更新进度条的值
}

void TransferWindow::transferCompleted()
{
    progressBar->setValue(100);  // 设置进度条为 100%
    sourcePathLabel->setText("Transfer Completed Successfully");

    // 启用关闭按钮
    closeButton->setEnabled(true);

    // 断开与进度和取消的信号连接
    disconnect(spiceQt, &SpiceQt::fileTransferProgress, this, &TransferWindow::updateProgress);
    disconnect(spiceQt, &SpiceQt::fileTransferCancelled, this, &TransferWindow::transferCancelled);
}

void TransferWindow::transferCancelled()
{
    progressBar->reset();  // 重置进度条
    sourcePathLabel->setText("Transfer Cancelled");

    // 启用关闭按钮
    closeButton->setEnabled(true);

    // 重新启用传输按钮
    transferButton->setEnabled(true);
}

void TransferWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow *mainWindow = qobject_cast<QMainWindow *>(parent());
    if (mainWindow) {
        mainWindow->activateWindow();  // 重新激活主窗口
        mainWindow->setFocus();  // 设置焦点到主窗口
    }
    QWidget::closeEvent(event);
}
