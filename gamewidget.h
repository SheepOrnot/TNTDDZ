#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "widgetargcard.h"
#include "widgetcard.h"
namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();
    int Width=1080,Height=1920;     //用于修改分辨率&实例化新的窗口时的参数。
    std::vector<WidgetCard> PreviousPlayerOutCards,NextPlayerOutCards,PlayerOutCards,PlayerHandCards,FinalCards;
    WidgetArgCard CardArg;

private:
    Ui::GameWidget *ui;
    int CardStyle = 0;
    WidgetCard AllCards[54];
//    void InitAllCards(WidgetCard AllCards[54]);
    //将CardArg中的OutCard和HandCard译成vector<WidgetCard>对象，包含Point Type Path
//    std::vector<WidgetCard> Transform_To_Vector(std::bitset<54> BitsetCards);
    //将PreviousPlayerOutCards等译成Bitset对象，包含HandCard和OutCard
//    std::bitset<54> Transform_To_Bitset(std::vector<WidgetCard> VectorCards);
private slots:
//    void ResolutionChanged(int _Width,int _Height);      //接收设置界面发出的分辨率修改信号。
};

#endif // GAMEWIDGET_H
