/********************************************************************************
** Form generated from reading UI file 'gameoverwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEOVERWIDGET_H
#define UI_GAMEOVERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameOverWidget
{
public:
    QLabel *Title;
    QLabel *Username3;
    QLabel *Username1;
    QLabel *Username2;
    QLabel *Times3;
    QLabel *Times1;
    QLabel *Times2;
    QLabel *Score3;
    QLabel *Score1;
    QLabel *Score2;
    QPushButton *ReturnToLobby;
    QPushButton *ContinueGame;

    void setupUi(QWidget *GameOverWidget)
    {
        if (GameOverWidget->objectName().isEmpty())
            GameOverWidget->setObjectName("GameOverWidget");
        GameOverWidget->resize(1186, 667);
        Title = new QLabel(GameOverWidget);
        Title->setObjectName("Title");
        Title->setGeometry(QRect(380, 60, 400, 160));
        Title->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 72pt \"ZXF Small Pudding Trial\";"));
        Username3 = new QLabel(GameOverWidget);
        Username3->setObjectName("Username3");
        Username3->setGeometry(QRect(330, 270, 201, 51));
        Username1 = new QLabel(GameOverWidget);
        Username1->setObjectName("Username1");
        Username1->setGeometry(QRect(330, 340, 201, 51));
        Username2 = new QLabel(GameOverWidget);
        Username2->setObjectName("Username2");
        Username2->setGeometry(QRect(330, 410, 201, 51));
        Times3 = new QLabel(GameOverWidget);
        Times3->setObjectName("Times3");
        Times3->setGeometry(QRect(570, 270, 81, 51));
        Times1 = new QLabel(GameOverWidget);
        Times1->setObjectName("Times1");
        Times1->setGeometry(QRect(570, 340, 81, 51));
        Times2 = new QLabel(GameOverWidget);
        Times2->setObjectName("Times2");
        Times2->setGeometry(QRect(570, 410, 81, 51));
        Score3 = new QLabel(GameOverWidget);
        Score3->setObjectName("Score3");
        Score3->setGeometry(QRect(760, 270, 111, 51));
        Score1 = new QLabel(GameOverWidget);
        Score1->setObjectName("Score1");
        Score1->setGeometry(QRect(760, 340, 111, 51));
        Score2 = new QLabel(GameOverWidget);
        Score2->setObjectName("Score2");
        Score2->setGeometry(QRect(760, 410, 111, 51));
        ReturnToLobby = new QPushButton(GameOverWidget);
        ReturnToLobby->setObjectName("ReturnToLobby");
        ReturnToLobby->setGeometry(QRect(190, 520, 191, 71));
        ContinueGame = new QPushButton(GameOverWidget);
        ContinueGame->setObjectName("ContinueGame");
        ContinueGame->setGeometry(QRect(770, 520, 191, 71));

        retranslateUi(GameOverWidget);

        QMetaObject::connectSlotsByName(GameOverWidget);
    } // setupUi

    void retranslateUi(QWidget *GameOverWidget)
    {
        GameOverWidget->setWindowTitle(QCoreApplication::translate("GameOverWidget", "Form", nullptr));
        Title->setText(QCoreApplication::translate("GameOverWidget", "   \350\203\234\345\210\251", nullptr));
        Username3->setText(QCoreApplication::translate("GameOverWidget", "Uname1\357\274\210Identity\357\274\211", nullptr));
        Username1->setText(QCoreApplication::translate("GameOverWidget", "Uname2", nullptr));
        Username2->setText(QCoreApplication::translate("GameOverWidget", "Uname3", nullptr));
        Times3->setText(QCoreApplication::translate("GameOverWidget", "      \342\250\211N", nullptr));
        Times1->setText(QCoreApplication::translate("GameOverWidget", "      \342\250\211N", nullptr));
        Times2->setText(QCoreApplication::translate("GameOverWidget", "      \342\250\211N", nullptr));
        Score3->setText(QCoreApplication::translate("GameOverWidget", "-aaaa", nullptr));
        Score1->setText(QCoreApplication::translate("GameOverWidget", "+bbbb", nullptr));
        Score2->setText(QCoreApplication::translate("GameOverWidget", "-cccc", nullptr));
        ReturnToLobby->setText(QCoreApplication::translate("GameOverWidget", "\350\277\224\345\233\236\345\244\247\345\216\205", nullptr));
        ContinueGame->setText(QCoreApplication::translate("GameOverWidget", "\347\273\247\347\273\255\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameOverWidget: public Ui_GameOverWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEOVERWIDGET_H
