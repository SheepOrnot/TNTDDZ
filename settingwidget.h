#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>

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
};

#endif // SETTINGWIDGET_H
