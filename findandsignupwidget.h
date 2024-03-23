#ifndef FINDANDSIGNUPWIDGET_H
#define FINDANDSIGNUPWIDGET_H

#include <QWidget>
#include <QPushButton>
#include<QRegularExpressionValidator>
namespace Ui {
class FindAndSignUpWidget;
}

class FindAndSignUpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FindAndSignUpWidget(int mode,QWidget *parent = nullptr);
    QString Email = "";
    QString VerificationCode= "";
    QString Username= "";
    QString Password1= "";
    QString Password2= "";

    ~FindAndSignUpWidget();
private:
    QPushButton *ShowPassword1,*HidePassword1,*ShowPassword2,*HidePassword2;
    int mode;
    QRegularExpressionValidator *PasswordValidator = nullptr;
    QRegularExpressionValidator *EmailValidator = nullptr;
    QRegularExpressionValidator *VerificationCodeValidator = nullptr;
    QRegularExpressionValidator *UsernameValidator = nullptr;

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
