/********************************************************************************
** Form generated from reading UI file 'gamewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWIDGET_H
#define UI_GAMEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWidget
{
public:
    QLabel *FinalCard1;
    QLabel *FinalCard2;
    QLabel *FinalCard3;
    QLabel *MultiplierLabel;
    QPushButton *RuleBtn;
    QPushButton *SettingBtn;
    QLabel *ProfileLabel1;
    QLabel *ProfileLabel2;
    QLineEdit *BeansLineEdit1;
    QLineEdit *BeansLineEdit2;
    QLabel *ClockNum;
    QLabel *ClockImageLabel;
    QLabel *DoubleLabel1;
    QLabel *DoubleLabel2;
    QLabel *IdentityLabel1;
    QLabel *IdentityLabel2;
    QPushButton *PlayCardBtn;
    QLabel *ProfileLabel3;
    QLineEdit *BeansLineEdit3;
    QLabel *DoubleLabel3;
    QLabel *IdentityLabel3;
    QComboBox *ChatComboBox;
    QPushButton *SkipTurnBtn;
    QPushButton *CallLandlordBtn;
    QPushButton *SkipCallLandlordBtn;
    QPushButton *BidForLandlordBtn;
    QPushButton *SkipLandlordBidBtn;
    QPushButton *DoubleBtn;
    QPushButton *UnDoubleBtn;
    QLabel *RoomId;
    QLabel *MSGLabel1;
    QLabel *MSGLabel2;
    QLabel *MSGLabel3;
    QPushButton *ReadyBtn;
    QLabel *ReadyLabel3;
    QLabel *ReadyLabel1;
    QLabel *ReadyLabel2;
    QPushButton *UnReadyBtn;
    QTableView *Recorder;
    QLabel *Name1;
    QLabel *Name2;
    QLabel *Name3;

    void setupUi(QWidget *GameWidget)
    {
        if (GameWidget->objectName().isEmpty())
            GameWidget->setObjectName("GameWidget");
        GameWidget->resize(1920, 1080);
        GameWidget->setStyleSheet(QString::fromUtf8(""));
        FinalCard1 = new QLabel(GameWidget);
        FinalCard1->setObjectName("FinalCard1");
        FinalCard1->setGeometry(QRect(740, 20, 81, 111));
        FinalCard1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        FinalCard2 = new QLabel(GameWidget);
        FinalCard2->setObjectName("FinalCard2");
        FinalCard2->setGeometry(QRect(850, 20, 81, 111));
        FinalCard2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        FinalCard3 = new QLabel(GameWidget);
        FinalCard3->setObjectName("FinalCard3");
        FinalCard3->setGeometry(QRect(950, 20, 81, 111));
        FinalCard3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        MultiplierLabel = new QLabel(GameWidget);
        MultiplierLabel->setObjectName("MultiplierLabel");
        MultiplierLabel->setGeometry(QRect(1040, 50, 81, 81));
        RuleBtn = new QPushButton(GameWidget);
        RuleBtn->setObjectName("RuleBtn");
        RuleBtn->setGeometry(QRect(1730, 20, 61, 61));
        SettingBtn = new QPushButton(GameWidget);
        SettingBtn->setObjectName("SettingBtn");
        SettingBtn->setGeometry(QRect(1810, 20, 61, 61));
        ProfileLabel1 = new QLabel(GameWidget);
        ProfileLabel1->setObjectName("ProfileLabel1");
        ProfileLabel1->setGeometry(QRect(50, 270, 121, 131));
        ProfileLabel1->setStyleSheet(QString::fromUtf8(""));
        ProfileLabel2 = new QLabel(GameWidget);
        ProfileLabel2->setObjectName("ProfileLabel2");
        ProfileLabel2->setGeometry(QRect(1740, 280, 121, 131));
        ProfileLabel2->setStyleSheet(QString::fromUtf8(""));
        BeansLineEdit1 = new QLineEdit(GameWidget);
        BeansLineEdit1->setObjectName("BeansLineEdit1");
        BeansLineEdit1->setGeometry(QRect(40, 440, 121, 31));
        BeansLineEdit2 = new QLineEdit(GameWidget);
        BeansLineEdit2->setObjectName("BeansLineEdit2");
        BeansLineEdit2->setGeometry(QRect(1740, 460, 121, 31));
        ClockNum = new QLabel(GameWidget);
        ClockNum->setObjectName("ClockNum");
        ClockNum->setGeometry(QRect(1550, 250, 20, 21));
        ClockNum->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 127);"));
        ClockImageLabel = new QLabel(GameWidget);
        ClockImageLabel->setObjectName("ClockImageLabel");
        ClockImageLabel->setGeometry(QRect(1540, 240, 41, 41));
        ClockImageLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        DoubleLabel1 = new QLabel(GameWidget);
        DoubleLabel1->setObjectName("DoubleLabel1");
        DoubleLabel1->setGeometry(QRect(120, 460, 51, 19));
        DoubleLabel2 = new QLabel(GameWidget);
        DoubleLabel2->setObjectName("DoubleLabel2");
        DoubleLabel2->setGeometry(QRect(1740, 470, 51, 19));
        IdentityLabel1 = new QLabel(GameWidget);
        IdentityLabel1->setObjectName("IdentityLabel1");
        IdentityLabel1->setGeometry(QRect(90, 220, 41, 41));
        IdentityLabel1->setStyleSheet(QString::fromUtf8(""));
        IdentityLabel2 = new QLabel(GameWidget);
        IdentityLabel2->setObjectName("IdentityLabel2");
        IdentityLabel2->setGeometry(QRect(1780, 230, 41, 41));
        IdentityLabel2->setStyleSheet(QString::fromUtf8(""));
        PlayCardBtn = new QPushButton(GameWidget);
        PlayCardBtn->setObjectName("PlayCardBtn");
        PlayCardBtn->setGeometry(QRect(630, 770, 161, 51));
        ProfileLabel3 = new QLabel(GameWidget);
        ProfileLabel3->setObjectName("ProfileLabel3");
        ProfileLabel3->setGeometry(QRect(120, 890, 121, 131));
        ProfileLabel3->setStyleSheet(QString::fromUtf8(""));
        BeansLineEdit3 = new QLineEdit(GameWidget);
        BeansLineEdit3->setObjectName("BeansLineEdit3");
        BeansLineEdit3->setGeometry(QRect(120, 1050, 121, 31));
        DoubleLabel3 = new QLabel(GameWidget);
        DoubleLabel3->setObjectName("DoubleLabel3");
        DoubleLabel3->setGeometry(QRect(260, 1040, 51, 19));
        IdentityLabel3 = new QLabel(GameWidget);
        IdentityLabel3->setObjectName("IdentityLabel3");
        IdentityLabel3->setGeometry(QRect(160, 840, 41, 41));
        IdentityLabel3->setStyleSheet(QString::fromUtf8(""));
        ChatComboBox = new QComboBox(GameWidget);
        ChatComboBox->setObjectName("ChatComboBox");
        ChatComboBox->setGeometry(QRect(1700, 1010, 201, 31));
        SkipTurnBtn = new QPushButton(GameWidget);
        SkipTurnBtn->setObjectName("SkipTurnBtn");
        SkipTurnBtn->setGeometry(QRect(1000, 770, 161, 51));
        CallLandlordBtn = new QPushButton(GameWidget);
        CallLandlordBtn->setObjectName("CallLandlordBtn");
        CallLandlordBtn->setGeometry(QRect(630, 750, 161, 51));
        SkipCallLandlordBtn = new QPushButton(GameWidget);
        SkipCallLandlordBtn->setObjectName("SkipCallLandlordBtn");
        SkipCallLandlordBtn->setGeometry(QRect(1000, 750, 161, 51));
        BidForLandlordBtn = new QPushButton(GameWidget);
        BidForLandlordBtn->setObjectName("BidForLandlordBtn");
        BidForLandlordBtn->setGeometry(QRect(630, 730, 161, 51));
        SkipLandlordBidBtn = new QPushButton(GameWidget);
        SkipLandlordBidBtn->setObjectName("SkipLandlordBidBtn");
        SkipLandlordBidBtn->setGeometry(QRect(1000, 730, 161, 51));
        DoubleBtn = new QPushButton(GameWidget);
        DoubleBtn->setObjectName("DoubleBtn");
        DoubleBtn->setGeometry(QRect(630, 710, 161, 51));
        UnDoubleBtn = new QPushButton(GameWidget);
        UnDoubleBtn->setObjectName("UnDoubleBtn");
        UnDoubleBtn->setGeometry(QRect(1000, 710, 161, 51));
        RoomId = new QLabel(GameWidget);
        RoomId->setObjectName("RoomId");
        RoomId->setGeometry(QRect(1570, 30, 131, 41));
        RoomId->setStyleSheet(QString::fromUtf8("font: 600 20pt \"Sitka Subheading Semibold\";\n"
"border-color: rgb(0, 0, 0);\n"
"border:1px solid;"));
        MSGLabel1 = new QLabel(GameWidget);
        MSGLabel1->setObjectName("MSGLabel1");
        MSGLabel1->setGeometry(QRect(340, 360, 171, 41));
        MSGLabel2 = new QLabel(GameWidget);
        MSGLabel2->setObjectName("MSGLabel2");
        MSGLabel2->setGeometry(QRect(1400, 340, 171, 41));
        MSGLabel3 = new QLabel(GameWidget);
        MSGLabel3->setObjectName("MSGLabel3");
        MSGLabel3->setGeometry(QRect(820, 770, 171, 41));
        ReadyBtn = new QPushButton(GameWidget);
        ReadyBtn->setObjectName("ReadyBtn");
        ReadyBtn->setGeometry(QRect(810, 740, 161, 51));
        ReadyLabel3 = new QLabel(GameWidget);
        ReadyLabel3->setObjectName("ReadyLabel3");
        ReadyLabel3->setGeometry(QRect(150, 880, 61, 51));
        ReadyLabel1 = new QLabel(GameWidget);
        ReadyLabel1->setObjectName("ReadyLabel1");
        ReadyLabel1->setGeometry(QRect(70, 260, 61, 51));
        ReadyLabel2 = new QLabel(GameWidget);
        ReadyLabel2->setObjectName("ReadyLabel2");
        ReadyLabel2->setGeometry(QRect(1770, 290, 61, 51));
        UnReadyBtn = new QPushButton(GameWidget);
        UnReadyBtn->setObjectName("UnReadyBtn");
        UnReadyBtn->setGeometry(QRect(810, 730, 161, 51));
        Recorder = new QTableView(GameWidget);
        Recorder->setObjectName("Recorder");
        Recorder->setGeometry(QRect(310, 20, 401, 71));
        Name1 = new QLabel(GameWidget);
        Name1->setObjectName("Name1");
        Name1->setGeometry(QRect(40, 410, 121, 21));
        Name2 = new QLabel(GameWidget);
        Name2->setObjectName("Name2");
        Name2->setGeometry(QRect(1740, 430, 121, 21));
        Name3 = new QLabel(GameWidget);
        Name3->setObjectName("Name3");
        Name3->setGeometry(QRect(120, 1020, 121, 21));
        ClockImageLabel->raise();
        FinalCard1->raise();
        FinalCard2->raise();
        FinalCard3->raise();
        MultiplierLabel->raise();
        RuleBtn->raise();
        SettingBtn->raise();
        ProfileLabel1->raise();
        ProfileLabel2->raise();
        BeansLineEdit1->raise();
        BeansLineEdit2->raise();
        ClockNum->raise();
        DoubleLabel1->raise();
        DoubleLabel2->raise();
        IdentityLabel1->raise();
        IdentityLabel2->raise();
        PlayCardBtn->raise();
        ProfileLabel3->raise();
        BeansLineEdit3->raise();
        DoubleLabel3->raise();
        IdentityLabel3->raise();
        ChatComboBox->raise();
        SkipTurnBtn->raise();
        CallLandlordBtn->raise();
        SkipCallLandlordBtn->raise();
        BidForLandlordBtn->raise();
        SkipLandlordBidBtn->raise();
        DoubleBtn->raise();
        UnDoubleBtn->raise();
        RoomId->raise();
        MSGLabel1->raise();
        MSGLabel2->raise();
        MSGLabel3->raise();
        ReadyBtn->raise();
        ReadyLabel3->raise();
        ReadyLabel1->raise();
        ReadyLabel2->raise();
        UnReadyBtn->raise();
        Recorder->raise();
        Name1->raise();
        Name2->raise();
        Name3->raise();

        retranslateUi(GameWidget);

        QMetaObject::connectSlotsByName(GameWidget);
    } // setupUi

    void retranslateUi(QWidget *GameWidget)
    {
        GameWidget->setWindowTitle(QCoreApplication::translate("GameWidget", "Form", nullptr));
        FinalCard1->setText(QCoreApplication::translate("GameWidget", "\345\272\225\347\211\2141", nullptr));
        FinalCard2->setText(QCoreApplication::translate("GameWidget", "\345\272\225\347\211\2142", nullptr));
        FinalCard3->setText(QCoreApplication::translate("GameWidget", "\345\272\225\347\211\2143", nullptr));
        MultiplierLabel->setText(QCoreApplication::translate("GameWidget", "\345\200\215\346\225\260\n"
"X6", nullptr));
        RuleBtn->setText(QString());
        SettingBtn->setText(QString());
        ProfileLabel1->setText(QCoreApplication::translate("GameWidget", "Profile1", nullptr));
        ProfileLabel2->setText(QCoreApplication::translate("GameWidget", "Profile2", nullptr));
        BeansLineEdit1->setText(QString());
        BeansLineEdit2->setText(QString());
        ClockNum->setText(QCoreApplication::translate("GameWidget", "30", nullptr));
        ClockImageLabel->setText(QCoreApplication::translate("GameWidget", "clock", nullptr));
        DoubleLabel1->setText(QString());
        DoubleLabel2->setText(QString());
        IdentityLabel1->setText(QString());
        IdentityLabel2->setText(QString());
        PlayCardBtn->setText(QCoreApplication::translate("GameWidget", "\345\207\272\347\211\214", nullptr));
        ProfileLabel3->setText(QCoreApplication::translate("GameWidget", "Profile3", nullptr));
        BeansLineEdit3->setText(QString());
        DoubleLabel3->setText(QString());
        IdentityLabel3->setText(QString());
        SkipTurnBtn->setText(QCoreApplication::translate("GameWidget", "\344\270\215\345\207\272", nullptr));
        CallLandlordBtn->setText(QCoreApplication::translate("GameWidget", "\345\217\253\345\234\260\344\270\273", nullptr));
        SkipCallLandlordBtn->setText(QCoreApplication::translate("GameWidget", "\344\270\215\345\217\253", nullptr));
        BidForLandlordBtn->setText(QCoreApplication::translate("GameWidget", "\346\212\242\345\234\260\344\270\273", nullptr));
        SkipLandlordBidBtn->setText(QCoreApplication::translate("GameWidget", "\344\270\215\346\212\242", nullptr));
        DoubleBtn->setText(QCoreApplication::translate("GameWidget", "\345\212\240\345\200\215", nullptr));
        UnDoubleBtn->setText(QCoreApplication::translate("GameWidget", "\344\270\215\345\212\240\345\200\215", nullptr));
        RoomId->setText(QCoreApplication::translate("GameWidget", "123789", nullptr));
        MSGLabel1->setText(QCoreApplication::translate("GameWidget", "\345\212\240\345\200\215", nullptr));
        MSGLabel2->setText(QCoreApplication::translate("GameWidget", "\345\212\240\345\200\215", nullptr));
        MSGLabel3->setText(QCoreApplication::translate("GameWidget", "\345\212\240\345\200\215", nullptr));
        ReadyBtn->setText(QCoreApplication::translate("GameWidget", "\345\207\206\345\244\207", nullptr));
        ReadyLabel3->setText(QCoreApplication::translate("GameWidget", "TextLabel", nullptr));
        ReadyLabel1->setText(QCoreApplication::translate("GameWidget", "TextLabel", nullptr));
        ReadyLabel2->setText(QCoreApplication::translate("GameWidget", "TextLabel", nullptr));
        UnReadyBtn->setText(QCoreApplication::translate("GameWidget", "\345\217\226\346\266\210\345\207\206\345\244\207", nullptr));
        Name1->setText(QCoreApplication::translate("GameWidget", "Name1", nullptr));
        Name2->setText(QCoreApplication::translate("GameWidget", "Name2", nullptr));
        Name3->setText(QCoreApplication::translate("GameWidget", "Name3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWidget: public Ui_GameWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWIDGET_H
