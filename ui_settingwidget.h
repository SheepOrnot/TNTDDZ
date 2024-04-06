/********************************************************************************
** Form generated from reading UI file 'settingwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGWIDGET_H
#define UI_SETTINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingWidget
{
public:
    QPushButton *BasicBtn;
    QPushButton *FrameBtn;
    QPushButton *SoundEffectBtn;
    QPushButton *NameListBtn;
    QLabel *CardFront;
    QLabel *CardBack;
    QComboBox *CardStyleComboBox;
    QLabel *CardStyleWord;
    QComboBox *ResolutionComboBox;
    QLabel *ResolutionWord;
    QSlider *BGMVolume;
    QSlider *EffectVolume;
    QLabel *GameBGMWord;
    QLabel *GameEffectWord;
    QLabel *LobbyBGMWord;
    QCheckBox *LobbyBGMCheck;
    QPushButton *ApplyBtn;
    QPushButton *CancelBtn;
    QCheckBox *GameBGMCheck;
    QCheckBox *GameEffectCheck;

    void setupUi(QWidget *SettingWidget)
    {
        if (SettingWidget->objectName().isEmpty())
            SettingWidget->setObjectName("SettingWidget");
        SettingWidget->resize(1102, 745);
        QFont font;
        font.setFamilies({QString::fromUtf8("Ink Free")});
        font.setPointSize(9);
        SettingWidget->setFont(font);
        SettingWidget->setStyleSheet(QString::fromUtf8(""));
        BasicBtn = new QPushButton(SettingWidget);
        BasicBtn->setObjectName("BasicBtn");
        BasicBtn->setGeometry(QRect(40, 60, 201, 91));
        BasicBtn->setStyleSheet(QString::fromUtf8(" background-color: transparent; border-radius: 45px;\n"
"border:1px solid;\n"
"font: 36pt \"\345\255\227\345\277\203\345\235\212\345\260\217\345\221\200\345\260\217\345\270\203\344\270\201\344\275\223\";\n"
"\n"
""));
        FrameBtn = new QPushButton(SettingWidget);
        FrameBtn->setObjectName("FrameBtn");
        FrameBtn->setGeometry(QRect(40, 220, 201, 91));
        FrameBtn->setStyleSheet(QString::fromUtf8(" background-color: transparent;  border-radius: 45px;\n"
"border:1px solid;\n"
"font: 36pt \"\345\255\227\345\277\203\345\235\212\345\260\217\345\221\200\345\260\217\345\270\203\344\270\201\344\275\223\";\n"
"\n"
""));
        SoundEffectBtn = new QPushButton(SettingWidget);
        SoundEffectBtn->setObjectName("SoundEffectBtn");
        SoundEffectBtn->setGeometry(QRect(40, 370, 201, 91));
        SoundEffectBtn->setStyleSheet(QString::fromUtf8(" background-color: transparent;  border-radius: 45px;\n"
"border:1px solid;\n"
"font: 36pt \"\345\255\227\345\277\203\345\235\212\345\260\217\345\221\200\345\260\217\345\270\203\344\270\201\344\275\223\";\n"
""));
        NameListBtn = new QPushButton(SettingWidget);
        NameListBtn->setObjectName("NameListBtn");
        NameListBtn->setGeometry(QRect(50, 700, 171, 31));
        NameListBtn->setStyleSheet(QString::fromUtf8(" background-color: transparent;\n"
"border:0px solid;\n"
"color: rgb(85, 170, 255);\n"
"font: 9pt \"Microsoft YaHei UI\";\n"
"text-decoration: underline;"));
        CardFront = new QLabel(SettingWidget);
        CardFront->setObjectName("CardFront");
        CardFront->setGeometry(QRect(520, 240, 111, 151));
        CardBack = new QLabel(SettingWidget);
        CardBack->setObjectName("CardBack");
        CardBack->setGeometry(QRect(740, 240, 111, 151));
        CardStyleComboBox = new QComboBox(SettingWidget);
        CardStyleComboBox->addItem(QString());
        CardStyleComboBox->addItem(QString());
        CardStyleComboBox->setObjectName("CardStyleComboBox");
        CardStyleComboBox->setGeometry(QRect(620, 140, 231, 31));
        CardStyleWord = new QLabel(SettingWidget);
        CardStyleWord->setObjectName("CardStyleWord");
        CardStyleWord->setGeometry(QRect(530, 140, 81, 31));
        CardStyleWord->setStyleSheet(QString::fromUtf8(""));
        ResolutionComboBox = new QComboBox(SettingWidget);
        ResolutionComboBox->setObjectName("ResolutionComboBox");
        ResolutionComboBox->setGeometry(QRect(620, 180, 231, 31));
        ResolutionWord = new QLabel(SettingWidget);
        ResolutionWord->setObjectName("ResolutionWord");
        ResolutionWord->setGeometry(QRect(530, 180, 81, 31));
        ResolutionWord->setStyleSheet(QString::fromUtf8(""));
        BGMVolume = new QSlider(SettingWidget);
        BGMVolume->setObjectName("BGMVolume");
        BGMVolume->setGeometry(QRect(550, 420, 311, 22));
        BGMVolume->setOrientation(Qt::Horizontal);
        EffectVolume = new QSlider(SettingWidget);
        EffectVolume->setObjectName("EffectVolume");
        EffectVolume->setGeometry(QRect(550, 460, 311, 22));
        EffectVolume->setOrientation(Qt::Horizontal);
        GameBGMWord = new QLabel(SettingWidget);
        GameBGMWord->setObjectName("GameBGMWord");
        GameBGMWord->setGeometry(QRect(430, 420, 91, 31));
        GameEffectWord = new QLabel(SettingWidget);
        GameEffectWord->setObjectName("GameEffectWord");
        GameEffectWord->setGeometry(QRect(430, 450, 91, 31));
        LobbyBGMWord = new QLabel(SettingWidget);
        LobbyBGMWord->setObjectName("LobbyBGMWord");
        LobbyBGMWord->setGeometry(QRect(430, 480, 91, 31));
        LobbyBGMCheck = new QCheckBox(SettingWidget);
        LobbyBGMCheck->setObjectName("LobbyBGMCheck");
        LobbyBGMCheck->setGeometry(QRect(530, 490, 16, 23));
        ApplyBtn = new QPushButton(SettingWidget);
        ApplyBtn->setObjectName("ApplyBtn");
        ApplyBtn->setGeometry(QRect(910, 660, 141, 71));
        ApplyBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 255);"));
        CancelBtn = new QPushButton(SettingWidget);
        CancelBtn->setObjectName("CancelBtn");
        CancelBtn->setGeometry(QRect(750, 660, 141, 71));
        CancelBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        GameBGMCheck = new QCheckBox(SettingWidget);
        GameBGMCheck->setObjectName("GameBGMCheck");
        GameBGMCheck->setGeometry(QRect(530, 420, 16, 23));
        GameEffectCheck = new QCheckBox(SettingWidget);
        GameEffectCheck->setObjectName("GameEffectCheck");
        GameEffectCheck->setGeometry(QRect(530, 460, 16, 23));

        retranslateUi(SettingWidget);

        QMetaObject::connectSlotsByName(SettingWidget);
    } // setupUi

    void retranslateUi(QWidget *SettingWidget)
    {
        SettingWidget->setWindowTitle(QCoreApplication::translate("SettingWidget", "Form", nullptr));
        BasicBtn->setText(QCoreApplication::translate("SettingWidget", "\345\237\272\347\241\200", nullptr));
        FrameBtn->setText(QCoreApplication::translate("SettingWidget", "\347\224\273\351\235\242", nullptr));
        SoundEffectBtn->setText(QCoreApplication::translate("SettingWidget", "\351\237\263\346\225\210", nullptr));
        NameListBtn->setText(QCoreApplication::translate("SettingWidget", "\345\274\200\345\217\221\344\272\272\345\221\230\345\220\215\345\215\225", nullptr));
        CardFront->setText(QCoreApplication::translate("SettingWidget", "TextLabel", nullptr));
        CardBack->setText(QCoreApplication::translate("SettingWidget", "TextLabel", nullptr));
        CardStyleComboBox->setItemText(0, QCoreApplication::translate("SettingWidget", "\347\273\217\345\205\270\346\254\276", nullptr));
        CardStyleComboBox->setItemText(1, QCoreApplication::translate("SettingWidget", "\347\273\217\345\205\270\344\270\255\347\232\204\347\273\217\345\205\270\346\254\276", nullptr));

        CardStyleWord->setText(QCoreApplication::translate("SettingWidget", "\347\211\214\347\273\204", nullptr));
        ResolutionWord->setText(QCoreApplication::translate("SettingWidget", "\345\210\206\350\276\250\347\216\207", nullptr));
        GameBGMWord->setText(QCoreApplication::translate("SettingWidget", "\346\270\270\346\210\217\350\203\214\346\231\257\351\237\263\344\271\220", nullptr));
        GameEffectWord->setText(QCoreApplication::translate("SettingWidget", "\346\270\270\346\210\217\351\237\263\346\225\210", nullptr));
        LobbyBGMWord->setText(QCoreApplication::translate("SettingWidget", "\345\244\247\345\216\205\350\203\214\346\231\257\351\237\263\344\271\220", nullptr));
        LobbyBGMCheck->setText(QString());
        ApplyBtn->setText(QCoreApplication::translate("SettingWidget", "\345\272\224\347\224\250", nullptr));
        CancelBtn->setText(QCoreApplication::translate("SettingWidget", "\345\217\226\346\266\210", nullptr));
        GameBGMCheck->setText(QString());
        GameEffectCheck->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SettingWidget: public Ui_SettingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWIDGET_H
