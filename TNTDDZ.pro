QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backgroundwidget.cpp \
    findandsignupwidget.cpp \
    gameoverwidget.cpp \
    gamewidget.cpp \
    lobbywidget.cpp \
    main.cpp \
    mainwindow.cpp \
    personalinfowidget.cpp \
    settingwidget.cpp \
    widgetcard.cpp

HEADERS += \
    HTTPJSONSender.h \
    backgroundwidget.h \
    common.h \
    findandsignupwidget.h \
    gameoverwidget.h \
    gamewidget.h \
    lobbywidget.h \
    mainwindow.h \
    personalinfowidget.h \
    messagecenter.h \
    messagepackage.h \
    networkrevpacker.h \
    settingwidget.h \
    threadpool.h \
    widgetargpackage.h \
    widgetcard.h \
    widgetrevpacker.h

FORMS += \
    findandsignupwidget.ui \
    gameoverwidget.ui \
    gamewidget.ui \
    lobbywidget.ui \
    mainwindow.ui \
    personalinfowidget.ui \
    settingwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

INCLUDEPATH += /home/fish/program/boost_1_84_0/
