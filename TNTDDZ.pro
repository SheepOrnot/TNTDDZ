QT       += core gui
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
    effectplayer.cpp \
    cardprocess.cpp \
    findandsignupwidget.cpp \
    gameoverwidget.cpp \
    gamewidget.cpp \
    lobbywidget.cpp \
    main.cpp \
    mainwindow.cpp \
    personalinfowidget.cpp \
    robot.cpp \
    settingwidget.cpp \
    singlegame.cpp \
    socketioclient.cpp \
    widgetcard.cpp

HEADERS += \
    HTTPJSONSender.h \
    backgroundwidget.h \
    effectplayer.h \
    cardprocess.h \
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
    robot.h \
    settingwidget.h \
    singlegame.h \
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

unix:!macx:INCLUDEPATH += ./
unix:!macx:INCLUDEPATH += ./../LIB/
unix:!macx:INCLUDEPATH += /home/fish/program/boost_1_84_0/
unix:!macx:INCLUDEPATH += /home/fish/Desktop/Software_project/qt_project/LIB/
unix:!macx:INCLUDEPATH += /home/fish/gitpack/socket.io-client-cpp/lib/asio/asio/include/
unix:!macx:INCLUDEPATH += /home/fish/gitpack/socket.io-client-cpp/lib/websocketpp/
unix:!macx:INCLUDEPATH += /home/fish/gitpack/socket.io-client-cpp/lib/rapidjson/include/
unix:!macx:INCLUDEPATH += /home/fish/gitpack/socket.io-client-cpp/src/
unix:!macx:INCLUDEPATH += /home/fish/gitpack/socket.io-client-cpp/src/internal


unix:!macx: LIBS += -L$$PWD/../LIB/ -lsioclient

unix:!macx:INCLUDEPATH += $$PWD/../LIB
unix:!macx:DEPENDPATH += $$PWD/../LIB

unix:!macx: PRE_TARGETDEPS += $$PWD/../LIB/libsioclient.a

BOOST = D:\\Program\\library\\boost_1_84_0
win32: INCLUDEPATH += $$BOOST
win32: LIBS += -L$$BOOST\\stage\\lib
win32: LIBS += -lws2_32
SOCKETIO = D:\\Program\\library\\socket.io-client-cpp
win32: INCLUDEPATH += $$SOCKETIO\\lib\\asio\\asio\\include
win32: INCLUDEPATH += $$SOCKETIO\\lib\\websocketpp
win32: INCLUDEPATH += $$SOCKETIO\\lib\\rapidjson\\include
win32: INCLUDEPATH += $$SOCKETIO\\src\\internal
win32: INCLUDEPATH += $$SOCKETIO\\src
win32: SOURCES += $$SOCKETIO\\src\\internal\\sio_packet.cpp
win32: SOURCES += $$SOCKETIO\\src\\internal\\sio_client_impl.cpp
win32: SOURCES += $$SOCKETIO\\src\\sio_client.cpp
win32: SOURCES += $$SOCKETIO\\src\\sio_socket.cpp
win32: HEADERS += $$SOCKETIO\\src\\sio_client.h
win32: DEFINES += BOOST_DATE_TIME_NO_LIB
win32: DEFINES += BOOST_REGEX_NO_LIB
win32: DEFINES += ASIO_STANDALONE
win32: DEFINES += _WEBSOCKETPP_CPP11_STL_
win32: DEFINES += _WEBSOCKETPP_CPP11_FUNCTIONAL_
