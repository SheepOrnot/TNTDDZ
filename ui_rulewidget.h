/********************************************************************************
** Form generated from reading UI file 'rulewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULEWIDGET_H
#define UI_RULEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RuleWidget
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QWidget *RuleWidget)
    {
        if (RuleWidget->objectName().isEmpty())
            RuleWidget->setObjectName("RuleWidget");
        RuleWidget->resize(450, 540);
        scrollArea = new QScrollArea(RuleWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 0, 450, 541));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 448, 539));
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(RuleWidget);

        QMetaObject::connectSlotsByName(RuleWidget);
    } // setupUi

    void retranslateUi(QWidget *RuleWidget)
    {
        RuleWidget->setWindowTitle(QCoreApplication::translate("RuleWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RuleWidget: public Ui_RuleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULEWIDGET_H
