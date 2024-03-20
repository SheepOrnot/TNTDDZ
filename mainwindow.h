#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "backgroundwidget.h"
#include "findandsignupwidget.h"
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include<QSpacerItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void onLoginButtonClicked();

    void onForgetPasswordButtonClicked();
    void onRegisterButtonClicked();
    void onShowPasswordClicked();
    void onHidePasswordClicked();
private:
    Ui::MainWindow *ui;
    BackgroundWidget *m_backgroundWidget;
    QPushButton *loginButton;
    QPushButton *forgetPasswordButton;
    QPushButton *registerButton;
    QPushButton *ShowPassword,*HidePassword;
    QCheckBox *rememberAccountCheckbox;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QStackedWidget *stackedWidget;
};
#endif // MAINWINDOW_H
