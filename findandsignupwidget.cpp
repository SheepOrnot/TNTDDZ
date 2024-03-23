#include "findandsignupwidget.h"
#include "ui_findandsignupwidget.h"
#include <QDebug>
FindAndSignUpWidget::FindAndSignUpWidget(int _mode,QWidget *parent):
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
    connect(ShowPassword1, &QPushButton::clicked, this, &FindAndSignUpWidget::on_ShowPassword1_clicked);

    ShowPassword2 = new QPushButton(this);
    ShowPassword2->setIcon(QIcon(":/image/image/Icon/eye_open.png"));
    ShowPassword2->setIconSize(QSize(20,20));
    ShowPassword2->setGeometry(ui->Password2LineEdit->x()+275,ui->Password2LineEdit->y()+25,20,20);
    ShowPassword2->setStyleSheet("QPushButton { background-color: transparent; }");
    connect(ShowPassword2, &QPushButton::clicked, this, &FindAndSignUpWidget::on_ShowPassword2_clicked);


    HidePassword1 = new QPushButton(this);
    HidePassword1->setIcon(QIcon(":/image/image/Icon/eye_close.png"));
    HidePassword1->setIconSize(QSize(20,20));
    HidePassword1->setGeometry(ui->Password1LineEdit->x()+275,ui->Password1LineEdit->y()+25,20,20);
    HidePassword1->setStyleSheet("QPushButton { background-color: transparent; }");
    HidePassword1->hide();
    connect(HidePassword1, &QPushButton::clicked, this, &FindAndSignUpWidget::on_HidePassword1_clicked);

    HidePassword2 = new QPushButton(this);
    HidePassword2->setIcon(QIcon(":/image/image/Icon/eye_close.png"));
    HidePassword2->setIconSize(QSize(20,20));
    HidePassword2->setGeometry(ui->Password2LineEdit->x()+275,ui->Password2LineEdit->y()+25,20,20);
    HidePassword2->setStyleSheet("QPushButton { background-color: transparent; }");
    HidePassword2->hide();
    connect(HidePassword2, &QPushButton::clicked, this, &FindAndSignUpWidget::on_HidePassword2_clicked);

}

FindAndSignUpWidget::~FindAndSignUpWidget()
{
    delete ui;


}
//确定验证码按钮点击，修改界面尺寸，显示其它输入框，删除按钮
void FindAndSignUpWidget::on_EnterKeyPushButton_clicked()
{
    if(mode==0)
    {
        this->setFixedSize(600,900);
        ui->EnterKeyPushButton->hide();
        ui->UsernameLineEdit->show();
        ui->Password1LineEdit->show();
        ui->Password2LineEdit->show();
        ui->EnterPushButton->show();
    }
    else
    {
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
}
void FindAndSignUpWidget::on_ShowPassword1_clicked()
{
    ShowPassword1->hide(); HidePassword1->show();
    ui->Password1LineEdit->setEchoMode(QLineEdit::Normal);
}

void FindAndSignUpWidget::on_ShowPassword2_clicked()
{
    ShowPassword2->hide(); HidePassword2->show();
    ui->Password2LineEdit->setEchoMode(QLineEdit::Normal);
}

void FindAndSignUpWidget::on_HidePassword1_clicked()
{
    ShowPassword1->show(); HidePassword1->hide();
    ui->Password1LineEdit->setEchoMode(QLineEdit::Password);
}

void FindAndSignUpWidget::on_HidePassword2_clicked()
{
    ShowPassword2->show(); HidePassword2->hide();
    ui->Password2LineEdit->setEchoMode(QLineEdit::Password);
}
