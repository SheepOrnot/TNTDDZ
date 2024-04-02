#ifndef LOBBYWIDGET_H
#define LOBBYWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QGraphicsOpacityEffect>
#include <QMediaPlayer>
#include <QCoreApplication>
#include <QThread>
#include <QMediaPlaylist>
#include"settingwidget.h"
#include"gamewidget.h"
namespace Ui {
class LobbyWidget;
}

class LobbyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LobbyWidget(QWidget *parent = nullptr);
    ~LobbyWidget();
private:
    Ui::LobbyWidget *ui;
    int Width=1920,Height=1080;     //用于修改分辨率&实例化新的窗口时的参数。
    int radius;
    bool BGMState;
    QString ProfileImagePath;        //头像图片(服务器获取)
    QString BeanNum,DiamondNum;      //豆和钻石数量(服务器获取)
    QString Username,UID;            //username和uid(服务器获取)
    QString RollPixmapsPath[7] = {
        ":/image/image/Profile/mjq.jpg",
        ":/image/image/Profile/syx.jpg",
        ":/image/image/Profile/lyw.jpg",
        ":/image/image/Profile/dcx.jpg",
        ":/image/image/Profile/zzy.jpg",
        ":/image/image/Profile/yhx.jpg",
        ":/image/image/Profile/hjl.jpg"
    };
    QPixmap DiamondPixmap,BeanPixmap;
    QPixmap ProfilePixmap;
    QTimer *RollImageTimer;
    int RollImageIndex;
    SettingWidget *settingWidget;
    GameWidget *gameWidget;
    QPushButton *GameExitBtn;
    QMediaPlayer BGMPlayer;
    QThread *BGMThread;
private:
    void ImportConfig();
public Q_SLOTS:
    void ResolutionChanged(int _Width,int _Height);
    //void ProfileChanged(int _Width,int _Height);
private Q_SLOTS:
    void onSettingBtnClicked();
    void onClassicModeBtnClicked();
    void onExitGameBtnClicked();
    void RollImage();
Q_SIGNALS:
    void ChangeResolutions(int _Width,int _Height);            //********测试用 ;

};

#endif // LOBBYWIDGET_H
