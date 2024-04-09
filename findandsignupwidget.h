#ifndef FINDANDSIGNUPWIDGET_H
#define FINDANDSIGNUPWIDGET_H

#include "messagecenter.h"
#include "widgetrevpacker.h"
#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include<QRegularExpressionValidator>


#include <QMessageBox>

namespace Ui {
class FindAndSignUpWidget;
}

class FindAndSignUpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FindAndSignUpWidget(int _mode,QWidget *parent = nullptr);
    QString Email = "";
    QString VerificationCode= "";
    QString Username= "";
    QString Password1= "";
    QString Password2= "";

    void interfaceForgetPasswordSuccess(WidgetArgPackage* arg);
    void interfaceForgetPasswordFail(WidgetArgPackage* arg);
    void interfaceRegisterSuccess(WidgetArgPackage* arg);
    void interfaceRegisterFail(WidgetArgPackage* arg);
    void interfaceForgetPasswordMailFail(WidgetArgPackage* arg);
    void interfaceRegisterMailFail(WidgetArgPackage* arg);
    void interfaceForgetPasswordMailSuccess(WidgetArgPackage* arg);
    void interfaceRegisterMailSuccess(WidgetArgPackage* arg);

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
    std::shared_ptr<MessageCenter> message_center;
    std::shared_ptr<WidgetRevPacker> widget_rev_packer;

private Q_SLOTS:
    void onEnterKeyPushButtonclicked();
    void onEnterPushButtonclicked();
    void onShowPassword1clicked();
    void onShowPassword2clicked();
    void onHidePassword1clicked();
    void onHidePassword2clicked();
    void onSendKeyPushButtonclicked();
private:
    Ui::FindAndSignUpWidget *ui;
};

#endif // FINDANDSIGNUPWIDGET_H
