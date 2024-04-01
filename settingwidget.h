#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QDebug>
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
    double gameBGMVolume,gameEffectVolume;
    bool LobbyBGM;
    int NewWidth,NewHeight;
    int CardStyle;
private:
    void WriteBackConfig();
private slots:
    void onBasicBtnClicked();
    void onFrameBtnClicked();
    void onSoundEffectBtnClicked();
    void onApplyBtnClicked();
};

#endif // SETTINGWIDGET_H
