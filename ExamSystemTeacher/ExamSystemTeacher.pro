QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clientsocket.cpp \
    dbhelper.cpp \
    logincontorller.cpp \
    loginmodel.cpp \
    main.cpp \
    registerdlg.cpp \
    widget.cpp

HEADERS += \
    clientsocket.h \
    dbhelper.h \
    logincontorller.h \
    loginmodel.h \
    registerdlg.h \
    widget.h

FORMS += \
    registerdlg.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

LIBS += -lws2_32

INCLUDEPATH += .\include


win32: LIBS += -L$$PWD/./ -llibmysql

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./libmysql.lib
