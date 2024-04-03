#ifndef FINDANDSIGNUPWIDGET_H
#define FINDANDSIGNUPWIDGET_H

#include <QWidget>
#include <QPushButton>
#include<QRegularExpressionValidator>
#include "messagecenter.h"
#include "widgetrevpacker.h"

#include <QMessageBox>

namespace Ui {
class FindAndSignUpWidget;
}

class FindAndSignUpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FindAndSignUpWidget(int _mode,MessageCenter *_message_center,WidgetRevPacker *_widget_rev_packer,QWidget *parent = nullptr);
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

    MessageCenter *message_center;
    WidgetRevPacker *widget_rev_packer;

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
