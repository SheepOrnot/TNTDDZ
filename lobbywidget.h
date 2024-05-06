#ifndef LOBBYWIDGET_H
#define LOBBYWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QGraphicsOpacityEffect>
#include <QThread>
#include"settingwidget.h"
#include"gamewidget.h"
#include"personalinfowidget.h"
#include "supermarketwidget.h"
#include "rulewidget.h"
#include "messagecenter.h"
#include "widgetrevpacker.h"

namespace Ui {
class LobbyWidget;
}

class LobbyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LobbyWidget(QWidget *parent = nullptr);
    ~LobbyWidget();

    void InitInfo(int _ProfileImageIndex,long long _BeanNum,long long _DiamondNum, std::string _Username, std::string _UID);
    void interfaceEnterRoomSuccess(WidgetArgPackage* arg);
    void interfaceEnterRoomFail(WidgetArgPackage* arg);
    void interfaceExitRoom(WidgetArgPackage* arg);
    void interfaceInfoInit(WidgetArgPackage* arg);

    WidgetArgPackage* Arg;

private:
    Ui::LobbyWidget *ui;
    int Width,Height;     //用于修改分辨率&实例化新的窗口时的参数。
    int SettingWidth,SettingHeight;
    int radius;
    bool BGMState;
    bool isFullScreen;
    int ProfileImageIndex;
    QString ProfileImagePath;        //头像图片(服务器获取)
    QString BeanNum,DiamondNum;      //豆和钻石数量(服务器获取)
    QString Username,UID;            //username和uid(服务器获取)
    QString RollPixmapsPath[7] = {
        ":/image/image/Profile/0.jpg",
        ":/image/image/Profile/1.jpg",
        ":/image/image/Profile/2.jpg",
        ":/image/image/Profile/3.jpg",
        ":/image/image/Profile/4.jpg",
        ":/image/image/Profile/5.jpg",
        ":/image/image/Profile/6.jpg"
    };
    QPixmap DiamondPixmap,BeanPixmap;
    QPixmap ProfilePixmap;
    QTimer *RollImageTimer;
    int RollImageIndex;
    SettingWidget *settingWidget;
    GameWidget *gameWidget;
    QPushButton *GameExitBtn;
    QMediaPlayer *BGMPlayer;
    QAudioOutput *BGMaudioOutput;
    QThread *BGMThread;
    PersonalInfoWidget *personalInfoWidget;
    SuperMarketWidget *SuperMarket;
    RuleWidget *ruleWidget;

    std::shared_ptr<MessageCenter> message_center;
    std::shared_ptr<WidgetRevPacker> widget_rev_packer;

    int signlemode = 0;

private:
    void ImportConfig();
public Q_SLOTS:
    void ResolutionChanged(int _Width,int _Height);
    //void ProfileChanged(int _Width,int _Height);
    QString Transform_To_String(long long Num);
private Q_SLOTS:
    void onSettingBtnClicked();
    void onClassicModeBtnClicked();
    void onJoinRoomBtnClicked();
    void onExitGameBtnClicked();
    void onPersonalInfoBtnClicked();
    void RollImage();
    void onSingleModeBtnClicked();
    void onDiamondShopClicked();
    void onBeanShopClicked();
    void onRuleBtnClicked();
    void onExitBtnClicked();
    void EnterGame();
    void doInfoInit();
    void doExitRoom();
Q_SIGNALS:
    void ChangeResolutions(int _Width,int _Height);            //********测试用 ;

};

#endif // LOBBYWIDGET_H
