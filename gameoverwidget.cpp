#include "gameoverwidget.h"
#include "ui_gameoverwidget.h"
#include <QDebug>
GameOverWidget::GameOverWidget(int _Width,int _Height,bool _Result,int _times,
                               bool _identity1, bool _identity2,bool _identity3,
                               QString _Name1,QString _Name2,QString _Name3,
                               bool _double1,bool _double2,bool _double3,
                               int _Score1,int _Score2,int _Score3,
                               QWidget *parent):
    QWidget(parent),Width(_Width),Height(_Height),Result(_Result),times(_times),identity1(_identity1),
    identity2(_identity2),identity3(_identity3),Name1(_Name1),Name2(_Name2),Name3(_Name3),
    double1(_double1),double2(_double2),double3(_double3),Score1(_Score1),Score2(_Score2),Score3(_Score3),
    ui(new Ui::GameOverWidget)
{
    ui->setupUi(this);
    //qDebug()<<"GameOver";
    this->setFixedSize(0.618*Width,0.618*Height);
//****** 测试 *******


//****** end *******

    ui->Score2       ->setGeometry(0.395*Width,  0.314*Height,  0.057*Width,   0.047*Height);
    ui->Score1       ->setGeometry(0.395*Width,  0.379*Height,  0.057*Width,   0.047*Height);
    ui->Score3       ->setGeometry(0.395*Width,  0.25 *Height,  0.057*Width,   0.047*Height);
    ui->Times2       ->setGeometry(0.296*Width,  0.314*Height,  0.042*Width,   0.047*Height);
    ui->Times1       ->setGeometry(0.296*Width,  0.379*Height,  0.042*Width,   0.047*Height);
    ui->Times3       ->setGeometry(0.296*Width,  0.25 *Height,  0.042*Width,   0.047*Height);
    ui->Username2    ->setGeometry(0.171*Width,  0.314*Height,  0.104*Width,   0.047*Height);
    ui->Username1    ->setGeometry(0.171*Width,  0.379*Height,  0.104*Width,   0.047*Height);
    ui->Username3    ->setGeometry(0.171*Width,  0.25 *Height,  0.104*Width,   0.047*Height);
    ui->Title        ->setGeometry(0.197*Width,  0.055*Height,  0.208*Width,   0.148*Height);
    ui->ReturnToLobby->setGeometry(0.098*Width,  0.481*Height,  0.099*Width,   0.065*Height);
    ui->ContinueGame ->setGeometry(0.401*Width,  0.481*Height,  0.099*Width,   0.065*Height);

    if(identity3 == 1)
    {
        Result1 = !Result; Result2 = !Result; Result3 = Result;
    }
    if(identity3 == 0)
    {
        Result1 = identity1 ? !Result : Result;
        Result2 = identity2 ? !Result : Result;
    }

    PreviousTimes = double1 ? "加倍" : "不加倍";
    NextTimes = double2 ? "加倍" : "不加倍";
    PlayerTimes = double3 ? "加倍" : "不加倍";

    PreviousResult = Result1 ? "胜利" : "失败";
    NextResult = Result2 ? "胜利" : "失败";
    PlayerResult = Result3 ? "胜利" : "失败";

    PreviousScore = QString::number(Score1);
    NextScore = QString::number(Score2);
    PlayerScore = QString::number(Score3);

    PreviousIdentity = identity1 ? "地主" : "农民";
    NextIdentity = identity2 ? "地主" : "农民";
    PlayerIdentity = identity3 ? "地主" : "农民";

}

GameOverWidget::~GameOverWidget()
{
    delete ui;
}
