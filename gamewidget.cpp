#include "gamewidget.h"
#include "ui_gamewidget.h"
#include<QDebug>
#include<iostream>
GameWidget::GameWidget(int _Width,int _Height,QWidget *parent) :
    QWidget(parent),Width(_Width),Height(_Height),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    InitAllCards();
    //****** 测试******
    std::bitset<54> BitsetCards(std::string("111000111000000000110011001100110011101000000010001110"));
    std::vector<WidgetCard>TestCardsVector = Transform_To_Vector(BitsetCards);
    std::bitset<54> TestCardBits = Transform_To_Bitset(TestCardsVector);
    std::cout<<BitsetCards<<"\n";
    std::cout<<TestCardBits;
    //******end******

}

GameWidget::~GameWidget()
{
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
        TempCards.push_back(TempCard);      //qDebug()<<TypeIndex[TempCard.Type]<<" "<<PointIndex[TempCard.Point];
    }
    if(BitsetCards[52]==1)
    {
        TempCard.Point=16;
        TempCard.Type=5;
        TempCard.ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/black_of_joker.png";
        TempCards.push_back(TempCard);      //qDebug()<<TypeIndex[TempCard.Type]<<" "<<PointIndex[TempCard.Point];
    }
    for(int i = 51; i>=0; i--)
    {
        if(BitsetCards[i]==0) continue;
        TempCard.Point = i/4+3;
        TempCard.Type = i%4 +1;
        TempCard.ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/"+QString::number(TempCard.Point)+"_of_"+QString::number(TempCard.Type)+".png";
        TempCards.push_back(TempCard);       //qDebug()<<TypeIndex[TempCard.Type]<<" "<<PointIndex[TempCard.Point];
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
