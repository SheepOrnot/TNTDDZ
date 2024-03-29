/********************************************************************************
** Form generated from reading UI file 'lobbywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOBBYWIDGET_H
#define UI_LOBBYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LobbyWidget
{
public:
    QLabel *ProfileLabel;
    QLabel *UsernameLabel;
    QLabel *UidLabel;
    QPushButton *SettingBtn;
    QPushButton *RuleBtn;
    QLineEdit *BeanEdit;
    QPushButton *AddBeanBtn;
    QLabel *BeanLabel;
    QLineEdit *DiamondEdit;
    QPushButton *AddDiamondBtn;
    QLabel *DiamondLabel;
    QLabel *RollLabel;
    QPushButton *ClassicModeBtn;
    QPushButton *ExitGameBtn;
    QLabel *GifLabel;
    QPushButton *JoinRoomBtn;

    void setupUi(QWidget *LobbyWidget)
    {
        if (LobbyWidget->objectName().isEmpty())
            LobbyWidget->setObjectName(QString::fromUtf8("LobbyWidget"));
        LobbyWidget->resize(1920, 1080);
        ProfileLabel = new QLabel(LobbyWidget);
        ProfileLabel->setObjectName(QString::fromUtf8("ProfileLabel"));
        ProfileLabel->setGeometry(QRect(40, 20, 130, 130));
        ProfileLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);"));
        UsernameLabel = new QLabel(LobbyWidget);
        UsernameLabel->setObjectName(QString::fromUtf8("UsernameLabel"));
        UsernameLabel->setGeometry(QRect(210, 30, 181, 31));
        UsernameLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);\n"
"font: 9pt \"\345\215\216\346\226\207\346\226\260\351\255\217\";"));
        UidLabel = new QLabel(LobbyWidget);
        UidLabel->setObjectName(QString::fromUtf8("UidLabel"));
        UidLabel->setGeometry(QRect(210, 90, 181, 31));
        UidLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        SettingBtn = new QPushButton(LobbyWidget);
        SettingBtn->setObjectName(QString::fromUtf8("SettingBtn"));
        SettingBtn->setGeometry(QRect(1850, 20, 51, 51));
        RuleBtn = new QPushButton(LobbyWidget);
        RuleBtn->setObjectName(QString::fromUtf8("RuleBtn"));
        RuleBtn->setGeometry(QRect(1780, 20, 51, 51));
        BeanEdit = new QLineEdit(LobbyWidget);
        BeanEdit->setObjectName(QString::fromUtf8("BeanEdit"));
        BeanEdit->setGeometry(QRect(830, 20, 171, 51));
        BeanEdit->setStyleSheet(QString::fromUtf8(""));
        AddBeanBtn = new QPushButton(LobbyWidget);
        AddBeanBtn->setObjectName(QString::fromUtf8("AddBeanBtn"));
        AddBeanBtn->setGeometry(QRect(1010, 20, 51, 51));
        BeanLabel = new QLabel(LobbyWidget);
        BeanLabel->setObjectName(QString::fromUtf8("BeanLabel"));
        BeanLabel->setGeometry(QRect(780, 20, 41, 41));
        DiamondEdit = new QLineEdit(LobbyWidget);
        DiamondEdit->setObjectName(QString::fromUtf8("DiamondEdit"));
        DiamondEdit->setGeometry(QRect(1160, 20, 171, 51));
        AddDiamondBtn = new QPushButton(LobbyWidget);
        AddDiamondBtn->setObjectName(QString::fromUtf8("AddDiamondBtn"));
        AddDiamondBtn->setGeometry(QRect(1340, 20, 51, 51));
        DiamondLabel = new QLabel(LobbyWidget);
        DiamondLabel->setObjectName(QString::fromUtf8("DiamondLabel"));
        DiamondLabel->setGeometry(QRect(1110, 20, 41, 41));
        RollLabel = new QLabel(LobbyWidget);
        RollLabel->setObjectName(QString::fromUtf8("RollLabel"));
        RollLabel->setGeometry(QRect(1160, 180, 631, 371));
        ClassicModeBtn = new QPushButton(LobbyWidget);
        ClassicModeBtn->setObjectName(QString::fromUtf8("ClassicModeBtn"));
        ClassicModeBtn->setGeometry(QRect(1310, 640, 311, 91));
        ExitGameBtn = new QPushButton(LobbyWidget);
        ExitGameBtn->setObjectName(QString::fromUtf8("ExitGameBtn"));
        ExitGameBtn->setGeometry(QRect(1310, 760, 311, 91));
        GifLabel = new QLabel(LobbyWidget);
        GifLabel->setObjectName(QString::fromUtf8("GifLabel"));
        GifLabel->setGeometry(QRect(110, 210, 461, 761));
        JoinRoomBtn = new QPushButton(LobbyWidget);
        JoinRoomBtn->setObjectName(QString::fromUtf8("JoinRoomBtn"));
        JoinRoomBtn->setGeometry(QRect(1310, 880, 311, 91));

        retranslateUi(LobbyWidget);

        QMetaObject::connectSlotsByName(LobbyWidget);
    } // setupUi

    void retranslateUi(QWidget *LobbyWidget)
    {
        LobbyWidget->setWindowTitle(QCoreApplication::translate("LobbyWidget", "Form", nullptr));
        ProfileLabel->setText(QString());
        UsernameLabel->setText(QCoreApplication::translate("LobbyWidget", "Username", nullptr));
        UidLabel->setText(QCoreApplication::translate("LobbyWidget", "Uid", nullptr));
        SettingBtn->setText(QString());
        RuleBtn->setText(QString());
        BeanEdit->setText(QString());
        AddBeanBtn->setText(QString());
        BeanLabel->setText(QCoreApplication::translate("LobbyWidget", "beanimage", nullptr));
        DiamondEdit->setText(QString());
        AddDiamondBtn->setText(QString());
        DiamondLabel->setText(QCoreApplication::translate("LobbyWidget", "diamondimage", nullptr));
        RollLabel->setText(QString());
        ClassicModeBtn->setText(QCoreApplication::translate("LobbyWidget", "\347\273\217\345\205\270\346\250\241\345\274\217", nullptr));
        ExitGameBtn->setText(QCoreApplication::translate("LobbyWidget", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        GifLabel->setText(QCoreApplication::translate("LobbyWidget", "giflabel", nullptr));
        JoinRoomBtn->setText(QCoreApplication::translate("LobbyWidget", "\345\212\240\345\205\245\346\210\277\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LobbyWidget: public Ui_LobbyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOBBYWIDGET_H
