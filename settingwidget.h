#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegExp>
#include <QDialog>
#include <QVBoxLayout>
namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(int _Width,int _Height,QWidget *parent = nullptr);
    ~SettingWidget();
    int Width;
    int Height;
private:
    Ui::SettingWidget *ui;
    bool GameBGMState,LobbyBGMState,GameEffectState,FullScreenState;
    double GameBGMVolume,GameEffectVolume;
    int ResolutionIndex,CardStyleIndex;
    QString NewGameBGMVolume,NewGameEffectVolume;
    QString NewGameBGM,NewGameEffect;
    QString NewLobbyBGM;
    QString NewWidth,NewHeight;
    QString NewCardStyleIndex;
    QString NewResolutionIndex;
    QString NewFullScreen;
    QPixmap CardFrontPixmap,CardBackPixmap;
    QString optipnStyleSheet;
private:
    void WriteBackConfig();
    void ImportConfig();
    void RestoreConfig();
private Q_SLOTS:
    void onBasicBtnClicked();
    void onFrameBtnClicked();
    void onSoundEffectBtnClicked();
    void onApplyBtnClicked();
    void onBGMVolumeChanged();
    void onEffectVolumeChanged();
    void onBGMCheckChanged();
    void onEffectCheckChanged();
    void onCardStyleChanged(int index);

};

#endif // SETTINGWIDGET_H
