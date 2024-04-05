#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.h"
#include <QMainWindow>
#include "backgroundwidget.h"
#include "findandsignupwidget.h"
#include "lobbywidget.h"
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include<QSpacerItem>
#include<QRegularExpressionValidator>
#include<QThread>

#include "widgetrevpacker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString EmailOrUid="";            //输入的用户名，点击登录时赋值
    QString Password = "";            //输入的密码，点击登录时赋值

    void interfaceLoginSuccess(WidgetArgPackage* arg);     //接口: 界面登录成功
    void interfaceLoginFail(WidgetArgPackage* arg);        //接口：界面登录失败
private Q_SLOTS:
    void onLoginButtonClicked();

    void onForgetPasswordButtonClicked();
    void onRegisterButtonClicked();
    void onShowPasswordClicked();
    void onHidePasswordClicked();
    void EnterLobby();

private:
    Ui::MainWindow *ui;
    BackgroundWidget *backgroundWidget = nullptr;
    QPushButton *loginButton= nullptr;
    QPushButton *forgetPasswordButton= nullptr;
    QPushButton *registerButton= nullptr;
    QPushButton *ShowPassword= nullptr,*HidePassword= nullptr;
    QCheckBox *rememberAccountCheckbox= nullptr;
    QLineEdit *usernameLineEdit= nullptr;
    QLineEdit *passwordLineEdit= nullptr;
    QStackedWidget *stackedWidget= nullptr;
    QGridLayout *GridLayout= nullptr;
    QHBoxLayout *HBoxLayout= nullptr;
    QSpacerItem *spacer1= nullptr;
    QSpacerItem *spacer2= nullptr;
    QSpacerItem *spacer3= nullptr;
    QSpacerItem *spacer4= nullptr;
    QRegularExpressionValidator *PasswordValidator = nullptr;
    QRegularExpressionValidator *UsernameValidator = nullptr;

    std::shared_ptr<MessageCenter> message_center;
    std::shared_ptr<WidgetRevPacker> widget_rev_packer;
    QString CiphertextPwd;         //需要记住账号密码时，在返回登录成功后写入json
private:
    bool RemUser;
    void ImportConfig();
    QString Encryption();
    QString Decryption();
    void RestoreConfig();
};

#endif // MAINWINDOW_H
