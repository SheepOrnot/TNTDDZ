#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "widgetcard.h"
#include "settingwidget.h"
#include "gameoverwidget.h"
#include <QFile>
#include <QJsonDocument>
#include <QPropertyAnimation>
#include <QJsonObject>
#include <QListView>
#include <QLabel>
#include <QTimer>
#include <QMediaPlayer>
#include <QCoreApplication>
#include <QRandomGenerator>
#include <QThread>
#include <iostream>
#include <QAudioOutput>
#include <bitset>
#include "messagecenter.h"
#include "widgetrevpacker.h"
#include "cardprocess.h"
namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(int _Width,int _Height,int _mode,QWidget *parent = nullptr);
    ~GameWidget();
//*******test********
    int TestStage = 0;
    std::bitset<54> previousBitset;
    std::bitset<54> nextBitset;
    std::bitset<54> playerBitset;
    std::bitset<54> finalBitset;
    std::bitset<54> playeroutBitset;
    std::bitset<54> previousoutBitset;
    std::bitset<54> nextoutBitset;
//*******end*********

    int Width,Height;
    std::vector<WidgetCard> PreviousPlayerOutCards,NextPlayerOutCards,PlayerOutCards,PlayerHandCards,FinalCards;    //   PlayerOutCards-> 返回的合法的牌
    std::bitset<54> SelectedCards = 0;//点击出牌时选中的牌（不知道合不合法）
    QString PreviousIdentityString,NextIdentityString,PlayerIdentityString;
    QString PreviousBeanNum,NextBeanNum,PlayerBeanNum;
    QMediaPlayer *BGMPlayer,*EffectPlayer;
    int Times = 1;
    int mode;
    void ShowIdentityIcon(std::string identity1,std::string identity2,std::string identity3);
    void placeHandCards();
    void placeOutCards(int Pos);
    void somebodyCallLandlordRound(int Pos);
    void somebodyBidForLandlordRound(int Pos);
    void somebodyDoubleRound();
    void somebodyPlayCardRound(int Pos);

    void somebodyOutCard(int Pos,std::bitset<54> Bitset,int Leftcards,int Cardtype,std::bitset<54> handcards = 0);
    void somebodyNotOutCard(int Pos,int Leftcards,std::bitset<54> handcards = 0);
    void somebodyReady(int Pos);
    void somebodyUnReady(int Pos);
    void somebodyCallLandlord(int Pos);
    void somebodyNotCallLandlord(int Pos);
    void somebodyBidForLandlord(int Pos);
    void somebodyNotBidForLandlord(int Pos);
    void somebodyDouble(int Pos);
    void somebodyNotDouble(int Pos);
    void somebodyEnterRoom(int Pos,int ProfileIndex,int Beans);
    void somebodyLeaveRoom(int Pos);
    void Dealingcards(std::bitset<54> handcards,int cardnum1 = 17,int cardnum2 = 17);
    void StartGame(std::string identity1,std::string identity2,std::string identity3,std::bitset<54> handcards,std::bitset<54> finalcards);
    void AddTimes(int newTimes);

    void interfaceSomebodyEnterRoom(WidgetArgPackage* arg);
    void interfaceSomebodyReady(WidgetArgPackage* arg);
    void interfaceDealingCards(WidgetArgPackage* arg);
    void interfaceCallLandlordRound(WidgetArgPackage* arg);
    void interfaceCallLandlord(WidgetArgPackage* arg);
    void interfaceBidForLandlordRound(WidgetArgPackage* arg);
    void interfaceBidForLandlord(WidgetArgPackage* arg);
    void interfacePlayCardRound(WidgetArgPackage* arg);
    void interfaceOutCard(WidgetArgPackage* arg);
    void interfaceGameEnd(WidgetArgPackage* arg);
    void interfaceStartGame(WidgetArgPackage* arg);

private:
    Ui::GameWidget *ui;
    int CardStyle;
    WidgetCard AllCards[54];
    QPixmap ProfilePixmap1,ProfilePixmap2,ProfilePixmap3,
        IdentityPixmap1,IdentityPixmap2,IdentityPixmap3,
        FinalCardPixmap1,FinalCardPixmap2,FinalCardPixmap3,
        ReadyPixmap,ClockPixmap;
    std::vector<QLabel*> backlabel1;
    std::vector<QLabel*> backlabel2;
    QAudioOutput *BGMaudioOutput,*EffectaudioOutput;
    QThread *BGMThread,*EffectThread;
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
    int PreviousOutCradsType,NextOutCradsType,PlayerOutCradsType;
    bool PreviousDouble,NextDouble,PlayerDouble;
    bool PreviousIdentity,NextIdentity,PlayerIdentity;
    QTimer *timer;
    int remainingTime;
    std::bitset<54> handcards;

    WidgetArgPackage* InterfaceArg[10];
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
        ":/image/image/Profile/0.jpg",
        ":/image/image/Profile/1.jpg",
        ":/image/image/Profile/2.jpg",
        ":/image/image/Profile/3.jpg",
        ":/image/image/Profile/4.jpg",
        ":/image/image/Profile/5.jpg",
        ":/image/image/Profile/6.jpg"
    };
    const QString CardTypeIndex[15] = {
        "None","Single","Pair","ThreePair","ThreePair_with_Single",
        "ThreePair_with_Pair",
        "Straight",
        "Pair_Straight",
        "Bomb",
        "Bomb_with_Single",
        "Bomb_with_Pair",
        "ThreePair_Straight",
        "ThreePair_Straight_with_Single",
        "ThreePair_Straight_with_Pair",
        "KingBomb"
    };

    std::shared_ptr<MessageCenter> message_center;
    std::shared_ptr<WidgetRevPacker> widget_rev_packer;
private:
    void InitAllCards();
    std::vector<WidgetCard> Transform_To_Vector(std::bitset<54> BitsetCards); //将CardArg中的OutCard和HandCard译成vector<WidgetCard>对象，包含Point Type Path
    std::bitset<54> Transform_To_Bitset(std::vector<WidgetCard> VectorCards); //将PreviousPlayerOutCards等译成Bitset对象，包含HandCard和OutCard

    void DestroyOutCards(int pos);
    void ImportConfig();
    void ConnectHandCards();
    void DisconnectHandCards();
    void AnimateMove(const QPoint& startPos, const QPoint& endPos,QPushButton *btn);
    void AnimateMoveLeft(QPushButton* btn, int distance);
    void PlacePreviousHandCards();
    void PlaceNextHandCards();
    void MakeSoundEffect(int Type); //0:叫地主  1：不叫  2：加倍  3：不加倍   4：抢地主   5：不抢    6：不出
                                    //7：上家出牌    8：下家出牌   9：自己出牌    10：游戏胜利    11：游戏失败
    void ShowFinalCards();
    void ShowProfiles(int Pos);
    void StartCountDown(int time,int pos);
    void updateCountDown();
    QString Transform_To_String(int Num);
private Q_SLOTS:
    void onSettingBtnClicked();
    void onPlayCardsClicked();    //点击出牌按钮，判断牌型和管牌逻辑；
    void onSkipTurnBtnClicked();    //点击不出按钮；
    void onCallLandlordBtnClicked();    //点击叫地主按钮
    void onSkipCallLandlordBtnClicked();//点击不叫按钮
    void onBidForLandlordBtnClicked();   //点击抢地主按钮
    void onSkipLandlordBidBtnClicked();  //点击不抢按钮
    void onDoubleBtnClicked();          //点击加倍按钮
    void onUnDoubleBtnClicked();        //点击不加倍按钮
    void onReadyBtnClicked();
    void onUnreadyBtnClicked();

    void doDealingCards();
    void doCallLandlordRound();
    void doCallLandlord();
    void doBidForLandlordRound();
    void doBidForLandlord();
    void doPlayCardRound();
    void doOutCard();
    void doStartGame();
Q_SIGNALS:
    void HaveNoHandCard();
};

#endif // GAMEWIDGET_H
