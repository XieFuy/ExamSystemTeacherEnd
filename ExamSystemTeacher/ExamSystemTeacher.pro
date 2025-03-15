QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    classsavedlg.cpp \
    clientsocket.cpp \
    correctsubjectivequestionscontorler.cpp \
    correctsubjectivequestionsdlg.cpp \
    correctsubjectivequestionsmodel.cpp \
    datetimeselectdlg.cpp \
    dbhelper.cpp \
    dpihelper.cpp \
    exitlogindlg.cpp \
    logincontorller.cpp \
    loginmodel.cpp \
    main.cpp \
    mainmenuecontorller.cpp \
    mainmenuedlg.cpp \
    mainmenuemodel.cpp \
    namechangedlg.cpp \
    phonenumberchangedlg.cpp \
    previewtestpapercontorller.cpp \
    previewtestpaperdlg.cpp \
    previewtestpapermodel.cpp \
    registercontorller.cpp \
    registerdlg.cpp \
    registermodel.cpp \
    testpaperreleasedlg.cpp \
    testpapersavedlg.cpp \
    threadpool.cpp \
    widget.cpp

HEADERS += \
    classsavedlg.h \
    clientsocket.h \
    correctsubjectivequestionscontorler.h \
    correctsubjectivequestionsdlg.h \
    correctsubjectivequestionsmodel.h \
    datetimeselectdlg.h \
    dbhelper.h \
    dpihelper.h \
    exitlogindlg.h \
    logincontorller.h \
    loginmodel.h \
    mainmenuecontorller.h \
    mainmenuedlg.h \
    mainmenuemodel.h \
    namechangedlg.h \
    phonenumberchangedlg.h \
    previewtestpapercontorller.h \
    previewtestpaperdlg.h \
    previewtestpapermodel.h \
    registercontorller.h \
    registerdlg.h \
    registermodel.h \
    testpaperreleasedlg.h \
    testpapersavedlg.h \
    threadpool.h \
    widget.h

FORMS += \
    classsavedlg.ui \
    correctsubjectivequestionsdlg.ui \
    datetimeselectdlg.ui \
    exitlogindlg.ui \
    mainmenuedlg.ui \
    namechangedlg.ui \
    phonenumberchangedlg.ui \
    previewtestpaperdlg.ui \
    registerdlg.ui \
    testpaperreleasedlg.ui \
    testpapersavedlg.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

LIBS += -lws2_32

INCLUDEPATH += .\include

include(QXlsx/QXlsx.pri)

win32: LIBS += -L$$PWD/./ -llibmysql

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./libmysql.lib

win32: LIBS += -L$$PWD/./ -lGdi32

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./Gdi32.lib

win32: LIBS += -L$$PWD/./ -lUser32

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./User32.lib

win32: LIBS += -L$$PWD/./ -lshell32

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./shell32.lib

# 指定 libmysql.dll 的路径
#LIBMYSQL_DLL = ./libmysql.dll
# 在构建完成后复制 libmysql.dll
#QMAKE_POST_LINK += $$quote(cmd /c copy /y $$LIBMYSQL_DLL $$OUT_PWD/$${DESTDIR})

#指定 gdi32.dll
#LIBGDI32_DLL = ./gdi32.dll
#QMAKE_POST_LINK += $$quote(cmd /c copy /y $$LIBGDI32_DLL $$OUT_PWD/$${DESTDIR})

#指定 shell32.dll
#LIBSHELL32_DLL = ./shell32.dll
#QMAKE_POST_LINK += $$quote(cmd /c copy /y $$LIBSHELL32_DLL $$OUT_PWD/$${DESTDIR})

#指定 user32.dll
#LIBUSER32_DLL = ./user32.dll
#QMAKE_POST_LINK += $$quote(cmd /c copy /y $$LIBUSER32_DLL $$OUT_PWD/$${DESTDIR})
