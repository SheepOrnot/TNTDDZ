#ifndef PERSONALINFOWIDGET_H
#define PERSONALINFOWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QDateTime>
#include <QScrollBar>
#include <QPushButton>
#include <QMessageBox>
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
    void GetInfo(int _Rate,int _Matches,int _WinMatches,int _LoseMatches,int _ProfileIndex,std::string _Name,std::string _UID,std::string _Email);
private:
    Ui::PersonalInfoWidget *ui;
    int Width,Height;
    QString Rate,Matches,WinMatches,LoseMatches;
    QString Name,UID,Email;
    int ProfileIndex,ChangingProfileIndex;
    QPixmap ProfilePixmap;
    QWidget *ContentWidget;
    int ScrollWidgetHeight = 1000;
    std::vector<Record> records;
    std::vector<QLabel*> recordLabels;
    QPushButton *ApplyChange;
    bool CanGetRecord = 1;
private Q_SLOTS:
    void onProfileChanged(int index);
    void onScrollBarValueChanged();
    void onRecordToBottom();       //历史记录翻到底部了->跟服务器要后十条数据。
    void onApplyChangeClicked(); //上传修改的ProfileIndex到服务器
Q_SIGNALS:
    void scrollBarAtBotton();
};

#endif // PERSONALINFOWIDGET_H
