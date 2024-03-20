#include "lobbywidget.h"
#include "ui_lobbywidget.h"

LobbyWidget::LobbyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LobbyWidget)
{
    ui->setupUi(this);
}

LobbyWidget::~LobbyWidget()
{
    delete ui;
}
