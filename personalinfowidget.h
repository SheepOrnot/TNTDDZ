#ifndef PERSONALINFOWIDGET_H
#define PERSONALINFOWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QDateTime>
#include <QScrollBar>
namespace Ui {
class PersonalInfoWidget;
}

class PersonalInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalInfoWidget(int _Width,int _Height,QWidget *parent = nullptr);
    ~PersonalInfoWidget();
    struct Record
    {
        std::string time;
        int Score;
        std::string WinorLose;
        std::string identity;
        std::string Mode;
    };
    void UpdataRecords(bool isLast,std::vector<Record> TenRecords);
private:
    Ui::PersonalInfoWidget *ui;
    int Width,Height;
    int Rate,Matches,WinMatches,LoseMatches;
    QString Name,UID,Email;
    int ProfileIndex;
    QPixmap ProfilePixmap;
    QWidget *ContentWidget;
    int ScrollWidgetHeight = 1000;
    std::vector<Record> records;
    std::vector<QLabel*> recordLabels;
    bool CanGetRecord = 1;
private Q_SLOTS:
    void onProfileChanged(int index);
    void onScrollBarValueChanged();
    void onRecordToBottom();       //历史记录翻到底部了->跟服务器要后十条数据。
signals:
    void scrollBarAtBotton();
};

#endif // PERSONALINFOWIDGET_H
