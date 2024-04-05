#include "findandsignupwidget.h"
#include "ui_findandsignupwidget.h"
#include <QDebug>
FindAndSignUpWidget::FindAndSignUpWidget(int _mode, QWidget *parent):
    QWidget(parent),
    mode(_mode),
    ui(new Ui::FindAndSignUpWidget)
{
    ui->setupUi(this);
    this->setFixedSize(600,400);
    ui->UsernameLineEdit->hide();
    ui->Password1LineEdit->hide();
    ui->Password2LineEdit->hide();
    ui->EnterPushButton->hide();

    QIcon MailIcon(":/image/image/Icon/mail.png");
    ui->MailLineEdit->setClearButtonEnabled(true);// 添加清除按钮
    ui->MailLineEdit->setPlaceholderText("Email");
    ui->MailLineEdit->addAction(MailIcon, QLineEdit::LeadingPosition); // 添加图标（LeadingPosition为左侧位置）
    QRegularExpression EmailRegex("^\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}\\b$");
    EmailValidator = new QRegularExpressionValidator(EmailRegex, this);
    ui->MailLineEdit->setValidator(EmailValidator);
    ui->MailLineEdit->setMaxLength(50);

    QIcon KeyIcon(":/image/image/Icon/key.png");
    ui->KeyLineEdit->setClearButtonEnabled(true);// 添加清除按钮
    ui->KeyLineEdit->setPlaceholderText("Verification code");
    ui->KeyLineEdit->addAction(KeyIcon, QLineEdit::LeadingPosition); // 添加图标（LeadingPosition为左侧位置）
    QRegularExpression VerificationCodeRegex("^\\d{6}$");
    VerificationCodeValidator = new QRegularExpressionValidator(VerificationCodeRegex, this);
    ui->KeyLineEdit->setValidator(VerificationCodeValidator);

    QIcon UsernameIcon(":/image/image/Icon/username.png");
    ui->UsernameLineEdit->setClearButtonEnabled(true); // 添加清除按钮
    ui->UsernameLineEdit->setPlaceholderText("Username");
    ui->UsernameLineEdit->addAction(UsernameIcon, QLineEdit::LeadingPosition); // 添加图标（LeadingPosition为左侧位置）
    QRegularExpression UsernameRegex("^[\u4e00-\u9fa5A-Za-z0-9_@~!#$%^&*:<>《|]*");
    UsernameValidator = new QRegularExpressionValidator(UsernameRegex, this);
    ui->UsernameLineEdit->setValidator(UsernameValidator);
    ui->UsernameLineEdit->setMaxLength(30);

    QIcon PasswordIcon(":/image/image/Icon/password.png");
    ui->Password1LineEdit->setEchoMode(QLineEdit::Password); // 设置密码输入框为密码模式
    ui->Password2LineEdit->setEchoMode(QLineEdit::Password); // 设置密码输入框为密码模式
    ui->Password1LineEdit->addAction(PasswordIcon, QLineEdit::LeadingPosition); // 添加图标（LeadingPosition为左侧位置）
    ui->Password2LineEdit->addAction(PasswordIcon, QLineEdit::LeadingPosition); // 添加图标（LeadingPosition为左侧位置）
    QRegularExpression PasswordRegex("[A-Za-z0-9_.*~#!@$%^&]*");
    PasswordValidator = new QRegularExpressionValidator(PasswordRegex, this);
    ui->Password1LineEdit->setValidator(PasswordValidator);
    ui->Password1LineEdit->setMaxLength(20);
    ui->Password2LineEdit->setValidator(PasswordValidator);
    ui->Password2LineEdit->setMaxLength(20);

    ShowPassword1 = new QPushButton(this);
    ShowPassword1->setIcon(QIcon(":/image/image/Icon/eye_open.png"));
    ShowPassword1->setIconSize(QSize(20,20));
    ShowPassword1->setGeometry(ui->Password1LineEdit->x()+275,ui->Password1LineEdit->y()+25,20,20);
    ShowPassword1->setStyleSheet("QPushButton { background-color: transparent; }");
    connect(ShowPassword1, &QPushButton::clicked, this, &FindAndSignUpWidget::onShowPassword1clicked);

    ShowPassword2 = new QPushButton(this);
    ShowPassword2->setIcon(QIcon(":/image/image/Icon/eye_open.png"));
    ShowPassword2->setIconSize(QSize(20,20));
    ShowPassword2->setGeometry(ui->Password2LineEdit->x()+275,ui->Password2LineEdit->y()+25,20,20);
    ShowPassword2->setStyleSheet("QPushButton { background-color: transparent; }");
    connect(ShowPassword2, &QPushButton::clicked, this, &FindAndSignUpWidget::onShowPassword2clicked);


    HidePassword1 = new QPushButton(this);
    HidePassword1->setIcon(QIcon(":/image/image/Icon/eye_close.png"));
    HidePassword1->setIconSize(QSize(20,20));
    HidePassword1->setGeometry(ui->Password1LineEdit->x()+275,ui->Password1LineEdit->y()+25,20,20);
    HidePassword1->setStyleSheet("QPushButton { background-color: transparent; }");
    HidePassword1->hide();
    connect(HidePassword1, &QPushButton::clicked, this, &FindAndSignUpWidget::onHidePassword1clicked);

    HidePassword2 = new QPushButton(this);
    HidePassword2->setIcon(QIcon(":/image/image/Icon/eye_close.png"));
    HidePassword2->setIconSize(QSize(20,20));
    HidePassword2->setGeometry(ui->Password2LineEdit->x()+275,ui->Password2LineEdit->y()+25,20,20);
    HidePassword2->setStyleSheet("QPushButton { background-color: transparent; }");
    HidePassword2->hide();
    connect(HidePassword2, &QPushButton::clicked, this, &FindAndSignUpWidget::onHidePassword2clicked);

    connect(ui->SendKeyPushButton,&QPushButton::clicked,this,&FindAndSignUpWidget::onSendKeyPushButtonclicked);
    connect(ui->EnterKeyPushButton,&QPushButton::clicked,this,&FindAndSignUpWidget::onEnterKeyPushButtonclicked);
    connect(ui->EnterPushButton,&QPushButton::clicked,this,&FindAndSignUpWidget::onEnterPushButtonclicked);

    message_center = MessageCenter::getInstance();
    widget_rev_packer = WidgetRevPacker::getInstance();

    message_center->loadInterface("interfaceForgetPasswordSuccess", std::bind(&FindAndSignUpWidget::interfaceForgetPasswordSuccess, this, std::placeholders::_1));
    message_center->loadInterface("interfaceForgetPasswordFail",    std::bind(&FindAndSignUpWidget::interfaceForgetPasswordFail, this, std::placeholders::_1));
    message_center->loadInterface("interfaceRegisterSuccess", std::bind(&FindAndSignUpWidget::interfaceRegisterSuccess, this, std::placeholders::_1));
    message_center->loadInterface("interfaceForgetPasswordMailFail",    std::bind(&FindAndSignUpWidget::interfaceForgetPasswordMailFail, this, std::placeholders::_1));
    message_center->loadInterface("interfaceRegisterMailFail",    std::bind(&FindAndSignUpWidget::interfaceRegisterMailFail, this, std::placeholders::_1));
    message_center->loadInterface("interfaceForgetPasswordMailSuccess",    std::bind(&FindAndSignUpWidget::interfaceForgetPasswordMailSuccess, this, std::placeholders::_1));
    message_center->loadInterface("interfaceRegisterMailSuccess",    std::bind(&FindAndSignUpWidget::interfaceRegisterMailSuccess, this, std::placeholders::_1));


}

FindAndSignUpWidget::~FindAndSignUpWidget()
{
    delete ui;


}

void FindAndSignUpWidget::onShowPassword1clicked()
{
    ShowPassword1->hide(); HidePassword1->show();
    ui->Password1LineEdit->setEchoMode(QLineEdit::Normal);
}

void FindAndSignUpWidget::onShowPassword2clicked()
{
    ShowPassword2->hide(); HidePassword2->show();
    ui->Password2LineEdit->setEchoMode(QLineEdit::Normal);
}

void FindAndSignUpWidget::onHidePassword1clicked()
{
    ShowPassword1->show(); HidePassword1->hide();
    ui->Password1LineEdit->setEchoMode(QLineEdit::Password);
}

void FindAndSignUpWidget::onHidePassword2clicked()
{
    ShowPassword2->show(); HidePassword2->hide();
    ui->Password2LineEdit->setEchoMode(QLineEdit::Password);
}

void FindAndSignUpWidget::onSendKeyPushButtonclicked()
{
    qDebug()<<"Send Verify Code";
    Email = ui->MailLineEdit->text();
    VerificationCode = ui->KeyLineEdit->text();
    Username = ui->UsernameLineEdit->text();
    Password1 = ui->Password1LineEdit->text();
    Password2 = ui->Password2LineEdit->text();
    if(mode==0) //find password
    {
        WidgetArgPackage* package = new WidgetArgPackage();
        package->packMessage<WidgetArgAccount>(ACCOUNT_OPCODE::REGISTER_MAIL, Email.toStdString(), "", "", "", VerificationCode.toStdString());
        widget_rev_packer->WidgetsendMessage(package);
    }
    else    //register
    {
        WidgetArgPackage* package = new WidgetArgPackage();
        package->packMessage<WidgetArgAccount>(ACCOUNT_OPCODE::FORGET_PASSWORD_MAIL, Email.toStdString(), "", "", "", VerificationCode.toStdString());
        widget_rev_packer->WidgetsendMessage(package);
    }
}


void FindAndSignUpWidget::onEnterPushButtonclicked() //send infomation
{
    qDebug() << "send infomation";
    Email = ui->MailLineEdit->text();
    VerificationCode = ui->KeyLineEdit->text();
    Username = ui->UsernameLineEdit->text();
    Password1 = ui->Password1LineEdit->text();
    Password2 = ui->Password2LineEdit->text();
    if(Password1 != Password2)
    {
        qDebug() << "两次密码不相同";
        return;
    }
    if(mode==0) //register
    {
        WidgetArgPackage* package = new WidgetArgPackage();
        package->packMessage<WidgetArgAccount>(ACCOUNT_OPCODE::REGISTER, Email.toStdString(), "", Password1.toStdString(), Username.toStdString(), VerificationCode.toStdString());
        widget_rev_packer->WidgetsendMessage(package);
    }
    else    //findpassword
    {
        WidgetArgPackage* package = new WidgetArgPackage();
        package->packMessage<WidgetArgAccount>(ACCOUNT_OPCODE::FORGET_PASSWORD, Email.toStdString(), "", Password1.toStdString(), Username.toStdString(), VerificationCode.toStdString());
        widget_rev_packer->WidgetsendMessage(package);
    }
}

//确定验证码按钮点击，修改界面尺寸，显示其它输入框，删除按钮
void FindAndSignUpWidget::onEnterKeyPushButtonclicked() //verify code
{
    qDebug() << "verify code";
    Email = ui->MailLineEdit->text();
    VerificationCode = ui->KeyLineEdit->text();
    Username = ui->UsernameLineEdit->text();
    Password1 = ui->Password1LineEdit->text();
    Password2 = ui->Password2LineEdit->text();
    if(mode==0) //register
    {
        WidgetArgPackage* package = new WidgetArgPackage();
        package->packMessage<WidgetArgAccount>(ACCOUNT_OPCODE::REGISTER_MAIL_CODE_VERIFY, Email.toStdString(), "", "", "", VerificationCode.toStdString());
        widget_rev_packer->WidgetsendMessage(package);
    }
    else    //findpassword
    {
        WidgetArgPackage* package = new WidgetArgPackage();
        package->packMessage<WidgetArgAccount>(ACCOUNT_OPCODE::FORGET_PASSWORD_MAIL_CODE_VERIFY, Email.toStdString(), "", "", "", VerificationCode.toStdString());
        widget_rev_packer->WidgetsendMessage(package);
    }
}

//***********************************INTERFACE********************************************
void FindAndSignUpWidget::interfaceForgetPasswordMailFail(WidgetArgPackage* arg)
{
    qDebug() << "验证码错误";
    WidgetArgStatus *status = static_cast<WidgetArgStatus*>(arg->package);
    std::cout << "ForgetPasswordMail Fail, code: " << status->status << std::endl;

    delete arg;
}
void FindAndSignUpWidget::interfaceRegisterMailFail(WidgetArgPackage* arg)
{
    qDebug() << "验证码错误";
    WidgetArgStatus *status = static_cast<WidgetArgStatus*>(arg->package);
    std::cout << "RegisterMail Fail, code: " << status->status << std::endl;

    delete arg;
}
void FindAndSignUpWidget::interfaceForgetPasswordMailSuccess(WidgetArgPackage* arg)
{
    qDebug() << "验证码正确";
    this->setFixedSize(600,750);
    ui->EnterKeyPushButton->hide();
    ui->Password1LineEdit->setGeometry(150,330,300,70);
    ui->Password1LineEdit->show();
    ui->Password2LineEdit->setGeometry(150,460,300,70);
    ui->Password2LineEdit->show();
    ui->EnterPushButton->setGeometry(180,590,240,60);
    ui->EnterPushButton->show();
    ShowPassword1->setGeometry(ui->Password1LineEdit->x()+275,ui->Password1LineEdit->y()+25,20,20);
    ShowPassword2->setGeometry(ui->Password2LineEdit->x()+275,ui->Password2LineEdit->y()+25,20,20);
    HidePassword1->setGeometry(ui->Password1LineEdit->x()+275,ui->Password1LineEdit->y()+25,20,20);
    HidePassword2->setGeometry(ui->Password2LineEdit->x()+275,ui->Password2LineEdit->y()+25,20,20);
}
void FindAndSignUpWidget::interfaceRegisterMailSuccess(WidgetArgPackage* arg)
{
    qDebug() << "验证码正确";
    this->setFixedSize(600,900);
    ui->EnterKeyPushButton->hide();
    ui->UsernameLineEdit->show();
    ui->Password1LineEdit->show();
    ui->Password2LineEdit->show();
    ui->EnterPushButton->show();
}
void FindAndSignUpWidget::interfaceForgetPasswordSuccess(WidgetArgPackage* arg)
{
    qDebug() << "密码重设成功";
    this->close();
}
void FindAndSignUpWidget::interfaceForgetPasswordFail(WidgetArgPackage* arg)
{
    WidgetArgStatus *status = static_cast<WidgetArgStatus*>(arg->package);
    std::cout << "ForgetPassword Fail, code: " << status->status << std::endl;

    delete arg;
}
void FindAndSignUpWidget::interfaceRegisterSuccess(WidgetArgPackage* arg)
{
    qDebug() << "注册成功";
    this->close();
}
void FindAndSignUpWidget::interfaceRegisterFail(WidgetArgPackage* arg)
{
    WidgetArgStatus *status = static_cast<WidgetArgStatus*>(arg->package);
    std::cout << "Register Fail, code: " << status->status << std::endl;

    delete arg;
}
//*****************************************************************************************
