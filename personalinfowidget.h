#ifndef PERSONALINFOWIDGET_H
#define PERSONALINFOWIDGET_H

#include <QWidget>
#include <QPainter>
namespace Ui {
class PersonalInfoWidget;
}

class PersonalInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalInfoWidget(int _Width,int _Height,QWidget *parent = nullptr);
    ~PersonalInfoWidget();

private:
    Ui::PersonalInfoWidget *ui;
    int Width,Height;
    int Rate,Matches,WinMatches,LoseMatches;
    QString Name,UID,Email;
    int ProfileIndex;
    QPixmap ProfilePixmap;
private Q_SLOTS:
    void onProfileChanged(int index);

};

#endif // PERSONALINFOWIDGET_H
