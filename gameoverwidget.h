#ifndef GAMEOVERWIDGET_H
#define GAMEOVERWIDGET_H

#include <QWidget>

namespace Ui {
class GameOverWidget;
}

class GameOverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameOverWidget(int _Width,int _Height,QWidget *parent = nullptr);
    ~GameOverWidget();
    int Width,Height;

private:
    Ui::GameOverWidget *ui;
    QString PreviousUsername,NextUsername,PlayerUsername,
            PreviousTimes,NextTimes,PlayerTimes,
            PreviousScore,NextScore,PlayerScore;

};

#endif // GAMEOVERWIDGET_H
