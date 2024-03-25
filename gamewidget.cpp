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
    InitAllCards();
//****** 测试******
    //std::bitset<54> BitsetCards(std::string("111000111000000000110011001100110011101000000010001110"));
    std::bitset<54> BitsetCards(std::string("111111111111111111110000000000000000000000000000000000"));
    std::vector<WidgetCard>TestCardsVector = Transform_To_Vector(BitsetCards);
    std::bitset<54> TestCardBits = Transform_To_Bitset(TestCardsVector);
    std::cout<<BitsetCards<<"\n";
    std::cout<<TestCardBits<<"\n";
    std::flush(std::cout);

    PlayerProfileNum = 0; PreviousProfileNum = 3; NextProfileNum = 4;
    PreviousIdentity = "landlord"; NextIdentity = "farmer"; PlayerIdentity = "farmer";
    ShowIdentityIcon();                                 //调用展示身份图标函数
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
    ui->FinalCard1         ->setGeometry( 0.415*Width,  0.018*Height,  0.042*Width,   0.102*Height);
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
    ui->ChatComboBox       ->setGeometry( 0.885*Width,  0.935*Height,  0.104*Width,   0.028*Height);


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

    ui->ChatComboBox->addItem("Option 1");
    ui->ChatComboBox->addItem("Option 2");
    ui->ChatComboBox->addItem("Option 3");

    qDebug()<<"Build GameWidget Completely";
}

GameWidget::~GameWidget()
{
    qDebug()<<"Destroy GameWidget";
    delete ui;
}

void GameWidget::InitAllCards()
{
    AllCards[0].Point = 17; AllCards[0].Type = 5;
    AllCards[0].ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/red_joker.png";
    AllCards[1].Point = 16; AllCards[0].Type = 5;
    AllCards[1].ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/black_joker.png";
    int i = 2;
    for(int j = 15; j>2; j--)
    {
        for(int k = 1; k<5; k++)
        {
            AllCards[i].Point = j; AllCards[i].Type = k;
            AllCards[1].ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/"+PointIndex[j]+"_of_"+TypeIndex[k]+".png";
            i++;
        }
    }
}

std::vector<WidgetCard> GameWidget::Transform_To_Vector(std::bitset<54> BitsetCards)
{
    std::vector<WidgetCard> TempCards;
    WidgetCard TempCard;
    if(BitsetCards[53]==1)
    {
        TempCard.Point=17;
        TempCard.Type=5;
        TempCard.ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/red_of_joker.png";
        TempCards.push_back(TempCard);      qDebug()<<TypeIndex[TempCard.Type]<<" "<<PointIndex[TempCard.Point];
    }
    if(BitsetCards[52]==1)
    {
        TempCard.Point=16;
        TempCard.Type=5;
        TempCard.ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/black_of_joker.png";
        TempCards.push_back(TempCard);      qDebug()<<TypeIndex[TempCard.Type]<<" "<<PointIndex[TempCard.Point];
    }
    for(int i = 51; i>=0; i--)
    {
        if(BitsetCards[i]==0) continue;
        TempCard.Point = i/4+3;
        TempCard.Type = i%4 +1;
        TempCard.ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/"+QString::number(TempCard.Point)+"_of_"+QString::number(TempCard.Type)+".png";
        TempCards.push_back(TempCard);       qDebug()<<TypeIndex[TempCard.Type]<<" "<<PointIndex[TempCard.Point];
    }
    return TempCards;
}

std::bitset<54> GameWidget::Transform_To_Bitset(std::vector<WidgetCard> VectorCards)
{
    std::bitset<54> TempBits = 0;
    for(int i = 0;i< VectorCards.size();i++)
    {
        if(VectorCards[i].Point==17) {TempBits[53]=1; continue;}
        if(VectorCards[i].Point==16) {TempBits[52]=1; continue;}
        TempBits[(VectorCards[i].Point-3)*4+VectorCards[i].Type-1] = 1;
    }
    return TempBits;
}

void GameWidget::ResolutionChanged(int _Width,int _Height)
{
    Width=_Width;  Height = _Height;
    this->setFixedSize(Width,Height);
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
    ui->FinalCard1         ->setGeometry( 0.385*Width,  0.018*Height,  0.042*Width,   0.102*Height);
    ui->FinalCard2         ->setGeometry( 0.442*Width,  0.018*Height,  0.042*Width,   0.102*Height);
    ui->FinalCard3         ->setGeometry( 0.494*Width,  0.018*Height,  0.042*Width,   0.102*Height);
    ui->MultiplierLabel    ->setGeometry( 0.541*Width,  0.046*Height,  0.042*Width,   0.075*Height);
    ui->ClockImageLabel    ->setGeometry( 0.802*Width,  0.222*Height,  0.021*Width,   0.037*Height);
    ui->ClockNum           ->setGeometry( 0.807*Width,  0.231*Height,  0.010*Width,   0.019*Height);
    ui->RuleBtn            ->setGeometry( 0.901*Width,  0.018*Height,  0.031*Width,   0.056*Height);
    ui->SettingBtn         ->setGeometry( 0.942*Width,  0.018*Height,  0.031*Width,   0.056*Height);
    ui->CallLandlordBtn    ->setGeometry( 0.328*Width,  0.694*Height,  0.083*Width,   0.047*Height);
    ui->SkipCallLandlordBtn->setGeometry( 0.520*Width,  0.694*Height,  0.083*Width,   0.047*Height);
    ui->BidForLandlordBtn  ->setGeometry( 0.328*Width,  0.675*Height,  0.083*Width,   0.047*Height);
    ui->SkipLandlordBidBtn ->setGeometry( 0.520*Width,  0.675*Height,  0.083*Width,   0.047*Height);
    ui->PlayCardBtn        ->setGeometry( 0.328*Width,  0.712*Height,  0.083*Width,   0.047*Height);
    ui->SkipTurnBtn        ->setGeometry( 0.520*Width,  0.712*Height,  0.083*Width,   0.047*Height);
    ui->DoubleBtn          ->setGeometry( 0.328*Width,  0.657*Height,  0.083*Width,   0.047*Height);
    ui->UnDoubleBtn        ->setGeometry( 0.520*Width,  0.657*Height,  0.083*Width,   0.047*Height);
    ui->ChatComboBox       ->setGeometry( 0.885*Width,  0.935*Height,  0.104*Width,   0.028*Height);

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


