#include "lobbywidget.h"
#include "ui_lobbywidget.h"
#include<QDebug>
#include<QPropertyAnimation>
LobbyWidget::LobbyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LobbyWidget)
{
    ui->setupUi(this);
    //*******本地获取的配置数据
    Width = 1920; Height = 1080;
    //*******end

    //*******从服务器获取的配置数据（测试用）
    ProfileImagePath = ":/image/image/Profile/mjq.jpg";
    BeanNum = "12345";
    DiamondNum = "1234567";
    //*******end
    RollImageIndex = 0;
    this->setFixedSize(Width,Height);
    ui->ProfileLabel->setGeometry(0.020*Width,0.018*Height,0.067*Width,0.120*Height);
    ui->UsernameLabel->setGeometry(0.109*Width,0.027*Height,0.094*Width,0.028*Height);
    ui->UidLabel->setGeometry(0.109*Width,0.083*Height,0.094*Width,0.028*Height);
    ui->GifLabel->setGeometry(0.057*Width,0.194*Height,0.240*Width,0.704*Height);
    ui->BeanLabel->setGeometry(0.406*Width,0.018*Height,0.021*Width,0.037*Height);
    ui->BeanEdit->setGeometry(0.432*Width,0.018*Height,0.089*Width,0.047*Height);
    ui->AddBeanBtn->setGeometry(0.516*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->DiamondLabel->setGeometry(0.578*Width,0.018*Height,0.021*Width,0.037*Height);
    ui->DiamondEdit->setGeometry(0.604*Width,0.018*Height,0.089*Width,0.047*Height);
    ui->AddDiamondBtn->setGeometry(0.687*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->RuleBtn->setGeometry(0.927*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->SettingBtn->setGeometry(0.963*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->RollLabel->setGeometry(0.604*Width,0.166*Height,0.328*Width,0.463*Height);
    ui->ClassicModeBtn->setGeometry(0.682*Width,0.652*Height,0.161*Width,0.084*Height);
    ui->ExitGameBtn->setGeometry(0.682*Width,0.763*Height,0.161*Width,0.084*Height);

    ui->SettingBtn->setIcon(QIcon(":/image/image/Icon/setting.png"));
    ui->SettingBtn->setStyleSheet("QPushButton { background-color: transparent; }");

    ui->RuleBtn->setIcon(QIcon(":/image/image/Icon/rule.png"));
    ui->RuleBtn->setStyleSheet("QPushButton { background-color: transparent; }");

    ui->AddBeanBtn->setIcon(QIcon(":/image/image/Icon/buy.png"));
    ui->AddBeanBtn->setStyleSheet("QPushButton { background-color: transparent; }");

    ui->AddDiamondBtn->setIcon(QIcon(":/image/image/Icon/buy.png"));
    ui->AddDiamondBtn->setStyleSheet("QPushButton { background-color: transparent; }");

    BeanPixmap = QPixmap(":/image/image/Icon/happybean.png");
    BeanPixmap = BeanPixmap.scaled(ui->BeanLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->BeanLabel->setPixmap(BeanPixmap);
    ui->BeanLabel->setScaledContents(true);

    DiamondPixmap = QPixmap(":/image/image/Icon/diamond.png");
    DiamondPixmap = DiamondPixmap.scaled(ui->DiamondLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->DiamondLabel->setPixmap(DiamondPixmap);
    ui->DiamondLabel->setScaledContents(true);


    //QPropertyAnimation *animation = new QPropertyAnimation(ui->RollLabel, "pixmap");
    RollImageTimer = new QTimer(this);
    connect(RollImageTimer, &QTimer::timeout, this, &LobbyWidget::RollImage);
    RollImageTimer->start(3000);
    QPixmap RollPixmap0(RollPixmapsPath[RollImageIndex++]);
    RollPixmap0 = RollPixmap0.scaled(ui->RollLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->RollLabel->setPixmap(RollPixmap0);
    ui->RollLabel->setScaledContents(true);

    ProfilePixmap = QPixmap(ProfileImagePath);
    ProfilePixmap = ProfilePixmap.scaled(ui->ProfileLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->ProfileLabel->setPixmap(ProfilePixmap);
    ui->ProfileLabel->setScaledContents(true);

    ui->BeanEdit->setText(BeanNum);
    ui->BeanEdit->setReadOnly(true);
    ui->BeanEdit->setStyleSheet("QLineEdit { border: 1px solid #555555; border-radius: 25px; background-color: transparent;font: 12pt Segoe Script; }");
    ui->BeanEdit->setAlignment(Qt::AlignHCenter);

    ui->DiamondEdit->setText(DiamondNum);
    ui->DiamondEdit->setReadOnly(true);
    ui->DiamondEdit->setStyleSheet("QLineEdit { border: 1px solid #555555; border-radius: 25px; background-color: transparent;font: 12pt Segoe Script; }");
    ui->DiamondEdit->setAlignment(Qt::AlignHCenter);
}

LobbyWidget::~LobbyWidget()
{
    delete ui;
}

void LobbyWidget::ResolutionChanged(int _Width,int _Height)
{
    Width = _Width;  Height = _Height;
    this->setFixedSize(Width,Height);
    ui->ProfileLabel->setGeometry(0.020*Width,0.018*Height,0.067*Width,0.120*Height);
    ui->UsernameLabel->setGeometry(0.109*Width,0.027*Height,0.094*Width,0.028*Height);
    ui->UidLabel->setGeometry(0.109*Width,0.083*Height,0.094*Width,0.028*Height);
    ui->GifLabel->setGeometry(0.057*Width,0.194*Height,0.240*Width,0.704*Height);
    ui->BeanLabel->setGeometry(0.406*Width,0.018*Height,0.021*Width,0.037*Height);
    ui->BeanEdit->setGeometry(0.432*Width,0.018*Height,0.089*Width,0.047*Height);
    ui->AddBeanBtn->setGeometry(0.516*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->DiamondLabel->setGeometry(0.578*Width,0.018*Height,0.021*Width,0.037*Height);
    ui->DiamondEdit->setGeometry(0.604*Width,0.018*Height,0.089*Width,0.047*Height);
    ui->AddDiamondBtn->setGeometry(0.687*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->RuleBtn->setGeometry(0.927*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->SettingBtn->setGeometry(0.963*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->RollLabel->setGeometry(0.604*Width,0.166*Height,0.328*Width,0.463*Height);
    ui->ClassicModeBtn->setGeometry(0.682*Width,0.652*Height,0.161*Width,0.084*Height);
    ui->ExitGameBtn->setGeometry(0.682*Width,0.763*Height,0.161*Width,0.084*Height);
    update();
}

void LobbyWidget::RollImage()
{

    QPixmap nextPixmap(RollPixmapsPath[RollImageIndex]);
    qDebug()<<"Next Picture";
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    ui->RollLabel->setGraphicsEffect(effect);
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(1000);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    nextPixmap = nextPixmap.scaled(ui->RollLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->RollLabel->setPixmap(nextPixmap);

    RollImageIndex = (RollImageIndex + 1) % 7;
}
