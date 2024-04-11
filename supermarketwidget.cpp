#include "supermarketwidget.h"
#include "ui_supermarketwidget.h"

SuperMarketWidget::SuperMarketWidget(int _Width,int _Height,int _option,QWidget *parent)
    : Width(_Width),Height(_Height),option(_option),QWidget(parent)
    , ui(new Ui::SuperMarketWidget)
{
    ui->setupUi(this);
    this->setFixedSize(0.5*Width,0.5*Height);
    this->setWindowTitle("游戏商城");
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setWindowModality(Qt::ApplicationModal);
    ui->DiamondMarketBtn  ->setGeometry(0.010*Width, 0.000*Height, 0.239*Width, 0.028*Height);
    ui->BeanMarketBtn     ->setGeometry(0.250*Width, 0.000*Height, 0.239*Width, 0.028*Height);
    ui->label1            ->setGeometry(0.119*Width, 0.101*Height, 0.057*Width, 0.093*Height); ui->label1            ->hide();
    ui->label2            ->setGeometry(0.229*Width, 0.101*Height, 0.057*Width, 0.093*Height); ui->label2            ->hide();
    ui->label3            ->setGeometry(0.338*Width, 0.101*Height, 0.057*Width, 0.093*Height); ui->label3            ->hide();
    ui->label4            ->setGeometry(0.119*Width, 0.333*Height, 0.057*Width, 0.093*Height); ui->label4            ->hide();
    ui->label5            ->setGeometry(0.229*Width, 0.333*Height, 0.057*Width, 0.093*Height); ui->label5            ->hide();
    ui->label6            ->setGeometry(0.338*Width, 0.333*Height, 0.057*Width, 0.093*Height); ui->label6            ->hide();
    ui->labelD10          ->setGeometry(0.119*Width, 0.074*Height, 0.057*Width, 0.019*Height); ui->labelD10          ->hide();
    ui->labelD60          ->setGeometry(0.229*Width, 0.074*Height, 0.057*Width, 0.019*Height); ui->labelD60          ->hide();
    ui->labelD300         ->setGeometry(0.338*Width, 0.074*Height, 0.057*Width, 0.019*Height); ui->labelD300         ->hide();
    ui->labelD1280        ->setGeometry(0.119*Width, 0.305*Height, 0.057*Width, 0.019*Height); ui->labelD1280        ->hide();
    ui->labelD3280        ->setGeometry(0.229*Width, 0.305*Height, 0.057*Width, 0.019*Height); ui->labelD3280        ->hide();
    ui->labelD6480        ->setGeometry(0.338*Width, 0.305*Height, 0.057*Width, 0.019*Height); ui->labelD6480        ->hide();
    ui->pushButtonD10     ->setGeometry(0.119*Width, 0.203*Height, 0.057*Width, 0.028*Height); ui->pushButtonD10     ->hide();
    ui->pushButtonD60     ->setGeometry(0.229*Width, 0.203*Height, 0.057*Width, 0.028*Height); ui->pushButtonD60     ->hide();
    ui->pushButtonD300    ->setGeometry(0.338*Width, 0.203*Height, 0.057*Width, 0.028*Height); ui->pushButtonD300    ->hide();
    ui->pushButtonD1280   ->setGeometry(0.119*Width, 0.444*Height, 0.057*Width, 0.028*Height); ui->pushButtonD1280   ->hide();
    ui->pushButtonD3280   ->setGeometry(0.229*Width, 0.444*Height, 0.057*Width, 0.028*Height); ui->pushButtonD3280   ->hide();
    ui->pushButtonD6480   ->setGeometry(0.338*Width, 0.444*Height, 0.057*Width, 0.028*Height); ui->pushButtonD6480   ->hide();
    ui->label1_2          ->setGeometry(0.119*Width, 0.101*Height, 0.057*Width, 0.093*Height); ui->label1_2          ->hide();
    ui->label2_2          ->setGeometry(0.229*Width, 0.101*Height, 0.057*Width, 0.093*Height); ui->label2_2          ->hide();
    ui->label3_2          ->setGeometry(0.338*Width, 0.101*Height, 0.057*Width, 0.093*Height); ui->label3_2          ->hide();
    ui->label4_2          ->setGeometry(0.119*Width, 0.333*Height, 0.057*Width, 0.093*Height); ui->label4_2          ->hide();
    ui->label5_2          ->setGeometry(0.229*Width, 0.333*Height, 0.057*Width, 0.093*Height); ui->label5_2          ->hide();
    ui->label6_2          ->setGeometry(0.338*Width, 0.333*Height, 0.057*Width, 0.093*Height); ui->label6_2          ->hide();
    ui->labelD10_2        ->setGeometry(0.119*Width, 0.074*Height, 0.057*Width, 0.019*Height); ui->labelD10_2        ->hide();
    ui->labelD60_2        ->setGeometry(0.229*Width, 0.074*Height, 0.057*Width, 0.019*Height); ui->labelD60_2        ->hide();
    ui->labelD300_2       ->setGeometry(0.338*Width, 0.074*Height, 0.057*Width, 0.019*Height); ui->labelD300_2       ->hide();
    ui->labelD1280_2      ->setGeometry(0.119*Width, 0.305*Height, 0.057*Width, 0.019*Height); ui->labelD1280_2      ->hide();
    ui->labelD3280_2      ->setGeometry(0.229*Width, 0.305*Height, 0.057*Width, 0.019*Height); ui->labelD3280_2      ->hide();
    ui->labelD6480_2      ->setGeometry(0.338*Width, 0.305*Height, 0.057*Width, 0.019*Height); ui->labelD6480_2      ->hide();
    ui->pushButtonD10_2   ->setGeometry(0.119*Width, 0.203*Height, 0.057*Width, 0.028*Height); ui->pushButtonD10_2   ->hide();
    ui->pushButtonD60_2   ->setGeometry(0.229*Width, 0.203*Height, 0.057*Width, 0.028*Height); ui->pushButtonD60_2   ->hide();
    ui->pushButtonD300_2  ->setGeometry(0.338*Width, 0.203*Height, 0.057*Width, 0.028*Height); ui->pushButtonD300_2  ->hide();
    ui->pushButtonD1280_2 ->setGeometry(0.119*Width, 0.444*Height, 0.057*Width, 0.028*Height); ui->pushButtonD1280_2 ->hide();
    ui->pushButtonD3280_2 ->setGeometry(0.229*Width, 0.444*Height, 0.057*Width, 0.028*Height); ui->pushButtonD3280_2 ->hide();
    ui->pushButtonD6480_2 ->setGeometry(0.338*Width, 0.444*Height, 0.057*Width, 0.028*Height); ui->pushButtonD6480_2 ->hide();
    if(option==0)   //钻石商城
    {
        ui->label1            ->show();
        ui->label2            ->show();
        ui->label3            ->show();
        ui->label4            ->show();
        ui->label5            ->show();
        ui->label6            ->show();
        ui->labelD10          ->show();
        ui->labelD60          ->show();
        ui->labelD300         ->show();
        ui->labelD1280        ->show();
        ui->labelD3280        ->show();
        ui->labelD6480        ->show();
        ui->pushButtonD10     ->show();
        ui->pushButtonD60     ->show();
        ui->pushButtonD300    ->show();
        ui->pushButtonD1280   ->show();
        ui->pushButtonD3280   ->show();
        ui->pushButtonD6480   ->show();
    }
    else if(option == 1)
    {
        ui->label1_2          ->show();
        ui->label2_2          ->show();
        ui->label3_2          ->show();
        ui->label4_2          ->show();
        ui->label5_2          ->show();
        ui->label6_2          ->show();
        ui->labelD10_2        ->show();
        ui->labelD60_2        ->show();
        ui->labelD300_2       ->show();
        ui->labelD1280_2      ->show();
        ui->labelD3280_2      ->show();
        ui->labelD6480_2      ->show();
        ui->pushButtonD10_2   ->show();
        ui->pushButtonD60_2   ->show();
        ui->pushButtonD300_2  ->show();
        ui->pushButtonD1280_2 ->show();
        ui->pushButtonD3280_2 ->show();
        ui->pushButtonD6480_2 ->show();
    }
    connect(ui->DiamondMarketBtn,&QPushButton::clicked,this,&SuperMarketWidget::onDiamondMarketBtnClicked);
    connect(ui->BeanMarketBtn,&QPushButton::clicked,this,&SuperMarketWidget::onBeanMarketBtnClicked);

}

SuperMarketWidget::~SuperMarketWidget()
{
    delete ui;
}

void SuperMarketWidget::onDiamondMarketBtnClicked()
{
    ui->label1            ->show();
    ui->label2            ->show();
    ui->label3            ->show();
    ui->label4            ->show();
    ui->label5            ->show();
    ui->label6            ->show();
    ui->labelD10          ->show();
    ui->labelD60          ->show();
    ui->labelD300         ->show();
    ui->labelD1280        ->show();
    ui->labelD3280        ->show();
    ui->labelD6480        ->show();
    ui->pushButtonD10     ->show();
    ui->pushButtonD60     ->show();
    ui->pushButtonD300    ->show();
    ui->pushButtonD1280   ->show();
    ui->pushButtonD3280   ->show();
    ui->pushButtonD6480   ->show();
    ui->label1_2          ->hide();
    ui->label2_2          ->hide();
    ui->label3_2          ->hide();
    ui->label4_2          ->hide();
    ui->label5_2          ->hide();
    ui->label6_2          ->hide();
    ui->labelD10_2        ->hide();
    ui->labelD60_2        ->hide();
    ui->labelD300_2       ->hide();
    ui->labelD1280_2      ->hide();
    ui->labelD3280_2      ->hide();
    ui->labelD6480_2      ->hide();
    ui->pushButtonD10_2   ->hide();
    ui->pushButtonD60_2   ->hide();
    ui->pushButtonD300_2  ->hide();
    ui->pushButtonD1280_2 ->hide();
    ui->pushButtonD3280_2 ->hide();
    ui->pushButtonD6480_2 ->hide();
}
void SuperMarketWidget::onBeanMarketBtnClicked()
{
    ui->label1_2          ->show();
    ui->label2_2          ->show();
    ui->label3_2          ->show();
    ui->label4_2          ->show();
    ui->label5_2          ->show();
    ui->label6_2          ->show();
    ui->labelD10_2        ->show();
    ui->labelD60_2        ->show();
    ui->labelD300_2       ->show();
    ui->labelD1280_2      ->show();
    ui->labelD3280_2      ->show();
    ui->labelD6480_2      ->show();
    ui->pushButtonD10_2   ->show();
    ui->pushButtonD60_2   ->show();
    ui->pushButtonD300_2  ->show();
    ui->pushButtonD1280_2 ->show();
    ui->pushButtonD3280_2 ->show();
    ui->pushButtonD6480_2 ->show();
    ui->label1            ->hide();
    ui->label2            ->hide();
    ui->label3            ->hide();
    ui->label4            ->hide();
    ui->label5            ->hide();
    ui->label6            ->hide();
    ui->labelD10          ->hide();
    ui->labelD60          ->hide();
    ui->labelD300         ->hide();
    ui->labelD1280        ->hide();
    ui->labelD3280        ->hide();
    ui->labelD6480        ->hide();
    ui->pushButtonD10     ->hide();
    ui->pushButtonD60     ->hide();
    ui->pushButtonD300    ->hide();
    ui->pushButtonD1280   ->hide();
    ui->pushButtonD3280   ->hide();
    ui->pushButtonD6480   ->hide();
}
