#ifndef FINDANDSIGNUPWIDGET_H
#define FINDANDSIGNUPWIDGET_H

#include <QWidget>
#include <QPushButton>
namespace Ui {
class FindAndSignUpWidget;
}

class FindAndSignUpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FindAndSignUpWidget(int mode,QWidget *parent = nullptr);
    int mode;
    QPushButton *ShowPassword1,*HidePassword1,*ShowPassword2,*HidePassword2;
    ~FindAndSignUpWidget();

private slots:
    void on_EnterKeyPushButton_clicked();
    void on_ShowPassword1_clicked();
    void on_ShowPassword2_clicked();
    void on_HidePassword1_clicked();
    void on_HidePassword2_clicked();

private:
    Ui::FindAndSignUpWidget *ui;
};

#endif // FINDANDSIGNUPWIDGET_H
