#ifndef WIDGETCARD_H
#define WIDGETCARD_H
#include<QString>
#include<QPushButton>
#include<QPropertyAnimation>
#include<QObject>

/*
class WidgetCardButton : public QPushButton
{
    Q_OBJECT
public:

};
*/


class WidgetCard
{

public:
    WidgetCard();
    int Point,Type;
    QString ImagePath;
    QPushButton *btn;
    int Index;
    bool isUp = false;
    void toggleMove();
private:
    void animateMove(const QPoint& startPos, const QPoint& endPos);
private slots:


};

#endif // WIDGETCARD_H
