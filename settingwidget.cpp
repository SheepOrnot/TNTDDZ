#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(int _Width,int _Height,QWidget *parent) :
    QWidget(parent),Width(_Width),Height(_Height),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
    this->setFixedSize(0.618*Width,0.618*Height);
    ImportConfig();
    ui->BasicBtn          ->setGeometry(0.020*Width,  0.055*Height,  0.104*Width,  0.084*Height);
    ui->FrameBtn          ->setGeometry(0.020*Width,  0.203*Height,  0.104*Width,  0.084*Height);
    ui->NameListBtn       ->setGeometry(0.026*Width,  0.588*Height,  0.089*Width,  0.028*Height);
    ui->SoundEffectBtn    ->setGeometry(0.020*Width,  0.342*Height,  0.104*Width,  0.084*Height);
    ui->ResolutionComboBox->setGeometry(0.322*Width,  0.166*Height,  0.120*Width,  0.028*Height);
    ui->CardStyleComboBox ->setGeometry(0.322*Width,  0.129*Height,  0.120*Width,  0.028*Height);
    ui->CardStyleWord     ->setGeometry(0.276*Width,  0.129*Height,  0.042*Width,  0.028*Height);
    ui->ResolutionWord    ->setGeometry(0.276*Width,  0.166*Height,  0.042*Width,  0.028*Height);
    ui->BGMVolume         ->setGeometry(0.350*Width,  0.180*Height,  0.161*Width,  0.020*Height);
    ui->EffectVolume      ->setGeometry(0.350*Width,  0.240*Height,  0.161*Width,  0.020*Height);
    ui->CardBack          ->setGeometry(0.385*Width,  0.222*Height,  0.057*Width,  0.139*Height);
    ui->CardFront         ->setGeometry(0.270*Width,  0.222*Height,  0.057*Width,  0.139*Height);
    ui->GameBGMCheck      ->setGeometry(0.330*Width,  0.181*Height,  0.015*Width,  0.030*Height);
    ui->GameEffectCheck   ->setGeometry(0.330*Width,  0.240*Height,  0.015*Width,  0.030*Height);
    ui->LobbyBGMCheck     ->setGeometry(0.330*Width,  0.120*Height,  0.015*Width,  0.030*Height);
    ui->LobbyBGMWord      ->setGeometry(0.270*Width,  0.120*Height,  0.060*Width,  0.030*Height);
    ui->GameBGMWord       ->setGeometry(0.270*Width,  0.180*Height,  0.060*Width,  0.030*Height);
    ui->GameEffectWord    ->setGeometry(0.270*Width,  0.240*Height,  0.060*Width,  0.030*Height);
    ui->ApplyBtn          ->setGeometry(0.490*Width,  0.520*Height,  0.080*Width,  0.070*Height);
    ui->CancelBtn         ->setGeometry(0.390*Width,  0.520*Height,  0.080*Width,  0.070*Height);

    ui->BGMVolume->setRange(0,100);
    ui->EffectVolume->setRange(0,100);
    ui->BGMVolume->hide();
    ui->EffectVolume->hide();
    ui->ResolutionComboBox->hide();
    ui->ResolutionWord->hide();
    ui->LobbyBGMCheck->hide();
    ui->LobbyBGMWord->hide();
    ui->GameBGMWord->hide();
    ui->GameEffectWord->hide();
    ui->GameBGMCheck->hide();
    ui->GameEffectCheck->hide();


    QStringList resolutionOptions;
    resolutionOptions << "3840x2160(16:9)"<<"2560*1600(16:10)"<< "2560*1440(16:9)"<<"1920*1200(16:10)"<<"1920*1080(16:9)"
            <<"1680*1050(16:10)"<<"1680*945(16:9)"<<"1440*900(16:9)"<<"1200*900(4:3)"<<"800*600(4:3)";
    ui->ResolutionComboBox->addItems(resolutionOptions);
    ui->ResolutionComboBox->setMaxVisibleItems(4);
    ui->ResolutionComboBox->setCurrentIndex(ResolutionIndex);

    ui->CardStyleComboBox->setCurrentIndex(CardStyleIndex);
    QString CardFrontPath = ":/image/image/Cards_"+QString::number(CardStyleIndex)+"/6_of_hearts.png";
    CardFrontPixmap = QPixmap(CardFrontPath);                                   qDebug()<<CardFrontPath;
    CardFrontPixmap = CardFrontPixmap.scaled(ui->CardFront->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->CardFront->setPixmap(CardFrontPixmap);
    ui->CardFront->setScaledContents(true);

    QString CardBackPath = ":/image/image/Cards_"+QString::number(CardStyleIndex)+"/back.png";
    CardBackPixmap = QPixmap(CardBackPath);                                     qDebug()<<CardBackPath;
    CardBackPixmap = CardBackPixmap.scaled(ui->CardBack->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->CardBack->setPixmap(CardBackPixmap);
    ui->CardBack->setScaledContents(true);

    connect(ui->BasicBtn,&QPushButton::clicked,this,&SettingWidget::onBasicBtnClicked);
    connect(ui->FrameBtn,&QPushButton::clicked,this,&SettingWidget::onFrameBtnClicked);
    connect(ui->SoundEffectBtn,&QPushButton::clicked,this,&SettingWidget::onSoundEffectBtnClicked);
    connect(ui->ApplyBtn,&QPushButton::clicked,this,&SettingWidget::onApplyBtnClicked);

    connect(ui->BGMVolume, &QSlider::valueChanged,this,&SettingWidget::onBGMVolumeChanged);
    connect(ui->EffectVolume, &QSlider::valueChanged,this,&SettingWidget::onEffectVolumeChanged);

    connect(ui->GameBGMCheck,&QCheckBox::stateChanged,this,&SettingWidget::onBGMCheckChanged);
    connect(ui->GameEffectCheck,&QCheckBox::stateChanged,this,&SettingWidget::onEffectCheckChanged);
    connect(ui->CardStyleComboBox,&QComboBox::currentIndexChanged,this,&SettingWidget::onCardStyleChanged);

    qDebug()<<"Structure a new SettingWidget";
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
    ui->GameBGMCheck->hide();
    ui->GameEffectCheck->hide();
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
    ui->GameBGMCheck->hide();
    ui->GameEffectCheck->hide();
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
    ui->GameBGMCheck->show();
    ui->GameEffectCheck->show();
}
void SettingWidget::onApplyBtnClicked()
{
    NewGameBGMVolume = QString::number((double)ui->BGMVolume->value());
    NewGameEffectVolume = QString::number((double)ui->EffectVolume->value());
    QRegularExpression re("(\\d+)");
    QRegularExpressionMatch match = re.match(ui->ResolutionComboBox->currentText());
    for (int i = 0; i < 2; ++i) {
        if (match.hasMatch()) {
            if (i == 0) {
                NewWidth = QString::number(match.captured(1).toInt());
            } else if (i == 1) {
                NewHeight = QString::number(match.captured(1).toInt());
            }
        } else {
            break;
        }
        match = re.match(ui->ResolutionComboBox->currentText(), match.capturedEnd());
    }

    NewLobbyBGM  = (ui->LobbyBGMCheck  ->checkState()==Qt::Checked) ? "1" : "0";
    NewGameBGM   = (ui->GameBGMCheck   ->checkState()==Qt::Checked) ? "1" : "0";
    NewGameEffect= (ui->GameEffectCheck->checkState()==Qt::Checked) ? "1" : "0";

    NewCardStyleIndex = QString::number(ui->CardStyleComboBox->currentIndex());
    NewResolutionIndex = QString::number(ui->ResolutionComboBox->currentIndex());
    QFile file("./config/config.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open JSON file";
        return;
    }

    // 读取JSON内容
    QByteArray jsonData = file.readAll();
    file.close();

    // 解析JSON
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isObject()) {
        qDebug() << "JSON content is not an object";
        return ;
    }

    QJsonObject json = doc.object();
    QJsonObject gameSection = json["Game"].toObject();
    gameSection["Effect"] = NewGameEffect;
    gameSection["GameBGM"] = NewGameBGM;
    gameSection["EffectVolume"] = NewGameEffectVolume;
    gameSection["BGMVolume"] = NewGameBGMVolume;
    gameSection["Card"] = NewCardStyleIndex;

    json["Game"] = gameSection;

    QJsonObject lobbySection = json["Lobby"].toObject();
    lobbySection["LobbyBGM"] = NewLobbyBGM;
    json["Lobby"] = lobbySection;

    QJsonObject universalSection = json["Universal"].toObject();
    universalSection["Width"] = NewWidth;
    universalSection["Height"] = NewHeight;
    universalSection["Index"] = NewResolutionIndex;
    json["Universal"] = universalSection;

    QByteArray updatedJsonData = QJsonDocument(json).toJson();
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open JSON file for writing";
    }
    file.write(updatedJsonData);
    file.close();

    qDebug() << "JSON file updated successfully";
    QDialog dialog;
    dialog.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    dialog.setWindowTitle("");
    dialog.resize(0.25*Width, 0.25*Height); // 设置对话框的尺寸

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QLabel *label = new QLabel("重启后生效设置！");
    layout->addWidget(label);
    QPushButton *button = new QPushButton("确定");
    layout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.exec();


    this->close();
    this->deleteLater();
}
void SettingWidget::ImportConfig()
{
    QFile ConfigFile("./config/config.json");
    if (ConfigFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray jsonData = ConfigFile.readAll();
        ConfigFile.close();
        // 解析JSON数据
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        if (!jsonDoc.isNull())
        {
            if (jsonDoc.isObject())
            {
                QJsonObject jsonObj = jsonDoc.object();
                QJsonObject GameObj = jsonObj["Game"].toObject();
                QJsonObject LobbyObj = jsonObj["Lobby"].toObject();
                QJsonObject UniversalObj = jsonObj["Universal"].toObject();

                // 获取JSON中的键值对
                LobbyBGMState = bool(LobbyObj.value("LobbyBGM").toVariant().toInt());
                GameBGMState =  bool(GameObj.value("GameBGM").toVariant().toInt());
                GameEffectState = bool(GameObj.value("Effect").toVariant().toInt());
                GameBGMVolume = GameObj.value("BGMVolume").toVariant().toInt();
                GameEffectVolume = GameObj.value("EffectVolume").toVariant().toInt();
                ResolutionIndex =  UniversalObj.value("Index").toVariant().toInt();
                CardStyleIndex =  GameObj.value("Card").toVariant().toInt();
            }
            else
            {
                qDebug() << "JSON document is not an object.";
            }
        }
        else
        {
            qDebug() << "Failed to load JSON document.";
        }
    }
    if(LobbyBGMState==true)ui->LobbyBGMCheck->setCheckState(Qt::Checked);
    if(GameBGMState==true)
    {
        ui->GameBGMCheck->setCheckState(Qt::Checked);
        ui->BGMVolume->setValue(GameBGMVolume);
    }
    else
    {
        ui->BGMVolume->setValue(0);

    }
    if(GameEffectState==true)
    {
        ui->GameEffectCheck->setCheckState(Qt::Checked);
        ui->EffectVolume->setValue(GameEffectVolume);
    }
    else
    {
        ui->EffectVolume->setValue(0);

    }

}

void SettingWidget::onBGMVolumeChanged()
{
    if(ui->BGMVolume->value()==0)
        ui->GameBGMCheck->setCheckState(Qt::Unchecked);
    else  ui->GameBGMCheck->setCheckState(Qt::Checked);
}
void SettingWidget::onEffectVolumeChanged()
{
    if(ui->EffectVolume->value()==0)
        ui->GameEffectCheck->setCheckState(Qt::Unchecked);
    else  ui->GameEffectCheck->setCheckState(Qt::Checked);
}
void SettingWidget::onBGMCheckChanged()
{
    if(ui->GameBGMCheck->checkState()==Qt::Unchecked)
        ui->BGMVolume->setValue(0);
}
void SettingWidget::onEffectCheckChanged()
{
    if(ui->GameEffectCheck->checkState()==Qt::Unchecked)
        ui->EffectVolume->setValue(0);
}
void SettingWidget::onCardStyleChanged(int index)
{
    QString CardFrontPath = ":/image/image/Cards_"+QString::number(index)+"/6_of_hearts.png";
    CardFrontPixmap = QPixmap(CardFrontPath);                                   qDebug()<<CardFrontPath;
    CardFrontPixmap = CardFrontPixmap.scaled(ui->CardFront->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->CardFront->setPixmap(CardFrontPixmap);;

    QString CardBackPath = ":/image/image/Cards_"+QString::number(index)+"/back.png";
    CardBackPixmap = QPixmap(CardBackPath);                                     qDebug()<<CardBackPath;
    CardBackPixmap = CardBackPixmap.scaled(ui->CardBack->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->CardBack->setPixmap(CardBackPixmap);
}
