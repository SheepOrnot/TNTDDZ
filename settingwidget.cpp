#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(int _Width,int _Height,QWidget *parent) :
    QWidget(parent),Width(_Width),Height(_Height),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
    this->setFixedSize(0.618*Width,0.618*Height);
    ui->BasicBtn          ->setGeometry(0.020*Width,  0.055*Height,  0.104*Width,  0.084*Height);
    ui->FrameBtn          ->setGeometry(0.020*Width,  0.203*Height,  0.104*Width,  0.084*Height);
    ui->NameListBtn       ->setGeometry(0.026*Width,  0.648*Height,  0.089*Width,  0.028*Height);
    ui->SoundEffectBtn    ->setGeometry(0.020*Width,  0.342*Height,  0.104*Width,  0.084*Height);
    ui->ResolutionComboBox->setGeometry(0.322*Width,  0.166*Height,  0.120*Width,  0.028*Height);
    ui->CardStyleComboBox ->setGeometry(0.322*Width,  0.129*Height,  0.120*Width,  0.028*Height);
    ui->CardStyleWord     ->setGeometry(0.276*Width,  0.129*Height,  0.042*Width,  0.028*Height);
    ui->ResolutionWord    ->setGeometry(0.276*Width,  0.166*Height,  0.042*Width,  0.028*Height);
    ui->BGMVolume         ->setGeometry(0.330*Width,  0.180*Height,  0.161*Width,  0.020*Height);
    ui->EffectVolume      ->setGeometry(0.330*Width,  0.240*Height,  0.161*Width,  0.020*Height);
    ui->CardBack          ->setGeometry(0.385*Width,  0.222*Height,  0.057*Width,  0.139*Height);
    ui->CardFront         ->setGeometry(0.270*Width,  0.222*Height,  0.057*Width,  0.139*Height);

    ui->LobbyBGMCheck     ->setGeometry(0.330*Width,  0.120*Height,  0.015*Width,  0.030*Height);
    ui->LobbyBGMWord      ->setGeometry(0.270*Width,  0.120*Height,  0.060*Width,  0.030*Height);
    ui->GameBGMWord       ->setGeometry(0.270*Width,  0.180*Height,  0.060*Width,  0.030*Height);
    ui->GameEffectWord    ->setGeometry(0.270*Width,  0.240*Height,  0.060*Width,  0.030*Height);


    ui->BGMVolume->hide();
    ui->EffectVolume->hide();
    ui->ResolutionComboBox->hide();
    ui->ResolutionWord->hide();
    ui->LobbyBGMCheck->hide();
    ui->LobbyBGMWord->hide();
    ui->GameBGMWord->hide();
    ui->GameEffectWord->hide();

    QStringList resolutionOptions;
    resolutionOptions << "3840x2160(16:9)"<<"2560*1600(16:10)"<< "2560*1440(16:9)"<<"1920*1200(16:10)"<<"1920*1080(16:9)"
            <<"1680*1050(16:10)"<<"1680*945(16:9)"<<"1440*900(16:9)"<<"1200*900(4:3)"<<"800*600(4:3)";
    ui->ResolutionComboBox->addItems(resolutionOptions);
    ui->ResolutionComboBox->setMaxVisibleItems(4);
    ui->ResolutionComboBox->setCurrentText(QString::number(Width)+"*"+QString::number(Height));
    //ui->ResolutionComboBox->setCurrentIndex(4);

    connect(ui->BasicBtn,&QPushButton::clicked,this,&SettingWidget::onBasicBtnClicked);
    connect(ui->FrameBtn,&QPushButton::clicked,this,&SettingWidget::onFrameBtnClicked);
    connect(ui->SoundEffectBtn,&QPushButton::clicked,this,&SettingWidget::onSoundEffectBtnClicked);


}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::onBasicBtnClicked()
{
    ui->BGMVolume->hide();
    ui->EffectVolume->hide();
    ui->ResolutionComboBox->hide();
    ui->ResolutionWord->hide();
    ui->LobbyBGMCheck->hide();
    ui->LobbyBGMWord->hide();
    ui->GameBGMWord->hide();
    ui->GameEffectWord->hide();
    ui->CardBack->show();
    ui->CardFront->show();
    ui->CardStyleComboBox->show();
    ui->CardStyleWord->show();
}

void SettingWidget::onFrameBtnClicked()
{
    ui->BGMVolume->hide();
    ui->EffectVolume->hide();
    ui->ResolutionComboBox->show();
    ui->ResolutionWord->show();
    ui->LobbyBGMCheck->hide();
    ui->LobbyBGMWord->hide();
    ui->GameBGMWord->hide();
    ui->GameEffectWord->hide();
    ui->CardBack->hide();
    ui->CardFront->hide();
    ui->CardStyleComboBox->hide();
    ui->CardStyleWord->hide();
}

void SettingWidget::onSoundEffectBtnClicked()
{
    ui->BGMVolume->show();
    ui->EffectVolume->show();
    ui->LobbyBGMCheck->show();
    ui->LobbyBGMWord->show();
    ui->GameBGMWord->show();
    ui->GameEffectWord->show();
    ui->ResolutionComboBox->hide();
    ui->ResolutionWord->hide();
    ui->CardBack->hide();
    ui->CardFront->hide();
    ui->CardStyleComboBox->hide();
    ui->CardStyleWord->hide();
}
void SettingWidget::onApplyBtnClicked()
{
    gameBGMVolume = ui->BGMVolume->value()/100;
    gameEffectVolume = ui->EffectVolume->value()/100;

}
