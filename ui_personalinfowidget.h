/********************************************************************************
** Form generated from reading UI file 'personalinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSONALINFOWIDGET_H
#define UI_PERSONALINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PersonalInfoWidget
{
public:
    QLabel *NameLabel;
    QLabel *UIDLabel;
    QLabel *EmailLabel;
    QLabel *ProfileLabel;
    QComboBox *ChooseProfile;
    QLabel *Rate;
    QLabel *KD;
    QLabel *Matches;
    QPushButton *ExitBtn;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QWidget *PersonalInfoWidget)
    {
        if (PersonalInfoWidget->objectName().isEmpty())
            PersonalInfoWidget->setObjectName("PersonalInfoWidget");
        PersonalInfoWidget->resize(1152, 756);
        NameLabel = new QLabel(PersonalInfoWidget);
        NameLabel->setObjectName("NameLabel");
        NameLabel->setGeometry(QRect(50, 50, 261, 61));
        UIDLabel = new QLabel(PersonalInfoWidget);
        UIDLabel->setObjectName("UIDLabel");
        UIDLabel->setGeometry(QRect(50, 120, 260, 60));
        EmailLabel = new QLabel(PersonalInfoWidget);
        EmailLabel->setObjectName("EmailLabel");
        EmailLabel->setGeometry(QRect(50, 190, 260, 60));
        ProfileLabel = new QLabel(PersonalInfoWidget);
        ProfileLabel->setObjectName("ProfileLabel");
        ProfileLabel->setGeometry(QRect(710, 70, 180, 180));
        ChooseProfile = new QComboBox(PersonalInfoWidget);
        ChooseProfile->setObjectName("ChooseProfile");
        ChooseProfile->setGeometry(QRect(710, 270, 180, 35));
        Rate = new QLabel(PersonalInfoWidget);
        Rate->setObjectName("Rate");
        Rate->setGeometry(QRect(710, 520, 260, 60));
        KD = new QLabel(PersonalInfoWidget);
        KD->setObjectName("KD");
        KD->setGeometry(QRect(710, 450, 260, 60));
        Matches = new QLabel(PersonalInfoWidget);
        Matches->setObjectName("Matches");
        Matches->setGeometry(QRect(710, 380, 261, 61));
        ExitBtn = new QPushButton(PersonalInfoWidget);
        ExitBtn->setObjectName("ExitBtn");
        ExitBtn->setGeometry(QRect(1080, 10, 61, 61));
        scrollArea = new QScrollArea(PersonalInfoWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(40, 280, 501, 381));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 499, 379));
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(PersonalInfoWidget);

        QMetaObject::connectSlotsByName(PersonalInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *PersonalInfoWidget)
    {
        PersonalInfoWidget->setWindowTitle(QCoreApplication::translate("PersonalInfoWidget", "Form", nullptr));
        NameLabel->setText(QCoreApplication::translate("PersonalInfoWidget", "\346\230\265\347\247\260\357\274\232\345\206\267\351\224\213", nullptr));
        UIDLabel->setText(QCoreApplication::translate("PersonalInfoWidget", "UID \357\274\2320000000001", nullptr));
        EmailLabel->setText(QCoreApplication::translate("PersonalInfoWidget", "\351\202\256\347\256\261\357\274\232123456789@qq.com", nullptr));
        ProfileLabel->setText(QCoreApplication::translate("PersonalInfoWidget", "TextLabel", nullptr));
        Rate->setText(QCoreApplication::translate("PersonalInfoWidget", "\350\203\234\347\216\207         \357\274\23256%", nullptr));
        KD->setText(QCoreApplication::translate("PersonalInfoWidget", "\350\203\234\345\210\251/\345\244\261\350\264\245\357\274\2325000/4000", nullptr));
        Matches->setText(QCoreApplication::translate("PersonalInfoWidget", "\346\200\273\345\234\272\346\254\241     \357\274\2329000", nullptr));
        ExitBtn->setText(QCoreApplication::translate("PersonalInfoWidget", "exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PersonalInfoWidget: public Ui_PersonalInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONALINFOWIDGET_H
