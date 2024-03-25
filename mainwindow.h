#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
private slots:
    void onLoginButtonClicked();

    void onForgetPasswordButtonClicked();
    void onRegisterButtonClicked();
    void onShowPasswordClicked();
    void onHidePasswordClicked();
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
};
#endif // MAINWINDOW_H