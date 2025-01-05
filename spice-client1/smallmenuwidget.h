#ifndef SMALLMENUWIDGET_H
#define SMALLMENUWIDGET_H

#include <QWidget>

namespace Ui {
class SmallMenuWidget;
class SpiceMianWindow;
class SpiceQt;
}

class SmallMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SmallMenuWidget(QWidget *parent = nullptr);
    ~SmallMenuWidget();
    void checkIfMouseLeftMenu();
    bool isMenuActive = false;//小窗激活状态

private Q_SLOTS:
    void onCloseButtonClicked();
    void onMenuButtonClicked();
    void onFullscreenButtonClicked();
    void onUsbButtonClicked();
    void handleShortcutAction();
    void onFileButtonClicked();
    
private:
    Ui::SmallMenuWidget *ui;
};

#endif // SMALLMENUWIDGET_H
