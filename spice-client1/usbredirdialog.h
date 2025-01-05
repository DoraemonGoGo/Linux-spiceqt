#ifndef USBREDIRDIALOG_H
#define USBREDIRDIALOG_H

#include <QDialog>

namespace Ui {
class UsbRedirDialog;
}

class UsbRedirDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UsbRedirDialog(const QStringList &usbDevices, const QSet<QString> &redirectedDevices, QWidget *parent = nullptr);
    ~UsbRedirDialog();
    QStringList getSelectedDevices() const;

public Q_SLOTS:
    void UsbAdded(const QString &description);    // 处理设备添加
    void UsbRemoved(const QString &description);  // 处理设备移除

private:
    Ui::UsbRedirDialog *ui;
};

#endif // USBREDIRDIALOG_H
