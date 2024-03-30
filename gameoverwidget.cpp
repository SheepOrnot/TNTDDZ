#include "gameoverwidget.h"
#include "ui_gameoverwidget.h"
#include <QDebug>
GameOverWidget::GameOverWidget(int _Width,int _Height,QWidget *parent) :
    QWidget(parent),Width(_Width),Height(_Height),
    ui(new Ui::GameOverWidget)
{
    ui->setupUi(this);
    //qDebug()<<"GameOver";
    this->setFixedSize(0.618*Width,0.618*Height);
//****** 测试 *******


//****** end *******

    ui->Score1       ->setGeometry(0.395*Width,  0.314*Height,  0.057*Width,   0.047*Height);
    ui->Score2       ->setGeometry(0.395*Width,  0.379*Height,  0.057*Width,   0.047*Height);
    ui->Score3       ->setGeometry(0.395*Width,  0.25 *Height,  0.057*Width,   0.047*Height);
    ui->Times1       ->setGeometry(0.296*Width,  0.314*Height,  0.042*Width,   0.047*Height);
    ui->Times2       ->setGeometry(0.296*Width,  0.379*Height,  0.042*Width,   0.047*Height);
    ui->Times3       ->setGeometry(0.296*Width,  0.25 *Height,  0.042*Width,   0.047*Height);
    ui->Username1    ->setGeometry(0.171*Width,  0.314*Height,  0.104*Width,   0.047*Height);
    ui->Username2    ->setGeometry(0.171*Width,  0.379*Height,  0.104*Width,   0.047*Height);
    ui->Username3    ->setGeometry(0.171*Width,  0.25 *Height,  0.104*Width,   0.047*Height);
    ui->Title        ->setGeometry(0.197*Width,  0.055*Height,  0.208*Width,   0.148*Height);
    ui->ReturnToLobby->setGeometry(0.098*Width,  0.481*Height,  0.099*Width,   0.065*Height);
    ui->ContinueGame ->setGeometry(0.401*Width,  0.481*Height,  0.099*Width,   0.065*Height);
}

GameOverWidget::~GameOverWidget()
{
    delete ui;
}
