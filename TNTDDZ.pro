QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    argclass.cpp \
    backgroundwidget.cpp \
    findandsignupwidget.cpp \
    gamewidget.cpp \
    lobbywidget.cpp \
    main.cpp \
    mainwindow.cpp \
    widgetargcard.cpp \
    widgetargplayer.cpp \
    widgetargroom.cpp \
    widgetcard.cpp

HEADERS += \
    argclass.h \
    backgroundwidget.h \
    findandsignupwidget.h \
    gamewidget.h \
    lobbywidget.h \
    mainwindow.h \
    widgetargcard.h \
    widgetargplayer.h \
    widgetargroom.h \
    widgetcard.h

FORMS += \
    findandsignupwidget.ui \
    gamewidget.ui \
    lobbywidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
