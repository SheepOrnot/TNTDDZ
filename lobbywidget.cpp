#include "lobbywidget.h"
#include "ui_lobbywidget.h"
#include<QDebug>
#include<QPropertyAnimation>
LobbyWidget::LobbyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LobbyWidget)
{
    ui->setupUi(this);
    ImportConfig();
    this->setFixedSize(Width,Height);

    if(isFullScreen)
    {
        this->setWindowFlags(Qt::FramelessWindowHint);  // 设置无边框
        this->showFullScreen();  // 全屏显示
        SettingWidth = Width; SettingHeight = Height;
        Width = this->width();
        Height = this->height();
    }

    radius = Height*0.047*0.5;
    InitInfo(5,6666666666,454645,"冷锋冷锋冷锋冷锋冷锋","00000001");
    this->setWindowTitle("TNT斗地主");
//*****************本地获取的配置数据***************

//********************end*************************

    BGMPlayer = new QMediaPlayer();
    BGMPlayer->setSource(QUrl("qrc:/sound/sound/BGM/lobbybgm.mp3"));
    BGMPlayer->setLoops(-1);
    BGMaudioOutput = new QAudioOutput();
    BGMaudioOutput->setVolume(0.5);
    BGMPlayer->setAudioOutput(BGMaudioOutput);
    if(BGMState) BGMPlayer->play();
    BGMThread = new QThread;
    BGMPlayer->moveToThread(BGMThread);
    BGMThread->start();
    connect(qApp, &QCoreApplication::aboutToQuit,BGMThread, &QThread::quit);


    RollImageIndex = 0;


    ui->ProfileLabel  ->setGeometry(0.020*Width,0.018*Height,0.067*Width,0.120*Height);
    ui->UsernameLabel ->setGeometry(0.109*Width,0.027*Height,0.094*Width,0.028*Height);
    ui->UidLabel      ->setGeometry(0.109*Width,0.083*Height,0.094*Width,0.028*Height);
    ui->GifLabel      ->setGeometry(0.057*Width,0.194*Height,0.240*Width,0.704*Height);
    ui->BeanLabel     ->setGeometry(0.406*Width,0.018*Height,0.021*Width,0.037*Height);
    ui->BeanEdit      ->setGeometry(0.432*Width,0.018*Height,0.089*Width,0.047*Height);
    ui->AddBeanBtn    ->setGeometry(0.516*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->DiamondLabel  ->setGeometry(0.578*Width,0.018*Height,0.021*Width,0.037*Height);
    ui->DiamondEdit   ->setGeometry(0.604*Width,0.018*Height,0.089*Width,0.047*Height);
    ui->AddDiamondBtn ->setGeometry(0.687*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->RuleBtn       ->setGeometry(0.927*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->SettingBtn    ->setGeometry(0.963*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->RollLabel     ->setGeometry(0.604*Width,0.166*Height,0.328*Width,0.463*Height);
    ui->ClassicModeBtn->setGeometry(0.682*Width,0.652*Height,0.161*Width,0.084*Height);
    ui->SingleModeBtn ->setGeometry(0.682*Width,0.763*Height,0.161*Width,0.084*Height);
    ui->JoinRoomBtn   ->setGeometry(0.682*Width,0.874*Height,0.161*Width,0.084*Height);
    ui->RoomId        ->setGeometry(0.560*Width,0.876*Height,0.120*Width,0.080*Height);
    ui->ExitBtn       ->setGeometry(0.860*Width,0.874*Height,0.080*Width,0.084*Height);


    ui->SettingBtn->setIcon(QIcon(":/image/image/Icon/setting.png"));
    ui->SettingBtn->setStyleSheet("QPushButton { background-color: transparent; }");
    connect(ui->SettingBtn,&QPushButton::clicked,this,&LobbyWidget::onSettingBtnClicked);

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
    RollImageTimer = new QTimer();
    connect(RollImageTimer, &QTimer::timeout, this, &LobbyWidget::RollImage);
    RollImageTimer->start(3000);

    QPixmap RollPixmap0(RollPixmapsPath[RollImageIndex++]);
    RollPixmap0 = RollPixmap0.scaled(ui->RollLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->RollLabel->setPixmap(RollPixmap0);
    ui->RollLabel->setScaledContents(true);

    connect(ui->ProfileLabel,&QPushButton::clicked,this,&LobbyWidget::onPersonalInfoBtnClicked);




    QString roomidstyle = QString("font: %1pt Microsoft YaHei UI").arg(Width*0.02);
    ui->RoomId->setStyleSheet(roomidstyle);
    ui->RoomId->setAlignment(Qt::AlignCenter);

    ui->SingleModeBtn->setText("单机模式");
    connect(ui->ClassicModeBtn,&QPushButton::clicked,this,&LobbyWidget::onClassicModeBtnClicked);
    connect(ui->SingleModeBtn,&QPushButton::clicked,this,&LobbyWidget::onSingleModeBtnClicked);
    connect(ui->AddDiamondBtn,&QPushButton::clicked,this,&LobbyWidget::onDiamondShopClicked);
    connect(ui->AddBeanBtn,&QPushButton::clicked,this,&LobbyWidget::onBeanShopClicked);
    connect(ui->RuleBtn,&QPushButton::clicked,this,&LobbyWidget::onRuleBtnClicked);
    connect(ui->ExitBtn,&QPushButton::clicked,[&]()
            {
        this->close();
    });
    connect(ui->JoinRoomBtn,&QPushButton::clicked,this,&LobbyWidget::onJoinRoomBtnClicked);

    message_center = MessageCenter::getInstance();
    widget_rev_packer = WidgetRevPacker::getInstance();
    
    message_center->loadInterface("interfaceEnterRoomSuccess", std::bind(&LobbyWidget::interfaceEnterRoomSuccess, this, std::placeholders::_1));
    message_center->loadInterface("interfaceEnterRoomFail",    std::bind(&LobbyWidget::interfaceEnterRoomFail,    this, std::placeholders::_1));
    message_center->loadInterface("interfaceExitRoom",         std::bind(&LobbyWidget::interfaceExitRoom,         this, std::placeholders::_1));
    message_center->loadInterface("interfaceInfoInit",         std::bind(&LobbyWidget::interfaceInfoInit,         this, std::placeholders::_1));
}

LobbyWidget::~LobbyWidget()
{
    delete ui;
}

void LobbyWidget::ResolutionChanged(int _Width,int _Height)
{
    Width = _Width;  Height = _Height;
    this->setFixedSize(Width,Height);
    ui->ProfileLabel  ->setGeometry(0.020*Width,0.018*Height,0.067*Width,0.120*Height);
    ui->UsernameLabel ->setGeometry(0.109*Width,0.027*Height,0.094*Width,0.028*Height);
    ui->UidLabel      ->setGeometry(0.109*Width,0.083*Height,0.094*Width,0.028*Height);
    ui->GifLabel      ->setGeometry(0.057*Width,0.194*Height,0.240*Width,0.704*Height);
    ui->BeanLabel     ->setGeometry(0.406*Width,0.018*Height,0.021*Width,0.037*Height);
    ui->BeanEdit      ->setGeometry(0.432*Width,0.018*Height,0.089*Width,0.047*Height);
    ui->AddBeanBtn    ->setGeometry(0.516*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->DiamondLabel  ->setGeometry(0.578*Width,0.018*Height,0.021*Width,0.037*Height);
    ui->DiamondEdit   ->setGeometry(0.604*Width,0.018*Height,0.089*Width,0.047*Height);
    ui->AddDiamondBtn ->setGeometry(0.687*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->RuleBtn       ->setGeometry(0.927*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->SettingBtn    ->setGeometry(0.963*Width,0.018*Height,0.026*Width,0.047*Height);
    ui->RollLabel     ->setGeometry(0.604*Width,0.166*Height,0.328*Width,0.463*Height);
    ui->ClassicModeBtn->setGeometry(0.682*Width,0.652*Height,0.161*Width,0.084*Height);
    ui->SingleModeBtn ->setGeometry(0.682*Width,0.763*Height,0.161*Width,0.084*Height);
    ui->JoinRoomBtn   ->setGeometry(0.682*Width,0.874*Height,0.161*Width,0.084*Height);
    ui->RoomId        ->setGeometry(0.600*Width,0.876*Height,0.080*Width,0.080*Height);
    ui->ExitBtn       ->setGeometry(0.800*Width,0.900*Height,0.080*Width,0.080*Height);

    ui->BeanEdit->setStyleSheet("QLineEdit { border: 1px solid #555555; border-radius: "+QString::number(radius)+"px; background-color: transparent;font: "+QString::number(0.5*radius)+"pt Segoe Script; }");
    ui->DiamondEdit->setStyleSheet("QLineEdit { border: 1px solid #555555; border-radius: "+QString::number(radius)+"px; background-color: transparent;font: "+QString::number(0.5*radius)+"pt Segoe Script; }");
    update();

}
void LobbyWidget::onSettingBtnClicked()
{
    settingWidget = new SettingWidget(Width,Height);
    settingWidget->show();
}
void LobbyWidget::RollImage()
{

    QPixmap nextPixmap(RollPixmapsPath[RollImageIndex]);
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

void LobbyWidget::ImportConfig()
{
    QString filePath = "./config/config.json";
    QFile ConfigFile(filePath);
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
                QJsonObject UniversalObj = jsonObj["Universal"].toObject();
                QJsonObject LobbyObj = jsonObj["Lobby"].toObject();

                // 获取JSON中的键值对
                Width = UniversalObj.value("Width").toVariant().toInt();
                Height = UniversalObj.value("Height").toVariant().toInt();
                BGMState = bool(LobbyObj.value("LobbyBGM").toVariant().toInt());
                isFullScreen = bool(UniversalObj.value("FullScreen").toVariant().toInt());
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
}

void LobbyWidget::onPersonalInfoBtnClicked()
{
    personalInfoWidget = new PersonalInfoWidget(Width,Height);
    personalInfoWidget->show();
}

void LobbyWidget::onClassicModeBtnClicked()            //创建房间按钮
{
    WidgetArgPackage* create_room_submit = new WidgetArgPackage();
    create_room_submit->packMessage<WidgetArgNetWork>(NETWORK::CREATE_ROOM, UID.toStdString(), "", 0, 0, 0, 0, 0);
    widget_rev_packer->WidgetsendMessage(create_room_submit);
}
void LobbyWidget::onJoinRoomBtnClicked()
{
    WidgetArgPackage* join_room_submit = new WidgetArgPackage();
    join_room_submit->packMessage<WidgetArgNetWork>(NETWORK::JOIN_ROOM, UID.toStdString(), ui->RoomId->text().toStdString(), 0, 0, 0, 0, 0);
    widget_rev_packer->WidgetsendMessage(join_room_submit);
}
void LobbyWidget::onExitGameBtnClicked()
{
    WidgetArgPackage* exit_room_submit = new WidgetArgPackage();
    exit_room_submit->packMessage<WidgetArgNetWork>(NETWORK::LEAVE_ROOM, UID.toStdString(), ui->RoomId->text().toStdString(), 0, 0, 0, 0, 0);
    widget_rev_packer->WidgetsendMessage(exit_room_submit);
}
void LobbyWidget::onSingleModeBtnClicked()
{
    qDebug() << "Play Single";
    WidgetArgPackage* create_room_submit = new WidgetArgPackage();
    create_room_submit->packMessage<WidgetArgPlayer>(PLAYER_OPCODE::CREATE_ROOM, 0, 3, 88888888, Username.toStdString(), UID.toStdString(), ui->RoomId->text().toStdString(), 0, 1);
    widget_rev_packer->WidgetsendMessage(create_room_submit);
}
//********************INTERFACE****************************
void LobbyWidget::EnterGame()
{
    qDebug() << "Classic Mode" << signlemode;
    gameWidget = new GameWidget(Width,Height,signlemode);
    this->hide();
    gameWidget->show();
    gameWidget->exitFunc = std::bind(&LobbyWidget::interfaceExitRoom,this,std::placeholders::_1);
    GameExitBtn = new QPushButton(gameWidget);
    GameExitBtn->setGeometry(0.010*Width,  0.018*Height,  0.042*Width,   0.075*Height);
    GameExitBtn->setIcon(QIcon(":/image/image/Icon/quitgame.png"));
    GameExitBtn->setStyleSheet("QPushButton { background-color: transparent; }");
    GameExitBtn->setIconSize(GameExitBtn->size());
    GameExitBtn->show();
    BGMPlayer->stop();
    connect(GameExitBtn,&QPushButton::clicked,this,&LobbyWidget::onExitGameBtnClicked);
}
void LobbyWidget::onDiamondShopClicked()
{
    SuperMarket = new SuperMarketWidget(Width,Height,0);
    SuperMarket->show();
}
void LobbyWidget::onBeanShopClicked()
{
    SuperMarket = new SuperMarketWidget(Width,Height,1);
    SuperMarket->show();
}
void LobbyWidget::onRuleBtnClicked()
{
    ruleWidget = new RuleWidget;
    ruleWidget->show();
}
void  LobbyWidget::InitInfo(int _ProfileImageIndex,long long _BeanNum,long long _DiamondNum, std::string _Username, std::string _UID)
{
    ProfileImageIndex= _ProfileImageIndex;
    ProfileImagePath =QString(":/image/image/Profile/%1.jpg").arg(ProfileImageIndex);
    BeanNum = Transform_To_String(_BeanNum);
    DiamondNum = Transform_To_String(_DiamondNum);
    Username = QString::fromStdString(_Username);
    UID = QString::fromStdString(_UID);

    ui->ProfileLabel->setIcon(QIcon(ProfileImagePath));
    ui->ProfileLabel->setStyleSheet("QPushButton { background-color: transparent; }");
    ui->ProfileLabel->setIconSize(ui->ProfileLabel->size());

    ui->BeanEdit->setText(BeanNum);
    ui->BeanEdit->setReadOnly(true);
    ui->BeanEdit->setStyleSheet("QLineEdit { border: 1px solid #555555; border-radius: "+QString::number(radius)+"px; background-color: transparent;font: "+QString::number(0.5*radius)+"pt Segoe Script; }");
    ui->BeanEdit->setAlignment(Qt::AlignHCenter);

    ui->DiamondEdit->setText(DiamondNum);
    ui->DiamondEdit->setReadOnly(true);
    ui->DiamondEdit->setStyleSheet("QLineEdit { border: 1px solid #555555; border-radius: "+QString::number(radius)+"px; background-color: transparent;font: "+QString::number(0.5*radius)+"pt Segoe Script; }");
    ui->DiamondEdit->setAlignment(Qt::AlignHCenter);

    ui->UsernameLabel->setStyleSheet("QLabel {font: 12pt 华文新魏; background-color: yellow}");
    ui->UsernameLabel->setText(Username);

    ui->UidLabel->setStyleSheet("QLabel {font: 12pt Segoe Script; background-color: yellow}");
    ui->UidLabel->setText(UID);
}
QString LobbyWidget::Transform_To_String(long long Num)
{
    QString Str;
    double head;
    if(Num>100000000)
    {
        head = Num/100000000.0;
        Str = QString::number(head,'f', 2)+"亿";
    }
    else Str = QString::number(Num);
    return Str;
}

void LobbyWidget::onExitBtnClicked()
{
    this->close();
}
void LobbyWidget::doInfoInit()
{
    WidgetArgPlayerInfo *player = static_cast<WidgetArgPlayerInfo*>(Arg->package);
    InitInfo(player->profile,player->peas,player->diamond,player->username,player->account);
    delete Arg;
}
void LobbyWidget::interfaceInfoInit(WidgetArgPackage* arg)
{
    Arg = arg;
    QThread *gameThread = new QThread();
    connect(gameThread, SIGNAL(started()), this, SLOT(doInfoInit()));
    gameThread->start();
}
void LobbyWidget::interfaceEnterRoomSuccess(WidgetArgPackage* arg)
{
    WidgetArgStatus *status = static_cast<WidgetArgStatus*>(arg->package);
    signlemode = status->status == -1;

    QThread *gameThread = new QThread();
    connect(gameThread, SIGNAL(started()), this, SLOT(EnterGame()));
    gameThread->start();
    
    delete arg;
}
void LobbyWidget::interfaceEnterRoomFail(WidgetArgPackage* arg)
{
    WidgetArgStatus *status = static_cast<WidgetArgStatus*>(arg->package);
    std::cout << "EnterRoom Fail, code: " << status->status << std::endl;

    delete arg;
}
void LobbyWidget::doExitRoom()
{
    this->show();
    disconnect(GameExitBtn,&QPushButton::clicked,this,&LobbyWidget::onExitGameBtnClicked);
    delete GameExitBtn;
    delete gameWidget;
    gameWidget->BGMPlayer->stop();
    if(BGMState) BGMPlayer->play();
}
void LobbyWidget::interfaceExitRoom(WidgetArgPackage* arg)
{
    QThread *qThread = new QThread();
    connect(qThread, SIGNAL(started()), this, SLOT(doExitRoom()));
    qThread->start();

    delete arg;
}
//*********************************************************
