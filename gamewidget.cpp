#include "gamewidget.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
}

GameWidget::~GameWidget()
{
    delete ui;
}

void InitAllCards(WidgetCard AllCards[54],int CardStyle)
{
    AllCards[0].Point = 17; AllCards[0].Type = 5;
    AllCards[0].ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/"+QString::number(AllCards[0].Point)+"_"+QString::number(AllCards[0].Type)+".png";
    AllCards[1].Point = 16; AllCards[0].Type = 5;
    AllCards[1].ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/"+QString::number(AllCards[1].Point)+"_"+QString::number(AllCards[1].Type)+".png";
    int i = 2;
    for(int j = 15; j>2; j--)
    {
        for(int k = 1; k<5; k++)
        {
            AllCards[i].Point = j; AllCards[i].Type = k;
            AllCards[1].ImagePath = ":/image/image/Cards_"+QString::number(CardStyle)+"/"+QString::number(j)+"_"+QString::number(k)+".png";
            i++;
        }
    }
}
//std::vector<WidgetCard> GameWidget::Transform_To_Vector(std::bitset<54> BitsetCards)
//{
//    ;
//}

//std::bitset<54> GameWidget::Transform_To_Bitset(std::vector<WidgetCard> VectorCards)
//{
//    ;
//}
