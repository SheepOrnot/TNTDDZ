#include "gamewidget.h"
#include "ui_gamewidget.h"
#include<QDebug>

GameWidget::GameWidget(int _Width,int _Height,int _mode,QWidget *parent) :
    QWidget(parent),Width(_Width),Height(_Height),mode(_mode),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    ImportConfig();
    this->setFixedSize(Width,Height);
    InitAllCards();
    if(FullScreenState)
    {
        this->setWindowFlags(Qt::FramelessWindowHint);  // 设置无边框
        this->showFullScreen();  // 全屏显示
        SettingWidth = Width; SettingHeight = Height;
        Width = this->width();
        Height = this->height();
    }

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

    timer = new QTimer(this);

    EffectPlayer = new QMediaPlayer();
    EffectaudioOutput = new QAudioOutput();
    EffectaudioOutput->setVolume(1);
    EffectPlayer->setAudioOutput(EffectaudioOutput);
    EffectPlayer->moveToThread(BGMThread);

    CardBackPixmap = QPixmap(":/image/image/Cards_"+QString::number(CardStyle)+"/back.png");
    CardBackPixmap = CardBackPixmap.scaled(0.040*Width,0.070*Height, Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸

    PreviousCardsNumLabel = new QLabel(this);
    NextCardsNumLabel = new QLabel(this);
    RoomIdFontSize = 0.02*Height;

//****** 测试******
    std::bitset<54> BitsetCards(std::string("111000111000000000110011001100110011101000000010001110"));
    previousBitset= std::bitset<54>(std::string("000001111111100000000011111111000100000000000000000000"));
    nextBitset= std::bitset<54>    (std::string("000000000000000000000000000000111010110011111111001110"));
    playerBitset= std::bitset<54>  (std::string("111110000000011111111100000000000001001100000000000000"));
    finalBitset= std::bitset<54>   (std::string("000000000000000000000000000000000000000000000000110001"));

    QPushButton *Testbtn = new QPushButton(this);            //测试按钮
    Testbtn->setGeometry(0.624*Width,  0.018*Height,  0.025*Width,   0.04*Height);
    Testbtn->show();
    connect(Testbtn,&QPushButton::clicked,[&](){
        switch(TestStage)
        {
            case 0:{somebodyEnterRoom(3,0,"冷锋",66999,"995664"); break;}
            case 1:{somebodyEnterRoom(1,1,"陈韬羽",652);  break;}
            case 2:{somebodyReady(3);break;}
            case 3:{somebodyEnterRoom(2,3,"司令",777777777);break;}
            case 4:{somebodyReady(2);break;}
            case 5:{somebodyUnReady(3);break;}
            case 6:{somebodyReady(3);break;}
            case 7:{somebodyReady(1);break;}
            case 8:{Dealingcards(playerBitset);break;}
            case 9:{somebodyCallLandlordRound(1);break;}
            case 10:{somebodyNotCallLandlord(1);break;}
            case 11:{somebodyCallLandlordRound(3);break;}
            case 12:{somebodyCallLandlord(3);break;}
            case 13:{somebodyBidForLandlordRound(2);break;}
            case 14:{somebodyBidForLandlord(2);break;}
            case 15:{somebodyBidForLandlordRound(3);break;}
            case 16:{somebodyBidForLandlord(3);break;}
            case 17:{StartGame("farmer","farmer","landlord",finalBitset|playerBitset,finalBitset);break;}  //111110000000011111111100000000000001001100000000110001
            case 18:{somebodyPlayCardRound(3,1);break;};
            case 19:{
                    playeroutBitset = std::bitset<54>(std::string("000000000000000000000000000000000000000000000000110000"));
                    playerBitset    = std::bitset<54>(std::string("111110000000011111111100000000000001001100000000000001"));
                    somebodyOutCard(3,playeroutBitset,18,2,playerBitset);
                    break;
                    }
            case 20:{somebodyPlayCardRound(2);break;};
            case 21:{
                    nextoutBitset =  std::bitset<54>  (std::string("000000000000000000000000000000110000000000000000000000"));
                    //nextBitset    = std::bitset<54> (std::string("000000000000000000000000000000001010110011111111001110"));
                    somebodyOutCard(2,nextoutBitset,15,2);
                    break;
                    }
            case 22:{somebodyPlayCardRound(1);break;};
            case 23:{somebodyNotOutCard(1,17);break;}
            case 24:{somebodyPlayCardRound(3); break;}
            case 25:
            {
                playeroutBitset = std::bitset<54>(std::string("001100000000000000000000000000000000000000000000000000"));
                playerBitset= std::bitset<54>    (std::string("110010000000011111111100000000000001001100000000000001"));
                somebodyOutCard(3,playeroutBitset,16,2,playerBitset);
                break;
            }
            case 26:{somebodyPlayCardRound(2);break;}
            case 27:{somebodyNotOutCard(2,15);break;}
            case 28:{somebodyPlayCardRound(1);break;}
            case 29:{somebodyNotOutCard(1,17);break;}
            case 30:{somebodyPlayCardRound(3,1);break;}
            case 31:
            {
                //playeroutBitset = std::bitset<54>(std::string("110000000000000000000000000000000000000000000000000000"));
                playeroutBitset = std::bitset<54>(std::string("110010000000011111111100000000000001001100000000000001"));
                //playerBitset= std::bitset<54>    (std::string("000010000000011111111100000000000001001100000000000001"));
                playerBitset= std::bitset<54>    (std::string("000000000000000000000000000000000000000000000000000000"));
                somebodyOutCard(3,playeroutBitset,14,14,playerBitset);
                break;
            }
            case 32:{GameOver(1,6,-4500,-4500,9000);break;}
            default: qDebug()<<"done!";
        }
        qDebug()<<TestStage;
        TestStage++;
    });
//******end******

    //上家(previous)->1     下家(next)->2      自己->3
    ui->ProfileLabel1      ->setGeometry( 0.026*Width,  0.250*Height,  0.063*Width,   0.121*Height);
    ui->ProfileLabel2      ->setGeometry( 0.906*Width,  0.250*Height,  0.063*Width,   0.121*Height);
    ui->ProfileLabel3      ->setGeometry( 0.062*Width,  0.824*Height,  0.063*Width,   0.121*Height);
    ui->IdentityLabel1     ->setGeometry( 0.046*Width,  0.203*Height,  0.021*Width,   0.037*Height);
    ui->IdentityLabel2     ->setGeometry( 0.927*Width,  0.212*Height,  0.021*Width,   0.037*Height);
    ui->IdentityLabel3     ->setGeometry( 0.083*Width,  0.777*Height,  0.021*Width,   0.037*Height);
    ui->BeansLineEdit1     ->setGeometry( 0.026*Width,  0.388*Height,  0.063*Width,   0.028*Height);
    ui->BeansLineEdit2     ->setGeometry( 0.906*Width,  0.398*Height,  0.063*Width,   0.028*Height);
    ui->BeansLineEdit3     ->setGeometry( 0.062*Width,  0.953*Height,  0.063*Width,   0.028*Height);    ui->DoubleLabel1->hide();
    ui->DoubleLabel1       ->setGeometry( 0.062*Width,  0.425*Height,  0.026*Width,   0.017*Height);    ui->DoubleLabel2->hide();
    ui->DoubleLabel2       ->setGeometry( 0.906*Width,  0.435*Height,  0.026*Width,   0.017*Height);    ui->DoubleLabel3->hide();
    ui->DoubleLabel3       ->setGeometry( 0.135*Width,  0.962*Height,  0.026*Width,   0.017*Height);
    ui->FinalCard1         ->setGeometry( 0.420*Width,  0.018*Height,  0.042*Width,   0.102*Height);
    ui->FinalCard2         ->setGeometry( 0.472*Width,  0.018*Height,  0.042*Width,   0.102*Height);
    ui->FinalCard3         ->setGeometry( 0.524*Width,  0.018*Height,  0.042*Width,   0.102*Height);
    ui->MultiplierLabel    ->setGeometry( 0.571*Width,  0.046*Height,  0.042*Width,   0.075*Height);    ui->ClockImageLabel->hide();
    ui->ClockImageLabel    ->setGeometry( 0.802*Width,  0.222*Height,  0.021*Width,   0.037*Height);    ui->ClockNum->hide();
    ui->ClockNum           ->setGeometry( 0.808*Width,  0.231*Height,  0.010*Width,   0.019*Height);
    ui->RuleBtn            ->setGeometry( 0.901*Width,  0.018*Height,  0.031*Width,   0.056*Height);
    ui->SettingBtn         ->setGeometry( 0.942*Width,  0.018*Height,  0.031*Width,   0.056*Height);
    ui->CallLandlordBtn    ->setGeometry( 0.358*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->CallLandlordBtn     ->hide();
    ui->SkipCallLandlordBtn->setGeometry( 0.550*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->SkipCallLandlordBtn ->hide();
    ui->BidForLandlordBtn  ->setGeometry( 0.358*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->BidForLandlordBtn   ->hide();
    ui->SkipLandlordBidBtn ->setGeometry( 0.550*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->SkipLandlordBidBtn  ->hide();
    ui->PlayCardBtn        ->setGeometry( 0.358*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->PlayCardBtn         ->hide();
    ui->SkipTurnBtn        ->setGeometry( 0.550*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->SkipTurnBtn         ->hide();
    ui->DoubleBtn          ->setGeometry( 0.358*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->DoubleBtn           ->hide();
    ui->UnDoubleBtn        ->setGeometry( 0.520*Width,  0.680*Height,  0.083*Width,   0.047*Height);    ui->UnDoubleBtn         ->hide();
    ui->ChatComboBox       ->setGeometry( 0.885*Width,  0.785*Height,  0.104*Width,   0.028*Height);
    ui->RoomId             ->setGeometry( 0.830*Width,  0.020*Height,  0.070*Width,   0.048*Height);
    ui->MSGLabel1          ->setGeometry( 0.198*Width,  0.287*Height,  0.090*Width,   0.048*Height);    ui->MSGLabel1->hide();
    ui->MSGLabel2          ->setGeometry( 0.712*Width,  0.287*Height,  0.090*Width,   0.048*Height);    ui->MSGLabel2->hide();
    ui->MSGLabel3          ->setGeometry( 0.445*Width,  0.680*Height,  0.090*Width,   0.048*Height);    ui->MSGLabel3->hide();
    ui->ReadyBtn           ->setGeometry( 0.458*Width,  0.680*Height,  0.083*Width,   0.048*Height);
    ui->UnReadyBtn         ->setGeometry( 0.458*Width,  0.680*Height,  0.083*Width,   0.048*Height);    ui->UnReadyBtn->hide();
    ui->ReadyLabel1        ->setGeometry( 0.038*Width,  0.240*Height,  0.025*Width,   0.035*Height);    ui->ReadyLabel1->hide();
    ui->ReadyLabel2        ->setGeometry( 0.918*Width,  0.240*Height,  0.025*Width,   0.035*Height);    ui->ReadyLabel2->hide();
    ui->ReadyLabel3        ->setGeometry( 0.078*Width,  0.814*Height,  0.025*Width,   0.035*Height);    ui->ReadyLabel3->hide();
    ui->Recorder           ->setGeometry( 0.070*Width,  0.018*Height,  0.290*Width,   0.057*Height);    ui->Recorder->hide();
    ui->Name1              ->setGeometry( 0.062*Width,  0.420*Height,  0.050*Width,   0.035*Height);
    ui->Name2              ->setGeometry( 0.906*Width,  0.420*Height,  0.050*Width,   0.035*Height);
    ui->Name3              ->setGeometry( 0.140*Width,  0.953*Height,  0.050*Width,   0.035*Height);

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


    ProfilePixmap1 = QPixmap(":/image/image/Profile/default.jpg");
    ProfilePixmap1 = ProfilePixmap1.scaled(ui->ProfileLabel1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->ProfileLabel1->setPixmap(ProfilePixmap1);
    ui->ProfileLabel1->setScaledContents(true);


    ProfilePixmap2 = QPixmap(":/image/image/Profile/default.jpg");
    ProfilePixmap2 = ProfilePixmap2.scaled(ui->ProfileLabel2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->ProfileLabel2->setPixmap(ProfilePixmap2);
    ui->ProfileLabel2->setScaledContents(true);

    ProfilePixmap3 = QPixmap(":/image/image/Profile/default.jpg");
    ProfilePixmap3 = ProfilePixmap3.scaled(ui->ProfileLabel3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->ProfileLabel3->setPixmap(ProfilePixmap3);
    ui->ProfileLabel3->setScaledContents(true);

    QString roomIDstylesheet = QString("QLabel{font: 600 %1pt Sitka Subheading Semibold;border:1px solid;"
                                       " background-color: qradialgradient(cx:0.5, cy:0.5, radius: 1.4, fx:0.5, fy:0.5, stop:0 #fafafa, stop:1 #f4f4f4); "
                                       "box-shadow: 1px 1px 1px rgba(0, 0, 0, 0.2);}").arg(RoomIdFontSize);
    ui->RoomId->setStyleSheet(roomIDstylesheet);
    ui->RoomId->setAlignment(Qt::AlignCenter);


    ReadyPixmap = QPixmap(":/image/image/Icon/ready.png");
    ui->ReadyLabel1->setPixmap(ReadyPixmap);
    ui->ReadyLabel1->setScaledContents(true);
    ui->ReadyLabel2->setPixmap(ReadyPixmap);
    ui->ReadyLabel2->setScaledContents(true);
    ui->ReadyLabel3->setPixmap(ReadyPixmap);
    ui->ReadyLabel3->setScaledContents(true);

    ui->MSGLabel1->setAlignment(Qt::AlignCenter);
    ui->MSGLabel2->setAlignment(Qt::AlignCenter);
    ui->MSGLabel3->setAlignment(Qt::AlignCenter);

    ui->MultiplierLabel->setText("倍数\n⨉"+QString::number(Times));


    model = new QStandardItemModel(2,15);
    for (int column = 0; column < 15; ++column) {
        QStandardItem *item = new QStandardItem(PointIndex[column+3]);
        model->setItem(0, column, item);
    }
    ui->Recorder->setModel(model);
    ui->Recorder->resizeRowsToContents();
    ui->Recorder->resizeColumnsToContents();
    ui->Recorder->verticalHeader()->setVisible(false);
    ui->Recorder->horizontalHeader()->setVisible(false);


    ShowRecorderShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Period), this);  //CTRL + .
    QObject::connect(ShowRecorderShortcut, &QShortcut::activated, [&]() {
        if(RecordOpen==false)
            ui->Recorder->show();
        if(RecordOpen==true)
            ui->Recorder->hide();
        RecordOpen = !RecordOpen;
    });


    connect(ui->RuleBtn,&QPushButton::clicked,this,&GameWidget::onRuleBtnClicked);
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

void GameWidget::onSettingBtnClicked()
{
    settingWidget = new SettingWidget(Width,Height);
    settingWidget->show();
}

void GameWidget::placeHandCards()
{
    for(unsigned i = 0; i < PlayerHandCards.size(); i++)
    {
        PlayerHandCards[i].btn = new QPushButton(this);
        PlayerHandCards[i].btn->setIcon(QIcon(PlayerHandCards[i].ImagePath));
        PlayerHandCards[i].btn->setStyleSheet("QPushButton { background-color: transparent; }");
        //PlayerHandCards[i].btn->setStyleSheet("QPushButton:disabled{color: black;}");
        PlayerHandCards[i].btn->setGeometry((0.198+0.03*i)*Width,0.796*Height,0.06*Width,0.148*Height);
        PlayerHandCards[i].btn->setIconSize(PlayerHandCards[i].btn->size());
        PlayerHandCards[i].btn->show();
    }
    ConnectHandCards();
}
void GameWidget::replaceHandCards(std::bitset<54> handcrads)
{

    DisconnectHandCards();
    for(unsigned i = 0; i<PlayerHandCards.size(); i++)
    {
        delete PlayerHandCards[i].btn;
    }
    PlayerHandCards = Transform_To_Vector(handcrads);
    for(unsigned i = 0; i < PlayerHandCards.size(); i++)
    {
        PlayerHandCards[i].btn = new QPushButton(this);
        PlayerHandCards[i].btn->setIcon(QIcon(PlayerHandCards[i].ImagePath));
        PlayerHandCards[i].btn->setStyleSheet("QPushButton { background-color: transparent; }");
        //PlayerHandCards[i].btn->setStyleSheet("QPushButton:disabled{color: black;}");
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
void GameWidget::ShowFinalCards()
{
    FinalCardPixmap1 = QPixmap(FinalCards[0].ImagePath);
    FinalCardPixmap1 = FinalCardPixmap1.scaled(ui->FinalCard1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->FinalCard1->setPixmap(FinalCardPixmap1);
    ui->FinalCard1->setScaledContents(true);

    FinalCardPixmap2 = QPixmap(FinalCards[1].ImagePath);
    FinalCardPixmap2 = FinalCardPixmap2.scaled(ui->FinalCard2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->FinalCard2->setPixmap(FinalCardPixmap2);
    ui->FinalCard2->setScaledContents(true);

    FinalCardPixmap3 = QPixmap(FinalCards[2].ImagePath);
    FinalCardPixmap3 = FinalCardPixmap3.scaled(ui->FinalCard3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->FinalCard3->setPixmap(FinalCardPixmap3);
    ui->FinalCard3->setScaledContents(true);
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
                QJsonObject UniversalObj = jsonObj["Universal"].toObject();
                BGMState = bool(GameObj.value("GameBGM").toVariant().toInt());
                EffectState = bool(GameObj.value("Effect").toVariant().toInt());
                CardStyle = GameObj.value("Card").toVariant().toInt();
                BGMVolume = GameObj.value("BGMVolume").toVariant().toDouble();
                EffectVolume = GameObj.value("EffectVolume").toVariant().toDouble();
                FullScreenState = bool(UniversalObj.value("FullScreen").toVariant().toInt());
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
    SelectedCards = 0;

    for(unsigned i = 0;i < PlayerHandCards.size();i++)
    {
        if(PlayerHandCards[i].isUp==true)
        {
            SelectedCards[PlayerHandCards[i].Index] = 1;
        }
    }
}
void GameWidget::ConnectHandCards()
{
    for (int i = 0;i < PlayerHandCards.size();i++)
    {
        int index = i;
        connect(PlayerHandCards[i].btn,&QPushButton::pressed,[&,index]()
                {
                    if (!PlayerHandCards[index].isUp) {qDebug()<<"movecard"<<PlayerHandCards[index].Index;
                        AnimateMove(PlayerHandCards[index].btn->pos(), PlayerHandCards[index].btn->pos() - QPoint(0, 0.02*Height), PlayerHandCards[index].btn);
                    } else {
                        AnimateMove(PlayerHandCards[index].btn->pos(), PlayerHandCards[index].btn->pos() + QPoint(0, 0.02*Height), PlayerHandCards[index].btn);
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
void GameWidget::updateRecorder(int Pos)
{
    switch(Pos)
    {
        case 1:
        {
            for(unsigned i = 0;i<PreviousPlayerOutCards.size();i++)
            {
                Card_Recorder[PreviousPlayerOutCards[i].Point-3]--;
            }
            break;
        }
        case 2:
        {
            for(unsigned i = 0;i<NextPlayerOutCards.size();i++)
            {
                Card_Recorder[NextPlayerOutCards[i].Point-3]--;
            }
            break;
        }
        case 3:
        {
            for(unsigned i = 0;i< PlayerHandCards.size();i++)
            {
                Card_Recorder[PlayerHandCards[i].Point-3]--;
            }
            break;
        }
    }
        for (int column = 0; column < 15; ++column) {
        QStandardItem *item = new QStandardItem(QString::number(Card_Recorder[column]));
            model->setItem(1, column, item);
        }
        ui->Recorder->setModel(model);
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
    btn->setEnabled(false);
    btn->setGeometry(btn->x()-distance,btn->y(),btn->width(),btn->height());
    connect(animation,&QPropertyAnimation::finished,[btn]()
            {
                btn->setEnabled(true);
            });
}
void GameWidget::MessageSender(std::string Title, std::string Info, QMessageBox::Icon Type)
{
    QMessageBox msgBox;
    msgBox.setIcon(Type);
    msgBox.setWindowTitle(QString::fromStdString(Title));
    msgBox.setText(QString::fromStdString(Info));
    msgBox.exec();
}
void GameWidget::PlacePreviousHandCards()
{
    for(int i = 0;i<backlabel1.size();i++)
    {
        if(backlabel1[i])
        {
            delete backlabel1[i];
        }
    }
    backlabel1.clear();
    for(int i = 0;i<PreviousCardsNumber;i++)
    {
        QLabel *tmp = new QLabel(this);
        tmp->setGeometry(0.119*Width,(0.138+(0.026*i))*Height,0.040*Width,0.070*Height);
        tmp->setPixmap(CardBackPixmap);
        tmp->setScaledContents(true);
        tmp->show();
        backlabel1.push_back(tmp);
    }
    PreviousCardsNumLabel->setGeometry(0.135*Width,(0.143+0.026*PreviousCardsNumber)*Height,0.010*Width,0.019*Height);
    PreviousCardsNumLabel->setStyleSheet("background-color: gold;");
    PreviousCardsNumLabel->setText(QString::number(PreviousCardsNumber));
    PreviousCardsNumLabel->raise();
    PreviousCardsNumLabel->show();

}
void GameWidget::PlaceNextHandCards()
{
    for(int i = 0;i<backlabel2.size();i++)
    {
        if(backlabel2[i])
        {
            delete backlabel2[i];
        }
    }
    backlabel2.clear();
    for(int i = 0;i<NextCardsNumber;i++)
    {
        QLabel *tmp = new QLabel(this);
        tmp->setGeometry(0.841*Width,(0.138+(0.026*i))*Height,0.040*Width,0.070*Height);
        tmp->setPixmap(CardBackPixmap);
        tmp->setScaledContents(true);
        tmp->show();
        backlabel2.push_back(tmp);
    }
    NextCardsNumLabel->setGeometry(0.848*Width,(0.143+0.026*NextCardsNumber)*Height,0.010*Width,0.019*Height);
    NextCardsNumLabel->setStyleSheet("background-color: gold;");
    NextCardsNumLabel->setText(QString::number(NextCardsNumber));
    NextCardsNumLabel->raise();
    NextCardsNumLabel->show();
}
void GameWidget::DestroyOutCards(int pos)          //清空出牌显示区  1->上家    2->下家   3->自己
{
    if(pos==1)
    {
        for(unsigned i = 0 ;i<PreviousPlayerOutCards.size();i++)
        {
            delete PreviousPlayerOutCards[i].btn;
        }
            PreviousPlayerOutCards.clear();

    }
    if(pos==2)
    {
        for(unsigned i = 0 ;i<NextPlayerOutCards.size();i++)
        {
            delete NextPlayerOutCards[i].btn;
        }
        NextPlayerOutCards.clear();
    }
    if(pos==3)
    {
        for(unsigned i = 0 ;i<PlayerOutCards.size();i++)
        {
            delete PlayerOutCards[i].btn;
        }
        PlayerOutCards.clear();
    }
}
void GameWidget::MakeSoundEffect(int Type)  //0:叫地主  1：不叫  2：加倍  3：不加倍   4：抢地主   5：不抢    6：不出
{                                           //7：上家出牌    8：下家出牌   9：自己出牌    10：游戏胜利    11：游戏失败  12：超时预警
    qDebug()<<"Make Effect"<<Type;
    switch(Type)
    {
        case 0:
        {
            EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/jiaodizhu.m4a"));
            break;
        }
        case 1:
        {
            EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/bujiao.m4a"));
            break;
        }
        case 2:
        {
            EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/jiabei.m4a"));
            break;
        }
        case 3:
        {
            EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/bujiabei.m4a"));
            break;
        }
        case 4:
        {

            int rand = QRandomGenerator::global()->generate()%3;
            EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/qiangdizhu"+QString::number(rand)+".m4a"));  //***********
            break;
        }
        case 5:
        {
            EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/buqiang.m4a"));
            break;
        }
        case 6:
        {
            EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/buyao.m4a"));
            break;
        }
        case 7:
        {
            if(PreviousOutCradsType > 3)
            {
                EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/"+CardTypeIndex[PreviousOutCradsType]+".m4a"));
                break;
            }
            else if(PreviousOutCradsType>0&&PreviousOutCradsType<4)
            {
                EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/"+CardTypeIndex[PreviousOutCradsType]+"_"+PointIndex[PreviousPlayerOutCards[0].Point]+".m4a"));
                break;
            }
        }
        case 8:
        {
            if(NextOutCradsType > 3)
            {
                EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/"+CardTypeIndex[NextOutCradsType]+".m4a"));
                break;
            }
            else if(NextOutCradsType>0&&NextOutCradsType<4)
            {
                EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/"+CardTypeIndex[NextOutCradsType]+"_"+PointIndex[NextPlayerOutCards[0].Point]+".m4a"));
                break;
            }
        }
        case 9:
        {
            if(PlayerOutCradsType > 3)
            {
                EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/"+CardTypeIndex[PlayerOutCradsType]+".m4a"));
                break;
            }
            else if(PlayerOutCradsType>0&&PlayerOutCradsType<4)
            {
                EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/"+CardTypeIndex[PlayerOutCradsType]+"_"+PointIndex[PlayerOutCards[0].Point]+".m4a"));
                break;
            }
        }
        case 12:
        {
            EffectPlayer->setSource(QUrl("qrc:/sound/sound/Sound_effects/warning.mp3"));
            break;
        }
    }
    EffectPlayer->play();

}
void GameWidget::ShowProfiles(int Pos)
{
    switch(Pos)
    {
        case 1:
        {
            ProfilePixmap1 = QPixmap(":/image/image/Profile/"+QString::number(PreviousProfileIndex)+".jpg");
            ProfilePixmap1 = ProfilePixmap1.scaled(ui->ProfileLabel1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
            ui->ProfileLabel1->setPixmap(ProfilePixmap1);
            ui->ProfileLabel1->show();
            break;
        }
        case 2:
        {
            ProfilePixmap2 = QPixmap(":/image/image/Profile/"+QString::number(NextProfileIndex)+".jpg");
            ProfilePixmap2 = ProfilePixmap2.scaled(ui->ProfileLabel2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->ProfileLabel2->setPixmap(ProfilePixmap2);
            ui->ProfileLabel2->show();
            break;
        }
        case 3:
        {
            ProfilePixmap3 = QPixmap(":/image/image/Profile/"+QString::number(PlayerProfileIndex)+".jpg");
            ProfilePixmap3 = ProfilePixmap3.scaled(ui->ProfileLabel3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->ProfileLabel3->setPixmap(ProfilePixmap3);
            ui->ProfileLabel3->show();
            break;
        }
    }

}
void GameWidget::StartCountDown(int time,int pos)
{
    qDebug()<<"start timer";
    ui->ClockImageLabel->show();
    ui->ClockNum->show();
    if(pos==1) {ui->ClockImageLabel->setGeometry(0.177*Width,  0.222*Height,  0.021*Width,   0.037*Height);
                ui->ClockNum       ->setGeometry(0.182*Width,  0.231*Height,  0.010*Width,   0.019*Height);
    }
    else if(pos==2) {ui->ClockImageLabel->setGeometry(0.802*Width,  0.222*Height,  0.021*Width,   0.037*Height);
                     ui->ClockNum       ->setGeometry(0.808*Width,  0.231*Height,  0.010*Width,   0.019*Height);
    }
    else if(pos==3) {ui->ClockImageLabel->setGeometry(0.490*Width,  0.685*Height,  0.021*Width,   0.037*Height);
                     ui->ClockNum       ->setGeometry(0.495*Width,  0.694*Height,  0.010*Width,   0.019*Height);
    }
    remainingTime = time;
    connect(timer, &QTimer::timeout, this, &GameWidget::updateCountDown);
    timer->start(1000); // 每秒触发一次timeout()信号
    updateCountDown(); // 更新显示剩余秒数
}
void GameWidget::updateCountDown()
{
    if(remainingTime==5) MakeSoundEffect(12);
    if (remainingTime >= 0) {
        ui->ClockNum->setText(QString::number(remainingTime));
        ui->ClockNum->setAlignment(Qt::AlignCenter);
        remainingTime--;
    } else {
        timer->stop(); // 停止计时器
        qDebug()<<"stop Timer";
    }
}
QString GameWidget::Transform_To_String(int Num)
{
    QString Str;
    double head;
    if(Num>100000000)
    {
        head = Num/100000000.0;
        Str = QString::number(head,'f', 2)+"亿";
    }
    else if(Num>10000)
    {
        head = Num/10000.0;
        Str = QString::number(head,'f', 2)+"万";
    }
    else Str = QString::number(Num);
    return Str;
}
void GameWidget::ShowIdentityIcon(std::string identity1,std::string identity2,std::string identity3)  //"farmer" "landlord"
{
    PreviousIdentityString = QString::fromStdString(identity1); NextIdentityString = QString::fromStdString(identity2); PlayerIdentityString = QString::fromStdString(identity3);
    IdentityPixmap1 = QPixmap(":/image/image/Icon/"+PreviousIdentityString+".png");
    IdentityPixmap1 = IdentityPixmap1.scaled(ui->IdentityLabel1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->IdentityLabel1->setPixmap(IdentityPixmap1);
    ui->IdentityLabel1->setScaledContents(true);

    IdentityPixmap2 = QPixmap(":/image/image/Icon/"+NextIdentityString+".png");
    IdentityPixmap2 = IdentityPixmap2.scaled(ui->IdentityLabel1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->IdentityLabel2->setPixmap(IdentityPixmap2);
    ui->IdentityLabel2->setScaledContents(true);

    IdentityPixmap3 = QPixmap(":/image/image/Icon/"+PlayerIdentityString+".png");
    IdentityPixmap3 = IdentityPixmap3.scaled(ui->IdentityLabel3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->IdentityLabel3->setPixmap(IdentityPixmap3);
    ui->IdentityLabel3->setScaledContents(true);

}
void GameWidget::somebodyCallLandlordRound(int Pos)     //叫地主回合
{
    switch(Pos)
    {
        case 1:
        {
            StartCountDown(10,1);
            ui->MSGLabel1->clear();
            break;
        }
        case 2:
        {
            StartCountDown(10,2);
            ui->MSGLabel2->clear();
            break;
        }
        case 3:
        {
            ui->SkipCallLandlordBtn->show();
            ui->CallLandlordBtn->show();
            ui->MSGLabel3->clear();
            StartCountDown(10,3);
            break;
        }
    }


}
void GameWidget::somebodyBidForLandlordRound(int Pos) //抢地主回合
{
    switch(Pos)
    {
        case 1:
        {
            StartCountDown(10,1);
            ui->MSGLabel1->clear();
            break;
        }
        case 2:
        {
            StartCountDown(10,2);
            ui->MSGLabel2->clear();
            break;
        }
        case 3:
        {
            ui->BidForLandlordBtn->show();
            ui->SkipLandlordBidBtn->show();
            ui->MSGLabel3->clear();
            StartCountDown(10,3);
        }
    }

}
void GameWidget::somebodyDoubleRound()       //加倍回合
{
        ui->MSGLabel1->clear();
        ui->MSGLabel2->clear();
        ui->MSGLabel3->clear();
        ui->DoubleBtn->show();
        ui->UnDoubleBtn->show();
        StartCountDown(10,3);
}
void GameWidget::somebodyPlayCardRound(int Pos,bool MustOut)    //出牌回合
{
    switch(Pos)
    {
        case 1:
        {
            StartCountDown(30,1);
            ui->MSGLabel1->clear();
            break;
        }
        case 2:
        {
            StartCountDown(30,2);
            ui->MSGLabel2->clear();
            break;
        }
        case 3:
        {
            ui->PlayCardBtn->show();
            ui->SkipTurnBtn->show();
            if(!MustOut)
            ui->SkipTurnBtn->setEnabled(true);
            else
            ui->SkipTurnBtn->setEnabled(false);
            ui->MSGLabel3->clear();
            StartCountDown(30,3);
            break;
        }
    }
        DestroyOutCards(Pos);
}
void GameWidget::somebodyReady(int Pos)            //有人准备
{
    switch(Pos)
    {
        case 1:
        {
            ui->ReadyLabel1->show();
            break;
        }
        case 2:
        {
            ui->ReadyLabel2->show();
            break;
        }
        case 3:
        {
            ui->ReadyLabel3->show();
            ui->ReadyBtn->hide();
            ui->UnReadyBtn->show();
            break;
        }
    }
}
void GameWidget::somebodyUnReady(int Pos)            //有人取消准备
{
    switch(Pos)
    {
        case 1:
        {
            ui->ReadyLabel1->hide();
            break;
        }
        case 2:
        {
            ui->ReadyLabel2->hide();
            break;
        }
        case 3:
        {
            ui->ReadyLabel3->hide();
            ui->ReadyBtn->show();
            ui->UnReadyBtn->hide();
            break;
        }
    }
}
void GameWidget::somebodyCallLandlord(int Pos)       //有人叫地主
{
    switch(Pos)
    {
    case 1:
        {
            ui->MSGLabel1->setText("叫地主");
            ui->MSGLabel1->show();
            break;
        }
        case 2:
        {
            ui->MSGLabel2->setText("叫地主");
            ui->MSGLabel2->show();
            break;
        }
        case 3:
        {
            ui->MSGLabel3->setText("叫地主");
            ui->SkipCallLandlordBtn->hide();
            ui->CallLandlordBtn->hide();
            ui->MSGLabel3->show();
            break;
        }
    }
    MakeSoundEffect(0);
    timer->stop();qDebug()<<"stop Timer";
    disconnect(timer, nullptr, this, nullptr);
    ui->ClockImageLabel->hide();
    ui->ClockNum->hide();
}
void GameWidget::somebodyNotOutCard(int Pos,int Leftcards,std::bitset<54> handcards)   //有人不出
{
    switch (Pos)
    {
        case 1:
        {
            PreviousPlayerOutCards.clear();
            PreviousCardsNumber = Leftcards;
            PreviousOutCradsType = 0;
            ui->MSGLabel1->setText("不出");
            ui->MSGLabel1->show();
            break;
        }
        case 2:
        {
            NextPlayerOutCards.clear();
            NextCardsNumber = Leftcards;
            NextOutCradsType = 0;
            ui->MSGLabel2->setText("不出");
            ui->MSGLabel2->show();
            break;
        }
        case 3:
        {
            PlayerOutCards.clear();
            PlayerHandCards = Transform_To_Vector(handcards);
            PlayerOutCradsType = 0;
            ui->MSGLabel3->setText("不出");
            ui->MSGLabel3->show();
            ui->PlayCardBtn->hide();
            ui->SkipTurnBtn->hide();
            break;
        }
    }
        timer->stop();qDebug()<<"stop Timer";
        disconnect(timer, nullptr, this, nullptr);
        ui->ClockImageLabel->hide();
        ui->ClockNum->hide();
        MakeSoundEffect(6);
}
void GameWidget::somebodyOutCard(int Pos,std::bitset<54> Bitset,int Leftcards,int Cardtype,std::bitset<54> handcards)  //有人出牌
{
    switch(Pos)
    {
        case 1:
        {
            PreviousPlayerOutCards = Transform_To_Vector(Bitset);
            updateRecorder(Pos);
            PreviousCardsNumber = Leftcards;
            PreviousOutCradsType = Cardtype;
            PlacePreviousHandCards();
            break;
        }
        case 2:
        {
            NextPlayerOutCards = Transform_To_Vector(Bitset);
            updateRecorder(Pos);
            NextCardsNumber = Leftcards;
            NextOutCradsType = Cardtype;
            PlaceNextHandCards();
            break;
        }
        case 3:
        {
            PlayerOutCards = Transform_To_Vector(Bitset);
            PlayerOutCradsType = Cardtype;
            int HeadUnselectedCount = 0;
            //std::vector<int> recovercards;
            DisconnectHandCards();
            for(unsigned i = 0;i < PlayerHandCards.size();i++)
            {
                if(Bitset[PlayerHandCards[i].Index]==1)
                {
                    PlayerHandCards[i].isUp = true;
                }
                else if(PlayerHandCards[i].isUp==true)
                {
                    PlayerHandCards[i].isUp = false;    qDebug()<<"set Card"<<PlayerHandCards[i].Type<<" "<<PlayerHandCards[i].Point<<"isUp -> false";
                    // recovercards.push_back(i);
                }
            }
            for(unsigned i = 0;i < PlayerHandCards.size();i++)
            {
                if(PlayerHandCards[i].isUp==false)
                {
                    AnimateMoveLeft(PlayerHandCards[i].btn,0.03*Width*(i-HeadUnselectedCount++));
                    continue;
                }
                SelectedCards[PlayerHandCards[i].Index] = 1;
                PlayerHandCards[i].btn->hide();
                qDebug()<<"delete HandCards"<<PlayerHandCards[i].Type<<" "<<PlayerHandCards[i].Point;
                delete PlayerHandCards[i].btn;
            }
            std::vector<WidgetCard> temp;
            for(unsigned i = 0; i<PlayerHandCards.size();i++)
            {
                if(PlayerHandCards[i].isUp==false)
                    temp.push_back(PlayerHandCards[i]);
            }
            PlayerHandCards.clear();
            for(unsigned i = 0; i<temp.size();i++)
            {
                 PlayerHandCards.push_back(temp[i]);
            }
            // for(unsigned i = 0; i<PlayerHandCards.size();i++)
            // {
            //     if(PlayerHandCards[i].isUp==false)
            //     {
            //         PlayerHandCards.erase(std::remove_if(PlayerHandCards.begin(), PlayerHandCards.end(), [](const WidgetCard& card) {
            //                                   return card.isUp;
            //                               }), PlayerHandCards.end());
            //     }
            // }
            // for(int i = 0; i< PlayerHandCards.size();i++)
            // {
            //     for(int j = 0;j<recovercards.size();j++)
            //     {
            //         if(PlayerHandCards[i].Index==recovercards[j])
            //             PlayerHandCards[i].isUp = true;
            //     }
            // }
            ConnectHandCards();
            ui->PlayCardBtn->hide();
            ui->SkipTurnBtn->hide();
            break;
        }
    }
    placeOutCards(Pos);
    MakeSoundEffect(Pos+6);
    timer->stop();  qDebug()<<"stop Timer";
    disconnect(timer, nullptr, this, nullptr);
    ui->ClockImageLabel->hide();
    ui->ClockNum->hide();

}
void GameWidget::somebodyNotCallLandlord(int Pos)     //有人不叫
{
    switch(Pos)
    {
        case 1:
        {
            ui->MSGLabel1->setText("不叫");
            ui->MSGLabel1->show();
            break;
        }
        case 2:
        {
            ui->MSGLabel2->setText("不叫");
            ui->MSGLabel2->show();
            break;
        }
        case 3:
        {
            ui->MSGLabel3->setText("不叫");
            ui->SkipCallLandlordBtn->hide();
            ui->CallLandlordBtn->hide();
            ui->MSGLabel3->show();
            break;
        }
    }
        timer->stop();qDebug()<<"stop Timer";
        disconnect(timer, nullptr, this, nullptr);
        ui->ClockImageLabel->hide();
        ui->ClockNum->hide();
        MakeSoundEffect(1);
}
void GameWidget::somebodyBidForLandlord(int Pos)     //有人抢地主    ----》服务器端关联翻倍
{
    switch(Pos)
    {
        case 1:
        {
            ui->MSGLabel1->setText("抢地主");
            ui->MSGLabel1->show();
            break;
        }
        case 2:
        {
            ui->MSGLabel2->setText("抢地主");
            ui->MSGLabel2->show();
            break;
        }
        case 3:
        {
            ui->MSGLabel3->setText("抢地主");
            ui->SkipLandlordBidBtn->hide();
            ui->BidForLandlordBtn->hide();
            ui->MSGLabel3->show();
            break;
        }
    }
        timer->stop();qDebug()<<"stop Timer";
        disconnect(timer, nullptr, this, nullptr);
        ui->ClockImageLabel->hide();
        ui->ClockNum->hide();
        MakeSoundEffect(4);
}
void GameWidget::somebodyNotBidForLandlord(int Pos)
{
    switch(Pos)
    {
        case 1:
        {
            ui->MSGLabel1->setText("不抢");
            ui->MSGLabel1->show();
            break;
        }
        case 2:
        {
            ui->MSGLabel2->setText("不抢");
            ui->MSGLabel2->show();
            break;
        }
        case 3:
        {
            ui->MSGLabel3->setText("不抢");
            ui->SkipLandlordBidBtn->hide();
            ui->BidForLandlordBtn->hide();
            ui->MSGLabel3->show();
            break;
        }
    }
        timer->stop();qDebug()<<"stop Timer";
        disconnect(timer, nullptr, this, nullptr);
        ui->ClockImageLabel->hide();
        ui->ClockNum->hide();
        MakeSoundEffect(5);
}
void GameWidget::somebodyDouble(int Pos)
{
    switch(Pos)
    {
        case 1:
        {
            ui->MSGLabel1->setText("加倍");
            ui->MSGLabel1->show();
            //ui->DoubleLabel1->setPixmap();
            ui->DoubleLabel1->setText("加倍");
            ui->DoubleLabel1->show();
            break;
        }
        case 2:
        {
            ui->MSGLabel2->setText("加倍");
            ui->MSGLabel2->show();
            //ui->DoubleLabel2->setPixmap();
            ui->DoubleLabel2->setText("加倍");
            ui->DoubleLabel2->show();
            break;
        }
        case 3:
        {
            ui->MSGLabel3->setText("加倍");
            ui->DoubleBtn->hide();
            ui->UnDoubleBtn->hide();
            ui->MSGLabel3->show();
            //ui->DoubleLabel3->setPixmap();
            ui->DoubleLabel3->setText("加倍");
            ui->DoubleLabel3->show();
            timer->stop();qDebug()<<"stop Timer";
            disconnect(timer, nullptr, this, nullptr);
            ui->ClockImageLabel->hide();
            ui->ClockNum->hide();
            break;
        }
    }
    MakeSoundEffect(2);
}
void GameWidget::somebodyNotDouble(int Pos)
{
    switch(Pos)
    {
        case 1:
        {
            ui->MSGLabel1->setText("不加倍");
            ui->MSGLabel1->show();
            //ui->DoubleLabel1->setPixmap();
            ui->DoubleLabel1->setText("不加倍");
            ui->DoubleLabel1->show();
            break;
        }
        case 2:
        {
            ui->MSGLabel2->setText("不加倍");
            ui->MSGLabel2->show();
            //ui->DoubleLabel2->setPixmap();
            ui->DoubleLabel2->setText("不加倍");
            ui->DoubleLabel2->show();
            break;
        }
        case 3:
        {
            ui->MSGLabel3->setText("不加倍");
            ui->DoubleBtn->hide();
            ui->UnDoubleBtn->hide();
            ui->MSGLabel3->show();
            //ui->DoubleLabel3->setPixmap();
            ui->DoubleLabel3->setText("不加倍");
            ui->DoubleLabel3->show();
            timer->stop();qDebug()<<"stop Timer";
            disconnect(timer, nullptr, this, nullptr);
            ui->ClockImageLabel->hide();
            ui->ClockNum->hide();
            break;
        }
    }
    MakeSoundEffect(2);
}
void GameWidget::somebodyEnterRoom(int Pos,int ProfileIndex,std::string Name,int Beans,std::string _RoomId)  //有人加入房间，创建房间初始调用参数3，加入房间调用1/2显示已经在房间中的人，后加入房间正常调用
{
    switch(Pos)
    {
        case 1:
        {
            PreviousProfileIndex = ProfileIndex;
            PreviousBeanNum = Transform_To_String(Beans);
            ui->BeansLineEdit1->setText(PreviousBeanNum);
            PreviousName = QString::fromStdString(Name);
            ui->Name1->setText(PreviousName);ui->Name1->show();
            break;
        }
        case 2:
        {
            NextProfileIndex = ProfileIndex;
            NextBeanNum = Transform_To_String(Beans);
            ui->BeansLineEdit2->setText(NextBeanNum);
            NextName = QString::fromStdString(Name);
            ui->Name2->setText(NextName); ui->Name2->show();
            break;
        }
        case 3:
        {
            PlayerProfileIndex = ProfileIndex;
            PlayerBeanNum = Transform_To_String(Beans);
            ui->BeansLineEdit3->setText(PlayerBeanNum);
            PlayerName = QString::fromStdString(Name);
            ui->Name3->setText(PlayerName); ui->Name3->show();
            RoomId = QString::fromStdString(_RoomId);
            ui->RoomId->setText(RoomId);
            ui->RoomId->show();
            break;
        }
    }
    qDebug()<<"Pos "<<Pos;
    ShowProfiles(Pos);
}
void GameWidget::somebodyLeaveRoom(int Pos)   //游戏未开始时（三家没有全部准备时）
{
    switch(Pos)
    {
        case 1:
        {
            PreviousBeanNum = "";
            PreviousCardsNumber = 0;
            ProfilePixmap1 = QPixmap(":/image/image/Profile/default.jpg");
            ui->ProfileLabel1->setPixmap(ProfilePixmap1); ui->ProfileLabel1->show();
            PreviousName = "";
            ui->BeansLineEdit1->clear();
            ui->Name1->clear();
            somebodyUnReady(1);
            break;
        }
        case 2:
        {
            NextBeanNum = "";
            NextCardsNumber = 0;
            ProfilePixmap2 = QPixmap(":/image/image/Profile/default.jpg");
            ui->ProfileLabel2->setPixmap(ProfilePixmap2); ui->ProfileLabel2->show();
            NextName = "";
            ui->BeansLineEdit2->clear();
            ui->Name2->clear();
            somebodyUnReady(2);
            break;
        }
    }
}
void GameWidget::Dealingcards(std::bitset<54> handcards,int cardnum1,int cardnum2)
{
    ui->UnReadyBtn->hide();
    ui->ReadyLabel1->hide();
    ui->ReadyLabel2->hide();
    ui->ReadyLabel3->hide();
    PlayerHandCards = Transform_To_Vector(handcards);
    PreviousCardsNumber = cardnum1;
    NextCardsNumber = cardnum2;
    placeHandCards();
    PlaceNextHandCards();
    PlacePreviousHandCards();
}
void GameWidget::StartGame(std::string identity1,std::string identity2,std::string identity3,std::bitset<54> handcards,std::bitset<54> finalcards)
{
    ui->MSGLabel1->clear();
    ui->MSGLabel2->clear();
    ui->MSGLabel3->clear();
    ShowIdentityIcon(identity1,identity2,identity3);
    int cardnum1,cardnum2;
    if(identity1=="farmer") { cardnum1 = 17; PreviousIdentity = 0;}
    else { cardnum1 = 20; PreviousIdentity = 1;}
    if(identity2=="farmer") {cardnum2 = 17; NextIdentity = 0;}
    else { cardnum2 = 20; NextIdentity = 1;}
    if(identity3=="farmer") {PlayerIdentity = 0;}
    else {PlayerIdentity = 1;}
    DisconnectHandCards();
    for(int i = 0;i<PlayerHandCards.size();i++)
    {
        delete PlayerHandCards[i].btn;
    }
    PlayerHandCards = Transform_To_Vector(handcards);
    updateRecorder(3);
    Dealingcards(handcards,cardnum1,cardnum2);
    FinalCards = Transform_To_Vector(finalcards);
    ShowFinalCards();
}
void GameWidget::AddTimes(int newTimes)
{
    Times = newTimes;
    ui->MultiplierLabel->setText("倍数\n⨉"+QString::number(Times));
}
void GameWidget::GameOver(bool Result,int times,int Score1,int Score2,int Score3)
{
    gameoverWidget = new GameOverWidget(Width,Height,Result,times,PreviousIdentity,NextIdentity,PlayerIdentity,PreviousName,NextName,PlayerName,PreviousDouble
                                        ,NextDouble,PlayerDouble,Score1,Score2,Score3);
    ContinueGame = new QPushButton(gameoverWidget);
    ContinueGame->setGeometry(0.401*Width,  0.481*Height,  0.099*Width,   0.065*Height);
    ContinueGame->show();
    connect(ContinueGame,&QPushButton::clicked,this,&GameWidget::StartNewGame);
    gameoverWidget->show();
    timer->stop();  qDebug()<<"stop Timer";
    disconnect(timer, nullptr, this, nullptr);
    ui->ClockImageLabel->hide();
    ui->ClockNum->hide();
}

void GameWidget::StartNewGame()
{
    qDebug()<<"start new game";
    gameoverWidget->close();
    for(unsigned i = 0;i<backlabel1.size();i++){
        qDebug()<<"delete backlabel1"<<i;
        delete backlabel1[i];
        }
    for(unsigned i = 0;i<backlabel2.size();i++){
            qDebug()<<"delete backlabel2"<<i;
        delete backlabel2[i];
    }
    backlabel1.clear();
    backlabel2.clear();

    backlabel1.shrink_to_fit();
    backlabel2.shrink_to_fit();
    DestroyOutCards(1);
    DestroyOutCards(2);
    DestroyOutCards(3);
    PreviousPlayerOutCards.clear();
    NextPlayerOutCards.clear();
    PlayerOutCards.clear();
    PlayerHandCards.clear();
    FinalCards.clear();
    ui->FinalCard1->setPixmap(CardBackPixmap);
    ui->FinalCard2->setPixmap(CardBackPixmap);
    ui->FinalCard3->setPixmap(CardBackPixmap);
    PreviousCardsNumLabel->hide();
    PreviousCardsNumber = 0;
    NextCardsNumLabel->hide();
    NextCardsNumber = 0;
    ui->MSGLabel1->clear();
    ui->MSGLabel2->clear();
    ui->MSGLabel3->clear();
    ui->IdentityLabel1->hide();
    ui->IdentityLabel2->hide();
    ui->IdentityLabel3->hide();
    int temp[15] = {4,4,4,4,4,4,4,4,4,4,4,4,4,1,1};
    for(int i = 0;i<15;i++) Card_Recorder[i] = temp[i];
    //placeHandCards();

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
void GameWidget::onRuleBtnClicked()
{
    ruleWidget = new RuleWidget;
    ruleWidget->show();
}
