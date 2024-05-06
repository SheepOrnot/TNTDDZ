#ifndef GAMEOVERWIDGET_H
#define GAMEOVERWIDGET_H
#include <QPushButton>
#include <QWidget>

namespace Ui {
class GameOverWidget;
}

class GameOverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameOverWidget(int _Width,int _Height,bool _Result,int _times,
                            bool _identity1, bool _identity2,bool _identity3,
                            QString _Name1,QString _Name2,QString _Name3,
                            bool _double1,bool _double2,bool _double3,
                            int _Score1,int _Score2,int _Score3,
                            QWidget *parent = nullptr);
    ~GameOverWidget();


private:
    Ui::GameOverWidget *ui;
    int Width,Height;
    int times;
    bool Result;
    bool identity1,identity2,identity3;
    bool double1,double2,double3;
    QString Name1,Name2,Name3;
    int BaseScore = 100;
    int Score1,Score2,Score3;
    bool Result1,Result2,Result3;
    QString PreviousTimes,NextTimes,PlayerTimes,
            PreviousScore,NextScore,PlayerScore,
            PreviousIdentity,NextIdentity,PlayerIdentity,
            PreviousResult,NextResult,PlayerResult;
};

#endif // GAMEOVERWIDGET_H
