/********************************************************************************
** Form generated from reading UI file 'gamewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWIDGET_H
#define UI_GAMEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
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

    void setupUi(QWidget *GameWidget)
    {
        if (GameWidget->objectName().isEmpty())
            GameWidget->setObjectName(QString::fromUtf8("GameWidget"));
        GameWidget->resize(1920, 1080);
        FinalCard1 = new QLabel(GameWidget);
        FinalCard1->setObjectName(QString::fromUtf8("FinalCard1"));
        FinalCard1->setGeometry(QRect(740, 20, 81, 111));
        FinalCard1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        FinalCard2 = new QLabel(GameWidget);
        FinalCard2->setObjectName(QString::fromUtf8("FinalCard2"));
        FinalCard2->setGeometry(QRect(850, 20, 81, 111));
        FinalCard2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        FinalCard3 = new QLabel(GameWidget);
        FinalCard3->setObjectName(QString::fromUtf8("FinalCard3"));
        FinalCard3->setGeometry(QRect(950, 20, 81, 111));
        FinalCard3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        MultiplierLabel = new QLabel(GameWidget);
        MultiplierLabel->setObjectName(QString::fromUtf8("MultiplierLabel"));
        MultiplierLabel->setGeometry(QRect(1040, 50, 81, 81));
        RuleBtn = new QPushButton(GameWidget);
        RuleBtn->setObjectName(QString::fromUtf8("RuleBtn"));
        RuleBtn->setGeometry(QRect(1730, 20, 61, 61));
        SettingBtn = new QPushButton(GameWidget);
        SettingBtn->setObjectName(QString::fromUtf8("SettingBtn"));
        SettingBtn->setGeometry(QRect(1810, 20, 61, 61));
        ProfileLabel1 = new QLabel(GameWidget);
        ProfileLabel1->setObjectName(QString::fromUtf8("ProfileLabel1"));
        ProfileLabel1->setGeometry(QRect(50, 270, 121, 131));
        ProfileLabel1->setStyleSheet(QString::fromUtf8(""));
        ProfileLabel2 = new QLabel(GameWidget);
        ProfileLabel2->setObjectName(QString::fromUtf8("ProfileLabel2"));
        ProfileLabel2->setGeometry(QRect(1740, 280, 121, 131));
        ProfileLabel2->setStyleSheet(QString::fromUtf8(""));
        BeansLineEdit1 = new QLineEdit(GameWidget);
        BeansLineEdit1->setObjectName(QString::fromUtf8("BeansLineEdit1"));
        BeansLineEdit1->setGeometry(QRect(50, 420, 121, 31));
        BeansLineEdit2 = new QLineEdit(GameWidget);
        BeansLineEdit2->setObjectName(QString::fromUtf8("BeansLineEdit2"));
        BeansLineEdit2->setGeometry(QRect(1740, 430, 121, 31));
        ClockNum = new QLabel(GameWidget);
        ClockNum->setObjectName(QString::fromUtf8("ClockNum"));
        ClockNum->setGeometry(QRect(1550, 250, 20, 21));
        ClockNum->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 127);"));
        ClockImageLabel = new QLabel(GameWidget);
        ClockImageLabel->setObjectName(QString::fromUtf8("ClockImageLabel"));
        ClockImageLabel->setGeometry(QRect(1540, 240, 41, 41));
        ClockImageLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        DoubleLabel1 = new QLabel(GameWidget);
        DoubleLabel1->setObjectName(QString::fromUtf8("DoubleLabel1"));
        DoubleLabel1->setGeometry(QRect(120, 460, 51, 19));
        DoubleLabel2 = new QLabel(GameWidget);
        DoubleLabel2->setObjectName(QString::fromUtf8("DoubleLabel2"));
        DoubleLabel2->setGeometry(QRect(1740, 470, 51, 19));
        IdentityLabel1 = new QLabel(GameWidget);
        IdentityLabel1->setObjectName(QString::fromUtf8("IdentityLabel1"));
        IdentityLabel1->setGeometry(QRect(90, 220, 41, 41));
        IdentityLabel1->setStyleSheet(QString::fromUtf8(""));
        IdentityLabel2 = new QLabel(GameWidget);
        IdentityLabel2->setObjectName(QString::fromUtf8("IdentityLabel2"));
        IdentityLabel2->setGeometry(QRect(1780, 230, 41, 41));
        IdentityLabel2->setStyleSheet(QString::fromUtf8(""));
        PlayCardBtn = new QPushButton(GameWidget);
        PlayCardBtn->setObjectName(QString::fromUtf8("PlayCardBtn"));
        PlayCardBtn->setGeometry(QRect(630, 770, 161, 51));
        ProfileLabel3 = new QLabel(GameWidget);
        ProfileLabel3->setObjectName(QString::fromUtf8("ProfileLabel3"));
        ProfileLabel3->setGeometry(QRect(120, 890, 121, 131));
        ProfileLabel3->setStyleSheet(QString::fromUtf8(""));
        BeansLineEdit3 = new QLineEdit(GameWidget);
        BeansLineEdit3->setObjectName(QString::fromUtf8("BeansLineEdit3"));
        BeansLineEdit3->setGeometry(QRect(120, 1030, 121, 31));
        DoubleLabel3 = new QLabel(GameWidget);
        DoubleLabel3->setObjectName(QString::fromUtf8("DoubleLabel3"));
        DoubleLabel3->setGeometry(QRect(260, 1040, 51, 19));
        IdentityLabel3 = new QLabel(GameWidget);
        IdentityLabel3->setObjectName(QString::fromUtf8("IdentityLabel3"));
        IdentityLabel3->setGeometry(QRect(160, 840, 41, 41));
        IdentityLabel3->setStyleSheet(QString::fromUtf8(""));
        ChatComboBox = new QComboBox(GameWidget);
        ChatComboBox->setObjectName(QString::fromUtf8("ChatComboBox"));
        ChatComboBox->setGeometry(QRect(1700, 1010, 201, 31));
        SkipTurnBtn = new QPushButton(GameWidget);
        SkipTurnBtn->setObjectName(QString::fromUtf8("SkipTurnBtn"));
        SkipTurnBtn->setGeometry(QRect(1000, 770, 161, 51));
        CallLandlordBtn = new QPushButton(GameWidget);
        CallLandlordBtn->setObjectName(QString::fromUtf8("CallLandlordBtn"));
        CallLandlordBtn->setGeometry(QRect(630, 750, 161, 51));
        SkipCallLandlordBtn = new QPushButton(GameWidget);
        SkipCallLandlordBtn->setObjectName(QString::fromUtf8("SkipCallLandlordBtn"));
        SkipCallLandlordBtn->setGeometry(QRect(1000, 750, 161, 51));
        BidForLandlordBtn = new QPushButton(GameWidget);
        BidForLandlordBtn->setObjectName(QString::fromUtf8("BidForLandlordBtn"));
        BidForLandlordBtn->setGeometry(QRect(630, 730, 161, 51));
        SkipLandlordBidBtn = new QPushButton(GameWidget);
        SkipLandlordBidBtn->setObjectName(QString::fromUtf8("SkipLandlordBidBtn"));
        SkipLandlordBidBtn->setGeometry(QRect(1000, 730, 161, 51));
        DoubleBtn = new QPushButton(GameWidget);
        DoubleBtn->setObjectName(QString::fromUtf8("DoubleBtn"));
        DoubleBtn->setGeometry(QRect(630, 710, 161, 51));
        UnDoubleBtn = new QPushButton(GameWidget);
        UnDoubleBtn->setObjectName(QString::fromUtf8("UnDoubleBtn"));
        UnDoubleBtn->setGeometry(QRect(1000, 710, 161, 51));
        RoomId = new QLabel(GameWidget);
        RoomId->setObjectName(QString::fromUtf8("RoomId"));
        RoomId->setGeometry(QRect(1570, 30, 131, 41));
        RoomId->setStyleSheet(QString::fromUtf8("font: 600 20pt \"Sitka Subheading Semibold\";\n"
"border-color: rgb(0, 0, 0);\n"
"border:1px solid;"));
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
        DoubleLabel1->setText(QCoreApplication::translate("GameWidget", "\344\270\215\345\212\240\345\200\215", nullptr));
        DoubleLabel2->setText(QCoreApplication::translate("GameWidget", "\345\212\240\345\200\215", nullptr));
        IdentityLabel1->setText(QCoreApplication::translate("GameWidget", "Icon", nullptr));
        IdentityLabel2->setText(QCoreApplication::translate("GameWidget", "Icon2", nullptr));
        PlayCardBtn->setText(QCoreApplication::translate("GameWidget", "\345\207\272\347\211\214", nullptr));
        ProfileLabel3->setText(QCoreApplication::translate("GameWidget", "Profile3", nullptr));
        BeansLineEdit3->setText(QString());
        DoubleLabel3->setText(QCoreApplication::translate("GameWidget", "\344\270\215\345\212\240\345\200\215", nullptr));
        IdentityLabel3->setText(QCoreApplication::translate("GameWidget", "Icon", nullptr));
        SkipTurnBtn->setText(QCoreApplication::translate("GameWidget", "\344\270\215\345\207\272", nullptr));
        CallLandlordBtn->setText(QCoreApplication::translate("GameWidget", "\345\217\253\345\234\260\344\270\273", nullptr));
        SkipCallLandlordBtn->setText(QCoreApplication::translate("GameWidget", "\344\270\215\345\217\253", nullptr));
        BidForLandlordBtn->setText(QCoreApplication::translate("GameWidget", "\346\212\242\345\234\260\344\270\273", nullptr));
        SkipLandlordBidBtn->setText(QCoreApplication::translate("GameWidget", "\344\270\215\346\212\242", nullptr));
        DoubleBtn->setText(QCoreApplication::translate("GameWidget", "\345\212\240\345\200\215", nullptr));
        UnDoubleBtn->setText(QCoreApplication::translate("GameWidget", "\344\270\215\345\212\240\345\200\215", nullptr));
        RoomId->setText(QCoreApplication::translate("GameWidget", "123789", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWidget: public Ui_GameWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWIDGET_H
