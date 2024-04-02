QT       += core gui multimedia network
QT       += multimedia
QT       += core5compat
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += no_keywords
CONFIG += c++17

QMAKE_CXXFLAGS += -lsioclient
QMAKE_CXXFLAGS += -lboost_random
QMAKE_CXXFLAGS += -lboost_system
QMAKE_CXXFLAGS += -lboost_date_time
# LIBS += -lsioclient
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
    socketioclient.cpp \
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
    socketioclient.h \
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

INCLUDEPATH += ./
INCLUDEPATH += ./../LIB/
INCLUDEPATH += /home/fish/program/boost_1_84_0/
INCLUDEPATH += /home/fish/Desktop/Software_project/qt_project/LIB/
INCLUDEPATH += /home/fish/gitpack/socket.io-client-cpp/lib/asio/asio/include/
INCLUDEPATH += /home/fish/gitpack/socket.io-client-cpp/lib/websocketpp/
INCLUDEPATH += /home/fish/gitpack/socket.io-client-cpp/lib/rapidjson/include/
INCLUDEPATH += /home/fish/gitpack/socket.io-client-cpp/src/
INCLUDEPATH += /home/fish/gitpack/socket.io-client-cpp/src/internal


unix:!macx: LIBS += -L$$PWD/../LIB/ -lsioclient

INCLUDEPATH += $$PWD/../LIB
DEPENDPATH += $$PWD/../LIB

unix:!macx: PRE_TARGETDEPS += $$PWD/../LIB/libsioclient.a
