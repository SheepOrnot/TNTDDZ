/********************************************************************************
** Form generated from reading UI file 'personalinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSONALINFOWIDGET_H
#define UI_PERSONALINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PersonalInfoWidget
{
public:

    void setupUi(QWidget *PersonalInfoWidget)
    {
        if (PersonalInfoWidget->objectName().isEmpty())
            PersonalInfoWidget->setObjectName(QString::fromUtf8("PersonalInfoWidget"));
        PersonalInfoWidget->resize(1383, 915);

        retranslateUi(PersonalInfoWidget);

        QMetaObject::connectSlotsByName(PersonalInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *PersonalInfoWidget)
    {
        PersonalInfoWidget->setWindowTitle(QCoreApplication::translate("PersonalInfoWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PersonalInfoWidget: public Ui_PersonalInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONALINFOWIDGET_H
