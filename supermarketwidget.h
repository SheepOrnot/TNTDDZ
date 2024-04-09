#ifndef SUPERMARKETWIDGET_H
#define SUPERMARKETWIDGET_H

#include <QWidget>

namespace Ui {
class SuperMarketWidget;
}

class SuperMarketWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SuperMarketWidget(int _Width,int _Height,int _option,QWidget *parent = nullptr);
    ~SuperMarketWidget();

private:
    Ui::SuperMarketWidget *ui;
    int Width,Height;
    int option;
    void onDiamondMarketBtnClicked();
    void onBeanMarketBtnClicked();
};

#endif // SUPERMARKETWIDGET_H
