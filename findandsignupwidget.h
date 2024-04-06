#ifndef FINDANDSIGNUPWIDGET_H
#define FINDANDSIGNUPWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
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
    QTimer *timer;
    int remainingTime;
    void StartCountDown();
    void updateCountDown();
private slots:
    void onEnterKeyPushButtonclicked();
    void onShowPassword1clicked();
    void onShowPassword2clicked();
    void onHidePassword1clicked();
    void onHidePassword2clicked();
    void onSendKeyPushButtonclicked();
private:
    Ui::FindAndSignUpWidget *ui;
};

#endif // FINDANDSIGNUPWIDGET_H
