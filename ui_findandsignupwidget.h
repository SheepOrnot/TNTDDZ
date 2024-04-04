/********************************************************************************
** Form generated from reading UI file 'findandsignupwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDANDSIGNUPWIDGET_H
#define UI_FINDANDSIGNUPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindAndSignUpWidget
{
public:
    QLineEdit *MailLineEdit;
    QLineEdit *KeyLineEdit;
    QPushButton *SendKeyPushButton;
    QPushButton *EnterKeyPushButton;
    QLineEdit *UsernameLineEdit;
    QLineEdit *Password1LineEdit;
    QLineEdit *Password2LineEdit;
    QPushButton *EnterPushButton;

    void setupUi(QWidget *FindAndSignUpWidget)
    {
        if (FindAndSignUpWidget->objectName().isEmpty())
            FindAndSignUpWidget->setObjectName("FindAndSignUpWidget");
        FindAndSignUpWidget->resize(600, 900);
        FindAndSignUpWidget->setStyleSheet(QString::fromUtf8("#FindAndSignUpWidget{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 189, 137, 236), stop:1 rgba(255, 255, 255, 255));}"));
        MailLineEdit = new QLineEdit(FindAndSignUpWidget);
        MailLineEdit->setObjectName("MailLineEdit");
        MailLineEdit->setGeometry(QRect(150, 70, 300, 70));
        MailLineEdit->setStyleSheet(QString::fromUtf8("background-color: transparent; border: 1px solid black;"));
        MailLineEdit->setInputMethodHints(Qt::ImhNone);
        KeyLineEdit = new QLineEdit(FindAndSignUpWidget);
        KeyLineEdit->setObjectName("KeyLineEdit");
        KeyLineEdit->setEnabled(true);
        KeyLineEdit->setGeometry(QRect(150, 200, 300, 70));
        KeyLineEdit->setStyleSheet(QString::fromUtf8("background-color: transparent; border: 1px solid black;"));
        SendKeyPushButton = new QPushButton(FindAndSignUpWidget);
        SendKeyPushButton->setObjectName("SendKeyPushButton");
        SendKeyPushButton->setGeometry(QRect(460, 80, 81, 41));
        EnterKeyPushButton = new QPushButton(FindAndSignUpWidget);
        EnterKeyPushButton->setObjectName("EnterKeyPushButton");
        EnterKeyPushButton->setGeometry(QRect(180, 300, 240, 60));
        EnterKeyPushButton->setStyleSheet(QString::fromUtf8(""));
        UsernameLineEdit = new QLineEdit(FindAndSignUpWidget);
        UsernameLineEdit->setObjectName("UsernameLineEdit");
        UsernameLineEdit->setEnabled(true);
        UsernameLineEdit->setGeometry(QRect(150, 330, 300, 70));
        UsernameLineEdit->setStyleSheet(QString::fromUtf8("background-color: transparent; border: 1px solid black;"));
        Password1LineEdit = new QLineEdit(FindAndSignUpWidget);
        Password1LineEdit->setObjectName("Password1LineEdit");
        Password1LineEdit->setEnabled(true);
        Password1LineEdit->setGeometry(QRect(150, 460, 300, 70));
        Password1LineEdit->setStyleSheet(QString::fromUtf8("background-color: transparent; border: 1px solid black;"));
        Password2LineEdit = new QLineEdit(FindAndSignUpWidget);
        Password2LineEdit->setObjectName("Password2LineEdit");
        Password2LineEdit->setEnabled(true);
        Password2LineEdit->setGeometry(QRect(150, 590, 300, 70));
        Password2LineEdit->setStyleSheet(QString::fromUtf8("background-color: transparent; border: 1px solid black;"));
        EnterPushButton = new QPushButton(FindAndSignUpWidget);
        EnterPushButton->setObjectName("EnterPushButton");
        EnterPushButton->setGeometry(QRect(180, 690, 240, 60));
        EnterPushButton->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(FindAndSignUpWidget);

        QMetaObject::connectSlotsByName(FindAndSignUpWidget);
    } // setupUi

    void retranslateUi(QWidget *FindAndSignUpWidget)
    {
        FindAndSignUpWidget->setWindowTitle(QCoreApplication::translate("FindAndSignUpWidget", "Form", nullptr));
        SendKeyPushButton->setText(QCoreApplication::translate("FindAndSignUpWidget", "\345\217\221\351\200\201\351\252\214\350\257\201\347\240\201", nullptr));
        EnterKeyPushButton->setText(QCoreApplication::translate("FindAndSignUpWidget", "\347\241\256\345\256\232", nullptr));
        EnterPushButton->setText(QCoreApplication::translate("FindAndSignUpWidget", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindAndSignUpWidget: public Ui_FindAndSignUpWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDANDSIGNUPWIDGET_H
