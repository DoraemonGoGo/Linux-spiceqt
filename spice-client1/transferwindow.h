#ifndef TRANSFERWINDOW_H
#define TRANSFERWINDOW_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QProgressBar>
#include <QListWidget>
#include <QPushButton>

class SpiceQt;

class TransferWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TransferWindow(SpiceQt *spice, QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event) override;

private Q_SLOTS:
    void selectSourceFiles();
    void startFileTransfer();
    void updateProgress(double progress);  // 用于更新进度的槽函数，改为 double 类型
    void transferCompleted();  // 传输完成后的槽函数
    void transferCancelled();  // 传输取消后的槽函数

private:
    SpiceQt *spiceQt;
    QStringList sourceFilePaths;

    QLabel *sourcePathLabel;
    QProgressBar *progressBar;  // 进度条控件
    QPushButton *transferButton;
    QPushButton *closeButton;  // 关闭按钮
};

#endif // TRANSFERWINDOW_H
