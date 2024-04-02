#include "gamewidget.h"
#include "ui_gamewidget.h"
#include<QDebug>
#include<iostream>
GameWidget::GameWidget(int _Width,int _Height,QWidget *parent) :
    QWidget(parent),Width(_Width),Height(_Height),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    this->setFixedSize(Width,Height);
    ImportConfig();
    InitAllCards();

    BGMPlayer = new QMediaPlayer();
    BGMPlayer->setSource(QUrl("qrc:/sound/sound/BGM/gamebgm.mp3"));
    BGMPlayer->setLoops(-1);
    BGMaudioOutput = new QAudioOutput();
    BGMaudioOutput->setVolume(BGMVolume/100);
    BGMPlayer->setAudioOutput(BGMaudioOutput);
    if(BGMState) BGMPlayer->play();
    BGMThread = new QThread;
    BGMPlayer->moveToThread(BGMThread);
    BGMThread->start();
    connect(qApp, &QCoreApplication::aboutToQuit,BGMThread, &QThread::quit);

//****** 测试******
    //std::bitset<54> BitsetCards(std::string("111000111000000000110011001100110011101000000010001110"));
    QPushButton *GameOverbtn = new QPushButton(this);
    GameOverbtn->setGeometry(0.624*Width,  0.018*Height,  0.025*Width,   0.04*Height);
    GameOverbtn->show();
    connect(GameOverbtn,&QPushButton::clicked,[&](){
        gameoverWidget = new GameOverWidget(Width,Height);
        gameoverWidget->show();
    });

    std::bitset<54> BitsetCards(std::string("111111111111111111110000000000000000000000000000000000"));
    std::bitset<54>previousBitset(std::string("111111111111111111110000000000000000000000000000000000"));
    std::bitset<54>nextBitset(std::string("000000000000000000001111111111111111111100000000000000"));
    std::bitset<54>playerBitset(std::string("000000000000000000001111111110000000000000000000000000"));

    PlayerProfileNum = 0; PreviousProfileNum = 3; NextProfileNum = 4;
    PreviousIdentity = "landlord"; NextIdentity = "farmer"; PlayerIdentity = "farmer";
    PreviousBeanNum = "5.68W ";  NextBeanNum = "3266";  PlayerBeanNum = "359.62Y ";

    PlayerHandCards = Transform_To_Vector(BitsetCards);
    PreviousPlayerOutCards  = Transform_To_Vector(previousBitset);
    NextPlayerOutCards = Transform_To_Vector(nextBitset);
    PlayerOutCards = Transform_To_Vector(playerBitset);

    ShowIdentityIcon();                                 //调用展示身份图标函数

    placeHandCards();
    placeOutCards(1);
    placeOutCards(2);
    //placeOutCards(3);

//******end******

    //上家(previous)->1     下家(next)->2      自己->3
    ui->ProfileLabel1      ->setGeometry( 0.026*Width,  0.25 *Height,  0.063*Width,   0.121*Height);
    ui->ProfileLabel2      ->setGeometry( 0.906*Width,  0.259*Height,  0.063*Width,   0.121*Height);
    ui->ProfileLabel3      ->setGeometry( 0.062*Width,  0.824*Height,  0.063*Width,   0.121*Height);
    ui->IdentityLabel1     ->setGeometry( 0.046*Width,  0.203*Height,  0.021*Width,   0.037*Height);
    ui->IdentityLabel2     ->setGeometry( 0.927*Width,  0.212*Height,  0.021*Width,   0.037*Height);
    ui->IdentityLabel3     ->setGeometry( 0.083*Width,  0.777*Height,  0.021*Width,   0.037*Height);
    ui->BeansLineEdit1     ->setGeometry( 0.026*Width,  0.388*Height,  0.063*Width,   0.028*Height);
    ui->BeansLineEdit2     ->setGeometry( 0.906*Width,  0.398*Height,  0.063*Width,   0.028*Height);
    ui->BeansLineEdit3     ->setGeometry( 0.062*Width,  0.953*Height,  0.063*Width,   0.028*Height);
    ui->DoubleLabel1       ->setGeometry( 0.062*Width,  0.425*Height,  0.026*Width,   0.017*Height);
    ui->DoubleLabel2       ->setGeometry( 0.906*Width,  0.435*Height,  0.026*Width,   0.017*Height);
    ui->DoubleLabel3       ->setGeometry( 0.135*Width,  0.962*Height,  0.026*Width,   0.017*Height);
    ui->FinalCard1         ->setGeometry( 0.420*Width,  0.018*Height,  0.042*Width,   0.102*Height);
    ui->FinalCard2         ->setGeometry( 0.472*Width,  0.018*Height,  0.042*Width,   0.102*Height);
    ui->FinalCard3         ->setGeometry( 0.524*Width,  0.018*Height,  0.042*Width,   0.102*Height);
    ui->MultiplierLabel    ->setGeometry( 0.571*Width,  0.046*Height,  0.042*Width,   0.075*Height);
    ui->ClockImageLabel    ->setGeometry( 0.802*Width,  0.222*Height,  0.021*Width,   0.037*Height);
    ui->ClockNum           ->setGeometry( 0.808*Width,  0.231*Height,  0.010*Width,   0.019*Height);
    ui->RuleBtn            ->setGeometry( 0.901*Width,  0.018*Height,  0.031*Width,   0.056*Height);
    ui->SettingBtn         ->setGeometry( 0.942*Width,  0.018*Height,  0.031*Width,   0.056*Height);
    ui->CallLandlordBtn    ->setGeometry( 0.358*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->CallLandlordBtn     ->hide();
    ui->SkipCallLandlordBtn->setGeometry( 0.550*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->SkipCallLandlordBtn ->hide();
    ui->BidForLandlordBtn  ->setGeometry( 0.358*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->BidForLandlordBtn   ->hide();
    ui->SkipLandlordBidBtn ->setGeometry( 0.550*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->SkipLandlordBidBtn  ->hide();
    ui->PlayCardBtn        ->setGeometry( 0.358*Width,  0.680*Height,  0.083*Width,   0.047*Height);    //ui->PlayCardBtn         ->hide();
    ui->SkipTurnBtn        ->setGeometry( 0.550*Width,  0.680*Height,  0.083*Width,   0.047*Height);    //ui->SkipTurnBtn         ->hide();
    ui->DoubleBtn          ->setGeometry( 0.358*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->DoubleBtn           ->hide();
    ui->UnDoubleBtn        ->setGeometry( 0.520*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->UnDoubleBtn         ->hide();
    ui->ChatComboBox       ->setGeometry( 0.885*Width,  0.785*Height,  0.104*Width,   0.028*Height);
    ui->RoomId             ->setGeometry( 0.830*Width,  0.020*Height,  0.070*Width,   0.048*Height);

    ui->SettingBtn->setIcon(QIcon(":/image/image/Icon/setting.png"));
    ui->SettingBtn->setStyleSheet("QPushButton { background-color: transparent; }");
    connect(ui->SettingBtn,&QPushButton::clicked,this,&GameWidget::onSettingBtnClicked);

    ui->RuleBtn->setIcon(QIcon(":/image/image/Icon/rule.png"));
    ui->RuleBtn->setStyleSheet("QPushButton { background-color: transparent; }");

    BeanIcon = QIcon(":/image/image/Icon/happybean.png");
    ui->BeansLineEdit1->setReadOnly(true);
    ui->BeansLineEdit1->setStyleSheet("QLineEdit { border: 0px solid #555555;background-color: transparent;font: "+QString::number(Height*0.028*0.3)+"pt Segoe Script; }");
    ui->BeansLineEdit1->setAlignment(Qt::AlignHCenter);
    ui->BeansLineEdit1->addAction(BeanIcon, QLineEdit::LeadingPosition); // 添加图标（LeadingPosition为左侧位置）
    ui->BeansLineEdit1->setText(PreviousBeanNum);

    ui->BeansLineEdit2->setReadOnly(true);
    ui->BeansLineEdit2->setStyleSheet("QLineEdit { border: 0px solid #555555;background-color: transparent;font: "+QString::number(Height*0.028*0.3)+"pt Segoe Script; }");
    ui->BeansLineEdit2->setAlignment(Qt::AlignHCenter);
    ui->BeansLineEdit2->addAction(BeanIcon, QLineEdit::LeadingPosition); // 添加图标（LeadingPosition为左侧位置）
    ui->BeansLineEdit2->setText(NextBeanNum);

    ui->BeansLineEdit3->setReadOnly(true);
    ui->BeansLineEdit3->setStyleSheet("QLineEdit { border: 0px solid #555555;background-color: transparent;font: "+QString::number(Height*0.028*0.3)+"pt Segoe Script; }");
    ui->BeansLineEdit3->setAlignment(Qt::AlignHCenter);
    ui->BeansLineEdit3->addAction(BeanIcon, QLineEdit::LeadingPosition); // 添加图标（LeadingPosition为左侧位置）
    ui->BeansLineEdit3->setText(PlayerBeanNum);

    ProfilePixmap1 = QPixmap(ProfilePathIndex[PreviousProfileNum]);
    ProfilePixmap1 = ProfilePixmap1.scaled(ui->ProfileLabel1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->ProfileLabel1->setPixmap(ProfilePixmap1);
    ui->ProfileLabel1->setScaledContents(true);

    ProfilePixmap2 = QPixmap(ProfilePathIndex[NextProfileNum]);
    ProfilePixmap2 = ProfilePixmap2.scaled(ui->ProfileLabel2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->ProfileLabel2->setPixmap(ProfilePixmap2);
    ui->ProfileLabel2->setScaledContents(true);

    ProfilePixmap3 = QPixmap(ProfilePathIndex[PlayerProfileNum]);
    ProfilePixmap3 = ProfilePixmap3.scaled(ui->ProfileLabel3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->ProfileLabel3->setPixmap(ProfilePixmap3);
    ui->ProfileLabel3->setScaledContents(true);

    ClockPixmap = QPixmap(":/image/image/Icon/clock.png");
    ClockPixmap = ClockPixmap.scaled(ui->ClockImageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->ClockImageLabel->setPixmap(ClockPixmap);
    ui->ClockImageLabel->setScaledContents(true);
    ui->ClockNum->setStyleSheet("QLabel{ background-color: transparent;Color: gold;}");

    ui->ChatComboBox->addItem(" ...");
    ui->ChatComboBox->addItem("快点吧，我等的花都谢了");
    ui->ChatComboBox->addItem("你是MM,还是GG");
    ui->ChatComboBox->addItem("Option 3");
    ui->ChatComboBox->addItem("Option 4");
    ui->ChatComboBox->addItem("Option 5");
    ui->ChatComboBox->addItem("Option 6");
    ui->ChatComboBox->addItem("Option 7");
    ui->ChatComboBox->setMaxVisibleItems(5);

    connect(ui->PlayCardBtn,&QPushButton::clicked,this,&GameWidget::onPlayCardsClicked);
    qDebug()<<"Build GameWidget Completely";


}

GameWidget::~GameWidget()
{
    qDebug()<<"Destroy GameWidget";
    delete ui;
}

void GameWidget::InitAllCards()
{
    qDebug()<<"InitialCards CardStyle:"<<CardStyle;
    AllCards[53].Point = 17; AllCards[53].Type = 5;AllCards[53].Index = 53;
    AllCards[53].ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/red_of_joker.png";
    AllCards[52].Point = 16; AllCards[52].Type = 5;AllCards[52].Index = 52;
    AllCards[52].ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/black_of_joker.png";
    int i = 51;
    for(int j = 15; j>2; j--)
    {
        for(int k = 1; k<5; k++)
        {
            AllCards[i].Point = j; AllCards[i].Type = k; AllCards[i].Index = i;
            AllCards[i].ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/"+PointIndex[j]+"_of_"+TypeIndex[k]+".png";
            i--;
        }
    }
}

std::vector<WidgetCard> GameWidget::Transform_To_Vector(std::bitset<54> BitsetCards)
{
    std::vector<WidgetCard> TempCards;
    if(BitsetCards[53]==1)
    {
        TempCards.push_back(AllCards[53]);
    }
    if(BitsetCards[52]==1)
    {
        TempCards.push_back(AllCards[52]);
    }
    for(int i = 51; i>=0; i--)
    {
        if(BitsetCards[i]==0) continue;
        TempCards.push_back(AllCards[i]);
    }
    return TempCards;
}

std::bitset<54> GameWidget::Transform_To_Bitset(std::vector<WidgetCard> VectorCards)
{
    std::bitset<54> TempBits = 0;
    for(unsigned int i = 0;i< VectorCards.size();i++)
    {
        if(VectorCards[i].Point==17) {TempBits[53]=1; continue;}
        if(VectorCards[i].Point==16) {TempBits[52]=1; continue;}
        TempBits[(VectorCards[i].Point-3)*4+5-(VectorCards[i].Type+1)] = 1; qDebug()<< VectorCards[i].ImagePath<<"  "<<(VectorCards[i].Point-3)*4+5-(VectorCards[i].Type+1)<<" "<<VectorCards[i].Type;
    }
    return TempBits;
}


void GameWidget::ShowIdentityIcon()
{
    IdentityPixmap1 = QPixmap(":/image/image/Icon/"+PreviousIdentity+".png");
    IdentityPixmap1 = IdentityPixmap1.scaled(ui->IdentityLabel1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->IdentityLabel1->setPixmap(IdentityPixmap1);
    ui->IdentityLabel1->setScaledContents(true);

    IdentityPixmap2 = QPixmap(":/image/image/Icon/"+NextIdentity+".png");
    IdentityPixmap2 = IdentityPixmap2.scaled(ui->IdentityLabel1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->IdentityLabel2->setPixmap(IdentityPixmap2);
    ui->IdentityLabel2->setScaledContents(true);

    IdentityPixmap3 = QPixmap(":/image/image/Icon/"+PlayerIdentity+".png");
    IdentityPixmap3 = IdentityPixmap3.scaled(ui->IdentityLabel3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->IdentityLabel3->setPixmap(IdentityPixmap3);
    ui->IdentityLabel3->setScaledContents(true);

}

void GameWidget::onSettingBtnClicked()
{
    settingWidget = new SettingWidget(Width,Height);
    settingWidget->show();
}

void GameWidget::placeHandCards()
{
    for(int i = 0; i < PlayerHandCards.size(); i++)
    {
        PlayerHandCards[i].btn = new QPushButton(this);
        PlayerHandCards[i].btn->setIcon(QIcon(PlayerHandCards[i].ImagePath));
        PlayerHandCards[i].btn->setStyleSheet("QPushButton { background-color: transparent; }");
        PlayerHandCards[i].btn->setStyleSheet("QPushButton:disabled{color: black;}");
        PlayerHandCards[i].btn->setGeometry((0.198+0.03*i)*Width,0.796*Height,0.06*Width,0.148*Height);
        PlayerHandCards[i].btn->setIconSize(PlayerHandCards[i].btn->size());
        PlayerHandCards[i].btn->show();
    }
    ConnectHandCards();
}

void GameWidget::placeOutCards(int pos)
{
    if(pos == 1)
    {
        if(PreviousPlayerOutCards.size()<=10)
        {
            for(int i = 0; i < PreviousPlayerOutCards.size(); i++)
            {
                PreviousPlayerOutCards[i].btn = new QPushButton(this);
                PreviousPlayerOutCards[i].btn->setIcon(QIcon(PreviousPlayerOutCards[i].ImagePath));
                PreviousPlayerOutCards[i].btn->setStyleSheet("QPushButton { background-color: transparent; }");
                PreviousPlayerOutCards[i].btn->setGeometry((0.198+0.018*i)*Width,0.287*Height,0.036*Width,0.091*Height);
                PreviousPlayerOutCards[i].btn->setIconSize(PreviousPlayerOutCards[i].btn->size());
                PreviousPlayerOutCards[i].btn->show();
            }
        }
        else
        {
            for(int i = 0; i < 10; i++)
            {
                PreviousPlayerOutCards[i].btn = new QPushButton(this);
                PreviousPlayerOutCards[i].btn->setIcon(QIcon(PreviousPlayerOutCards[i].ImagePath));
                PreviousPlayerOutCards[i].btn->setStyleSheet("QPushButton { background-color: transparent; }");
                PreviousPlayerOutCards[i].btn->setGeometry((0.198+0.018*i)*Width,0.287*Height,0.036*Width,0.091*Height);
                PreviousPlayerOutCards[i].btn->setIconSize(PreviousPlayerOutCards[i].btn->size());
                PreviousPlayerOutCards[i].btn->show();
            }
            for(int i = 10; i < PreviousPlayerOutCards.size(); i++)
            {
                PreviousPlayerOutCards[i].btn = new QPushButton(this);
                PreviousPlayerOutCards[i].btn->setIcon(QIcon(PreviousPlayerOutCards[i].ImagePath));
                PreviousPlayerOutCards[i].btn->setStyleSheet("QPushButton { background-color: transparent; }");
                PreviousPlayerOutCards[i].btn->setGeometry((0.198+0.018*(i-10))*Width,0.34*Height,0.036*Width,0.091*Height);
                PreviousPlayerOutCards[i].btn->setIconSize(PreviousPlayerOutCards[i].btn->size());
                PreviousPlayerOutCards[i].btn->show();
            }
        }
    }
    if(pos == 2)
    {
        if(NextPlayerOutCards.size()<=10)
        {
            for(int i = 0; i < NextPlayerOutCards.size(); i++)
            {
                NextPlayerOutCards[i].btn = new QPushButton(this);
                NextPlayerOutCards[i].btn->setIcon(QIcon(NextPlayerOutCards[i].ImagePath));
                NextPlayerOutCards[i].btn->setStyleSheet("QPushButton { background-color: transparent; }");
                NextPlayerOutCards[i].btn->setGeometry((0.604+0.018*i)*Width,0.287*Height,0.036*Width,0.091*Height);
                NextPlayerOutCards[i].btn->setIconSize(NextPlayerOutCards[i].btn->size());
                NextPlayerOutCards[i].btn->show();
            }
        }
        else
        {
            for(int i = 0; i < 10; i++)
            {
                NextPlayerOutCards[i].btn = new QPushButton(this);
                NextPlayerOutCards[i].btn->setIcon(QIcon(NextPlayerOutCards[i].ImagePath));
                NextPlayerOutCards[i].btn->setStyleSheet("QPushButton { background-color: transparent; }");
                NextPlayerOutCards[i].btn->setGeometry((0.604+0.018*i)*Width,0.287*Height,0.036*Width,0.091*Height);
                NextPlayerOutCards[i].btn->setIconSize(NextPlayerOutCards[i].btn->size());
                NextPlayerOutCards[i].btn->show();
            }
            for(unsigned int i = 10; i < NextPlayerOutCards.size(); i++)
            {
                NextPlayerOutCards[i].btn = new QPushButton(this);
                NextPlayerOutCards[i].btn->setIcon(QIcon(NextPlayerOutCards[i].ImagePath));
                NextPlayerOutCards[i].btn->setStyleSheet("QPushButton { background-color: transparent; }");
                NextPlayerOutCards[i].btn->setGeometry((0.604+0.018*(i-10))*Width,0.34*Height,0.036*Width,0.091*Height);
                NextPlayerOutCards[i].btn->setIconSize(NextPlayerOutCards[i].btn->size());
                NextPlayerOutCards[i].btn->show();
            }
        }
    }
    if(pos == 3)
    {
        double StartX = 0.5-((0.036+(PlayerOutCards.size()-1)*0.018)/2);
        for(unsigned int i = 0; i < PlayerOutCards.size(); i++)
        {
            PlayerOutCards[i].btn = new QPushButton(this);
            PlayerOutCards[i].btn->setIcon(QIcon(PlayerOutCards[i].ImagePath));
            PlayerOutCards[i].btn->setStyleSheet("QPushButton { background-color: transparent; }");
            PlayerOutCards[i].btn->setGeometry((StartX+0.018*i)*Width,0.57*Height,0.036*Width,0.091*Height);
            PlayerOutCards[i].btn->setIconSize(PlayerOutCards[i].btn->size());
            PlayerOutCards[i].btn->show();
        }
    }
}

void GameWidget::ImportConfig()
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
                QJsonObject GameObj = jsonObj["Game"].toObject();
                BGMState = bool(GameObj.value("GameBGM").toVariant().toInt());
                EffectState = bool(GameObj.value("Effect").toVariant().toInt());
                CardStyle = GameObj.value("Card").toVariant().toInt();     qDebug()<<CardStyle;
                BGMVolume = GameObj.value("BGMVolume").toVariant().toDouble();
                EffectVolume = GameObj.value("EffectVolume").toVariant().toDouble();

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

void GameWidget::onPlayCardsClicked()
{
    SelectedCards =0;
    int HeadUnselectedCount = 0;
    DisconnectHandCards();
    //*********test**********
    PlayerOutCards.clear();
    //*********end **********
    for(unsigned i = 0;i < PlayerHandCards.size();i++)
    {
        if(PlayerHandCards[i].isUp==false)
        {
            qDebug()<<"移动前"<<PlayerHandCards[i].btn->x();
            AnimateMoveLeft(PlayerHandCards[i].btn,0.03*Width*(i-HeadUnselectedCount++));
            qDebug()<<"移动后"<<PlayerHandCards[i].btn->x();
            continue;
        }
        SelectedCards[PlayerHandCards[i].Index] = 1;
        //出牌后,更新playeroutcards
        delete PlayerHandCards[i].btn;
        PlayerOutCards.push_back(AllCards[PlayerHandCards[i].Index]);
    }
    for(unsigned i = 0; i<PlayerHandCards.size();i++)
    {
        if(PlayerHandCards[i].isUp==false)
        {
            PlayerHandCards.erase(std::remove_if(PlayerHandCards.begin(), PlayerHandCards.end(), [](const WidgetCard& card) {
                            return card.isUp;
                        }), PlayerHandCards.end());
        }
    }
    ConnectHandCards();
    std::bitset<54> test = 0;
    test = Transform_To_Bitset(PlayerHandCards);
    std::cout<<"new handcards  "<<test<<"\n";  std::flush(std::cout);

    placeOutCards(3);
    std::cout<<SelectedCards<<"\n";
    std::flush(std::cout);
}

void GameWidget::ConnectHandCards()
{
    for (int i = 0;i < PlayerHandCards.size();i++)
    {
        int index = i;
        connect(PlayerHandCards[i].btn,&QPushButton::clicked,[&,index]()
                {
            if (!PlayerHandCards[index].isUp) {qDebug()<<"movecard"<<PlayerHandCards[index].Index;
                AnimateMove(PlayerHandCards[index].btn->pos(), PlayerHandCards[index].btn->pos() - QPoint(0, 50), PlayerHandCards[index].btn);
            } else {
                AnimateMove(PlayerHandCards[index].btn->pos(), PlayerHandCards[index].btn->pos() + QPoint(0, 50), PlayerHandCards[index].btn);
            }
            PlayerHandCards[index].isUp = !PlayerHandCards[index].isUp;
        });
    }
}

void GameWidget::DisconnectHandCards()
{
    for (int i = 0;i < PlayerHandCards.size();i++)
    {
        disconnect(PlayerHandCards[i].btn,0,0,0);
    }
}
void GameWidget::AnimateMove(const QPoint& startPos, const QPoint& endPos,QPushButton *btn)
{
    QPropertyAnimation* animation = new QPropertyAnimation(btn, "pos");
    animation->setDuration(300);
    animation->setStartValue(startPos);
    animation->setEndValue(endPos);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start();
    btn->setEnabled(false);
    connect(animation,&QPropertyAnimation::finished,[btn]()
    {
        btn->setEnabled(true);
    });
}

void GameWidget::AnimateMoveLeft(QPushButton* btn, int distance)
{
    QPropertyAnimation* animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(500); // 动画持续时间为500毫秒
    animation->setStartValue(btn->geometry());
    animation->setEndValue(btn->geometry().translated(-distance, 0)); // 向左移动指定距离
    animation->setEasingCurve(QEasingCurve::OutCubic); // 使用缓动曲线来平滑动画
    animation->start();
    btn->setGeometry(btn->x()-distance,btn->y(),btn->width(),btn->height());
}
//没写呢
void GameWidget::DestroyOutCards(int pos)
{
    if(pos==1)
    {
        ;
    }
    if(pos==2)
    {
        ;
    }
    if(pos==3)
    {
        ;
    }
}

// void onSkipTurnBtnClicked()   //点击不出按钮；
// {

// }
// void onCallLandlordBtnClicked()    //点击叫地主按钮
// {

// }
// void onSkipCallLandlordBtnClicked()//点击不叫按钮
// {

// }
// void onBidForLandlordBtnClicked()   //点击抢地主按钮
// {

// }
// void onSkipLandlordBidBtnClicked()  //点击不抢按钮
// {

// }
// void onDoubleBtnClicked()          //点击加倍按钮
// {

// }
// void onUnDoubleBtnClicked()        //点击不加倍按钮
// {

// }
