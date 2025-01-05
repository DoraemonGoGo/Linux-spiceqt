#include "usbredirdialog.h"
#include "ui_usbredirdialog.h"
#include "QListWidgetItem"
#include "QListWidget"
#include "QDebug"

UsbRedirDialog::UsbRedirDialog(const QStringList &usbDevices, const QSet<QString> &redirectedDevices, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsbRedirDialog)
{
    ui->setupUi(this);

    setWindowTitle("USB 重定向选择");

    // 将 USB 设备添加到 QListWidget，并设置为可选
    for (const QString &device : usbDevices) {
        QListWidgetItem *item = new QListWidgetItem(device, ui->usbListWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        if (redirectedDevices.contains(device)) {
            item->setCheckState(Qt::Checked);
//            item->setFlags(item->flags() & ~Qt::ItemIsEnabled); // 禁用已重定向设备
        } else {
            item->setCheckState(Qt::Unchecked);
        }
    }
}

UsbRedirDialog::~UsbRedirDialog()
{
    delete ui;
}

QStringList UsbRedirDialog::getSelectedDevices() const
{
    QStringList selectedDevices;
    for (int i = 0; i < ui->usbListWidget->count(); ++i) {
        QListWidgetItem *item = ui->usbListWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            selectedDevices << item->text();
        }
    }
    return selectedDevices;
}

void UsbRedirDialog::UsbAdded(const QString &description)
{
    // 检查设备是否已经在列表中
    QList<QListWidgetItem *> items = ui->usbListWidget->findItems(description, Qt::MatchExactly);
    if (items.isEmpty()) {
        QListWidgetItem *item = new QListWidgetItem(description, ui->usbListWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        qDebug() << "USBRedirectDialog: 设备添加 -" << description;
    }
}

void UsbRedirDialog::UsbRemoved(const QString &description)
{
    qDebug() << "UsbRemoved 开始移除" << description;

    // 提取设备的供应商 ID 和产品 ID
    QRegExp rx("\\[(\\w{4}):(\\w{4})\\]");
    QString vendorId, productId;
    if (rx.indexIn(description) != -1) {
        vendorId = rx.cap(1);
        productId = rx.cap(2);
        qDebug() << "Vendor ID:" << vendorId << "Product ID:" << productId;
    } else {
        qDebug() << "无法提取 Vendor ID 和 Product ID";
        return;
    }

    // 遍历 usbListWidget，找到匹配的设备
    for (int i = 0; i < ui->usbListWidget->count(); ++i) {
        QListWidgetItem *item = ui->usbListWidget->item(i);
        QString itemText = item->text();

        // 检查设备描述中是否包含相同的 Vendor ID 和 Product ID
        if (itemText.contains(QString("[%1:%2]").arg(vendorId, productId))) {
            qDebug() << "找到匹配项：" << itemText;
            delete ui->usbListWidget->takeItem(i);
            qDebug() << "USBRedirectDialog: 设备移除 -" << itemText;
            return; // 假设每个设备唯一，只移除第一个匹配项
        }
    }

    qDebug() << "未找到匹配的设备描述：" << description;
}
