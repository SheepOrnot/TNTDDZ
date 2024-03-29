#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "widgetargcard.h"
#include "widgetcard.h"
#include "settingwidget.h"
#include "gameoverwidget.h"

#include <QListView>
namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(int _Width,int _Height,QWidget *parent = nullptr);
    ~GameWidget();
    int Width,Height;
    std::vector<WidgetCard> PreviousPlayerOutCards,NextPlayerOutCards,PlayerOutCards,PlayerHandCards,FinalCards;
    WidgetArgCard CardArg;             //卡牌参数对象
    int PreviousProfileNum,NextProfileNum,PlayerProfileNum;
    QString PreviousIdentity,NextIdentity,PlayerIdentity;
    QString PreviousBeanNum,NextBeanNum,PlayerBeanNum;
private:
    Ui::GameWidget *ui;
    int CardStyle;
    WidgetCard AllCards[54];
    QPixmap ProfilePixmap1,ProfilePixmap2,ProfilePixmap3,
        IdentityPixmap1,IdentityPixmap2,IdentityPixmap3,
        ClockPixmap;
    SettingWidget *settingWidget;
    GameOverWidget *gameoverWidget;
    QIcon BeanIcon;
    int radius;
    const QString TypeIndex[6] = { "",
        "spades",
        "hearts",
        "clubs",
        "diamonds",
        "joker"
    };
    const QString PointIndex[18] = {"","","",
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
        "black",
        "red"
    };
    const QString ProfilePathIndex[7] = {
        ":/image/image/Profile/mjq.jpg",
        ":/image/image/Profile/syx.jpg",
        ":/image/image/Profile/lyw.jpg",
        ":/image/image/Profile/dcx.jpg",
        ":/image/image/Profile/zzy.jpg",
        ":/image/image/Profile/yhx.jpg",
        ":/image/image/Profile/hjl.jpg"
    };
private:
    void InitAllCards();
//    void PlaceHandCrads();
//    void PlacePlayerOutCards();
//    void PlacePreviousOutCards();
//    void PlaceNextOutCards();
    std::vector<WidgetCard> Transform_To_Vector(std::bitset<54> BitsetCards); //将CardArg中的OutCard和HandCard译成vector<WidgetCard>对象，包含Point Type Path
    std::bitset<54> Transform_To_Bitset(std::vector<WidgetCard> VectorCards); //将PreviousPlayerOutCards等译成Bitset对象，包含HandCard和OutCard
    void ShowIdentityIcon();
    void placeHandCards();
    void placeOutCards(int Pos);
private slots:
    void ResolutionChanged(int _Width,int _Height);      //接收设置界面发出的分辨率修改信号。
    void onSettingBtnClicked();
};

#endif // GAMEWIDGET_H
