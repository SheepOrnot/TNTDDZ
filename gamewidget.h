#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "widgetargcard.h"
#include "widgetcard.h"
#include "settingwidget.h"
#include "gameoverwidget.h"
#include <QFile>
#include <QJsonDocument>
#include <QPropertyAnimation>
#include <QJsonObject>
#include <QListView>
#include <QLabel>
#include <QMediaPlayer>
#include <QCoreApplication>
#include <QThread>
#include <QAudioOutput>
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
    std::bitset<54> SelectedCards = 0;
    WidgetArgCard CardArg;             //卡牌参数对象
    QString PreviousIdentity,NextIdentity,PlayerIdentity;
    QString PreviousBeanNum,NextBeanNum,PlayerBeanNum;
    QMediaPlayer *BGMPlayer;
private:
    Ui::GameWidget *ui;
    int CardStyle;
    WidgetCard AllCards[54];
    QPixmap ProfilePixmap1,ProfilePixmap2,ProfilePixmap3,
        IdentityPixmap1,IdentityPixmap2,IdentityPixmap3,
        ClockPixmap;

    QAudioOutput *BGMaudioOutput;
    QThread *BGMThread;
    SettingWidget *settingWidget;
    GameOverWidget *gameoverWidget;
    QIcon BeanIcon;
    QPixmap CardBackPixmap;
    QLabel *PreviousCardsNumLabel, *NextCardsNumLabel;
    bool BGMState,EffectState;
    int radius,RoomIdFontSize;
    double BGMVolume,EffectVolume;
    int PreviousCardsNumber,NextCardsNumber;
    int PreviousProfileIndex,NextProfileIndex,PlayerProfileIndex;
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
    std::vector<WidgetCard> Transform_To_Vector(std::bitset<54> BitsetCards); //将CardArg中的OutCard和HandCard译成vector<WidgetCard>对象，包含Point Type Path
    std::bitset<54> Transform_To_Bitset(std::vector<WidgetCard> VectorCards); //将PreviousPlayerOutCards等译成Bitset对象，包含HandCard和OutCard
    void ShowIdentityIcon();
    void placeHandCards();
    void placeOutCards(int Pos);
    void DestroyOutCards(int pos);
    void ImportConfig();
    void ConnectHandCards();
    void DisconnectHandCards();
    void AnimateMove(const QPoint& startPos, const QPoint& endPos,QPushButton *btn);
    void AnimateMoveLeft(QPushButton* btn, int distance);
    void PlacePreviousHandCards();
    void PlaceNextHandCards();
private slots:
    void onSettingBtnClicked();
    void onPlayCardsClicked();    //点击出牌按钮，判断牌型和管牌逻辑；
    // void onSkipTurnBtnClicked();    //点击不出按钮；
    // void onCallLandlordBtnClicked();    //点击叫地主按钮
    // void onSkipCallLandlordBtnClicked();//点击不叫按钮
    // void onBidForLandlordBtnClicked();   //点击抢地主按钮
    // void onSkipLandlordBidBtnClicked();  //点击不抢按钮
    // void onDoubleBtnClicked();          //点击加倍按钮
    // void onUnDoubleBtnClicked();        //点击不加倍按钮
signals:
    void HaveNoHandCard();
};

#endif // GAMEWIDGET_H
