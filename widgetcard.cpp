#include "widgetcard.h"
WidgetCard::WidgetCard()
{
    //connect(btn, &QPushButton::clicked, this, &WidgetCard::toggleMove);
}
void WidgetCard::toggleMove() {
    if (!isUp) {
        animateMove(btn->pos(), btn->pos() - QPoint(0, 50));
    } else {
        animateMove(btn->pos(), btn->pos() + QPoint(0, 50));
    }
    isUp = !isUp;
}

void WidgetCard::animateMove(const QPoint& startPos, const QPoint& endPos) {
    QPropertyAnimation* animation = new QPropertyAnimation(btn, "pos");
    animation->setDuration(500);
    animation->setStartValue(startPos);
    animation->setEndValue(endPos);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    animation->start();
}
