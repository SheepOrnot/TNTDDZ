#include "personalinfowidget.h"
#include "ui_personalinfowidget.h"

PersonalInfoWidget::PersonalInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalInfoWidget)
{
    ui->setupUi(this);
}

PersonalInfoWidget::~PersonalInfoWidget()
{
    delete ui;
}
