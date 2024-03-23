#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(int _Width,int _Height,QWidget *parent) :
    QWidget(parent),Width(_Width),Height(_Height),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
    this->setFixedSize(0.618*Width,0.618*Height);
}

SettingWidget::~SettingWidget()
{
    delete ui;
}
