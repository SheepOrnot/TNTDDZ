#ifndef WIDGETCARD_H
#define WIDGETCARD_H
#include<QString>
#include<QPushButton>
class WidgetCard
{
public:
     WidgetCard();
    int Point,Type;
    QString ImagePath;
    QPushButton *btn;
    int Index;
};

#endif // WIDGETCARD_H
