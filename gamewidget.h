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
    int Width,Height;
    std::vector<WidgetCard> PreviousPlayerOutCards,NextPlayerOutCards,PlayerOutCards,PlayerHandCards,FinalCards;
    WidgetArgCard CardArg;
    const QString TypeIndex[6] = { "",
        "spades",
        "hearts",
        "clubs",
        "diamonds",
        "joker"
    };
    const QString PointIndex[16] = {"","","",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "10",
        "jack",
        "queen",
        "king",
        "ace",
        "2",
    };

private:
    Ui::GameWidget *ui;
    int CardStyle = 0;
    WidgetCard AllCards[54];
    void InitAllCards();
    //将CardArg中的OutCard和HandCard译成vector<WidgetCard>对象，包含Point Type Path
//    std::vector<WidgetCard> Transform_To_Vector(std::bitset<54> BitsetCards);
    //将PreviousPlayerOutCards等译成Bitset对象，包含HandCard和OutCard
//    std::bitset<54> Transform_To_Bitset(std::vector<WidgetCard> VectorCards);
private slots:
//    void ResolutionChanged(int _Width,int _Height);      //接收设置界面发出的分辨率修改信号。
};

#endif // GAMEWIDGET_H
