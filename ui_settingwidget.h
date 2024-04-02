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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingWidget
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QWidget *SettingWidget)
    {
        if (SettingWidget->objectName().isEmpty())
            SettingWidget->setObjectName("SettingWidget");
        SettingWidget->resize(1102, 745);
        QFont font;
        font.setFamilies({QString::fromUtf8("Ink Free")});
        font.setPointSize(28);
        SettingWidget->setFont(font);
        SettingWidget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(153, 255, 102, 255), stop:1 rgba(255, 255, 255, 255));"));
        pushButton = new QPushButton(SettingWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 60, 201, 91));
        pushButton->setStyleSheet(QString::fromUtf8(" background-color: transparent; border-radius: 45px;\n"
"border:1px solid;\n"
"font: 36pt \"\345\255\227\345\277\203\345\235\212\345\260\217\345\221\200\345\260\217\345\270\203\344\270\201\344\275\223\";\n"
"\n"
""));
        pushButton_2 = new QPushButton(SettingWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(40, 220, 201, 91));
        pushButton_2->setStyleSheet(QString::fromUtf8(" background-color: transparent;  border-radius: 45px;\n"
"border:1px solid;\n"
"font: 36pt \"\345\255\227\345\277\203\345\235\212\345\260\217\345\221\200\345\260\217\345\270\203\344\270\201\344\275\223\";\n"
"\n"
""));
        pushButton_3 = new QPushButton(SettingWidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(40, 370, 201, 91));
        pushButton_3->setStyleSheet(QString::fromUtf8(" background-color: transparent;  border-radius: 45px;\n"
"border:1px solid;\n"
"font: 36pt \"\345\255\227\345\277\203\345\235\212\345\260\217\345\221\200\345\260\217\345\270\203\344\270\201\344\275\223\";\n"
""));
        pushButton_4 = new QPushButton(SettingWidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(50, 700, 171, 31));
        pushButton_4->setStyleSheet(QString::fromUtf8(" background-color: transparent;\n"
"border:0px solid;\n"
"color: rgb(85, 170, 255);\n"
"font: 9pt \"Microsoft YaHei UI\";\n"
"text-decoration: underline;"));

        retranslateUi(SettingWidget);

        QMetaObject::connectSlotsByName(SettingWidget);
    } // setupUi

    void retranslateUi(QWidget *SettingWidget)
    {
        SettingWidget->setWindowTitle(QCoreApplication::translate("SettingWidget", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("SettingWidget", "\345\237\272\347\241\200", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SettingWidget", "\347\224\273\351\235\242", nullptr));
        pushButton_3->setText(QCoreApplication::translate("SettingWidget", "\351\237\263\346\225\210", nullptr));
        pushButton_4->setText(QCoreApplication::translate("SettingWidget", "\345\274\200\345\217\221\344\272\272\345\221\230\345\220\215\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingWidget: public Ui_SettingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWIDGET_H
