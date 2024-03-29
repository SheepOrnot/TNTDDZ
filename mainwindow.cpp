#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->statusBar()->hide();
    this->setFixedSize(1400,900);
    backgroundWidget = new BackgroundWidget(this);
    backgroundWidget->setGifBackground(":/image/image/mjqyjb.gif"); // 使用不同的GIF图像文件路径
    setCentralWidget(backgroundWidget);

    loginButton = new QPushButton("登录", this);
    loginButton->setIcon(QIcon(":/image/image/Icon/xxxxxxx.png")); // 设置登录按钮图标
    loginButton->setIconSize(QSize(20, 20)); // 设置图标大小
    loginButton->setStyleSheet("QPushButton { background-color: #ffffff; }"); // 设置登录按钮背景色
    loginButton->setMinimumHeight(50);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);

    forgetPasswordButton = new QPushButton(" 忘记密码 ", this);     // 创建忘记密码按钮
    forgetPasswordButton->setStyleSheet("QPushButton { background-color: transparent; }"); // 设置忘记密码按钮背景为透明色
    connect(forgetPasswordButton, &QPushButton::clicked, this, &MainWindow::onForgetPasswordButtonClicked);

    registerButton = new QPushButton("注册账号", this);           // 创建注册账号按钮
    registerButton->setStyleSheet("QPushButton { background-color: transparent; }"); // 设置注册按钮背景为透明色
    connect(registerButton, &QPushButton::clicked, this, &MainWindow::onRegisterButtonClicked);


    rememberAccountCheckbox = new QCheckBox(" 记住账号 ", this); // 创建“记住账号”的勾选框

    // 创建输入账号和密码的文本框
    usernameLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);        // 设置密码输入框为密码模式
    QRegularExpression PasswordRegex("[A-Za-z0-9_.*~#!@$%^&]*");
    PasswordValidator = new QRegularExpressionValidator(PasswordRegex, this);
    passwordLineEdit->setValidator(PasswordValidator);
    passwordLineEdit->setMaxLength(20);

    // 设置输入框的提示文本
    usernameLineEdit->setPlaceholderText("Account/Email");
    passwordLineEdit->setPlaceholderText("Password");
    usernameLineEdit->setMinimumHeight(50);
    passwordLineEdit->setMinimumHeight(50);
    usernameLineEdit->setStyleSheet("background-color: transparent; border: 1px solid black;");
    passwordLineEdit->setStyleSheet("background-color: transparent; border: 1px solid black;");

    QRegularExpression UsernameRegex("^[\u4e00-\u9fa5A-Za-z0-9_@~!#$%^&*:<>《|]*.[a-zA-Z]*");
    UsernameValidator = new QRegularExpressionValidator(UsernameRegex, this);
    usernameLineEdit->setValidator(UsernameValidator);
    usernameLineEdit->setMaxLength(30);

    QIcon MailIcon(":/image/image/Icon/mail.png");
    usernameLineEdit->setClearButtonEnabled(true); // 添加清除按钮
    usernameLineEdit->addAction(MailIcon, QLineEdit::LeadingPosition); // 添加图标（LeadingPosition为左侧位置）

    QIcon PasswordIcon(":/image/image/Icon/password.png");
    passwordLineEdit->addAction(PasswordIcon, QLineEdit::LeadingPosition); // 添加图标（LeadingPosition为左侧位置）

    ShowPassword = new QPushButton(passwordLineEdit);
    ShowPassword->setIcon(QIcon(":/image/image/Icon/eye_open.png"));
    ShowPassword->setIconSize(QSize(20,20));
    ShowPassword->setGeometry(430,15,20,20);
    ShowPassword->setStyleSheet("QPushButton { background-color: transparent;}");
    ShowPassword->setStyleSheet("border:0px");

    connect(ShowPassword, &QPushButton::clicked, this, &MainWindow::onShowPasswordClicked);

    HidePassword = new QPushButton(passwordLineEdit);
    HidePassword->setIcon(QIcon(":/image/image/Icon/eye_close.png"));
    HidePassword->setIconSize(QSize(20,20));
    HidePassword->setGeometry(430,15,20,20);
    HidePassword->setStyleSheet("QPushButton { background-color: transparent;}");
    HidePassword->setStyleSheet("border:0px");
    HidePassword->hide();
    connect(HidePassword, &QPushButton::clicked, this, &MainWindow::onHidePasswordClicked);

    GridLayout = new QGridLayout(backgroundWidget);
    HBoxLayout = new QHBoxLayout();
    //QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    spacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    spacer3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    spacer4 = new QSpacerItem(20, 300, QSizePolicy::Fixed, QSizePolicy::Fixed);
    GridLayout->addWidget(usernameLineEdit,1,1);
    GridLayout->addWidget(passwordLineEdit,2,1);
    GridLayout->addWidget(loginButton,3,1);
    GridLayout->addItem(spacer1,0,0);
    GridLayout->addItem(spacer2,0,2);
    GridLayout->addItem(spacer4,0,1);
    GridLayout->addLayout(HBoxLayout,4,1);
    HBoxLayout->addWidget(rememberAccountCheckbox,0);
    HBoxLayout->QHBoxLayout::addSpacerItem(spacer3);
    HBoxLayout->addWidget(forgetPasswordButton,2);
    HBoxLayout->addWidget(registerButton,3);


    GridLayout->setVerticalSpacing(35);
    GridLayout->setColumnStretch(0,1);
    GridLayout->setColumnStretch(1,1);
    GridLayout->setColumnStretch(2,1);

    GridLayout->setRowStretch(0,1);
    GridLayout->setRowStretch(1,1);
    GridLayout->setRowStretch(2,1);
    GridLayout->setRowStretch(3,1);
    GridLayout->setRowStretch(4,0);

    //***********************need global********************************
    message_center = new MessageCenter();
    widget_rev_packer = new WidgetRevPacker(message_center);

    message_center->loadInterface("interfaceLoginSuccess", std::bind(&MainWindow::interfaceLoginSuccess, this, std::placeholders::_1));
    message_center->loadInterface("interfaceLoginFail",    std::bind(&MainWindow::interfaceLoginFail, this, std::placeholders::_1));

}
void MainWindow::onForgetPasswordButtonClicked()
{
    FindAndSignUpWidget *FindWidget = new FindAndSignUpWidget(1);        //mode1 -> 忘记密码
    FindWidget->show();
}
void MainWindow::onRegisterButtonClicked()
{
    FindAndSignUpWidget *SignUPWidget = new FindAndSignUpWidget(0);         //mode0 -> 注册
    SignUPWidget->show();
}
void MainWindow::onShowPasswordClicked()
{
    ShowPassword->hide(); HidePassword->show();
    passwordLineEdit->setEchoMode(QLineEdit::Normal);
}
void MainWindow::onHidePasswordClicked()
{
    ShowPassword->show(); HidePassword->hide();
    passwordLineEdit->setEchoMode(QLineEdit::Password);
}
void MainWindow::onLoginButtonClicked()
{
    EmailOrUid = usernameLineEdit->text();
    Password = passwordLineEdit->text();

    WidgetArgPackage* login_submit = new WidgetArgPackage();
    login_submit->packMessage<WidgetArgLogin>(LOGIN_OPCODE::LOGIN, EmailOrUid.toStdString(), EmailOrUid.toStdString(), Password.toStdString(), "");
    widget_rev_packer->WidgetsendMessage(login_submit);
}


//********************INTERFACE****************************
void MainWindow::interfaceLoginSuccess(WidgetArgPackage* arg)
{
    EmailOrUid = usernameLineEdit->text();
    Password = passwordLineEdit->text();
    LobbyWidget *lobbyWidget = new LobbyWidget();
    lobbyWidget->show();
        //改为delete，先delete所有成员指针

    //deleteLater();
    this->close();
    //this->deleteLater();
}
void MainWindow::interfaceLoginFail(WidgetArgPackage* arg)
{
    WidgetArgStatus *status = static_cast<WidgetArgStatus*>(arg->package);
    std::cout << "Login Fail, code: " << status->status << std::endl;

    delete arg;
}
//********************************************************


MainWindow::~MainWindow()
{
    delete ui;

//    delete(loginButton);
//    delete(forgetPasswordButton);
//    delete(registerButton);
//    delete(ShowPassword);
//    delete(HidePassword);
//    delete(rememberAccountCheckbox);
//    delete(usernameLineEdit);
//    delete(passwordLineEdit);
//    delete(spacer1);
//    delete(spacer2);
//    delete(spacer3);
//    delete(spacer4);
//    delete(stackedWidget);qDebug()<<"123";
//    delete(HBoxLayout);qDebug()<<"123";
//    delete(backgroundWidget);qDebug()<<"123";
//    delete(GridLayout);qDebug()<<"123";


}

