QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcomponentdialog.cpp \
    characteristic.cpp \
    component.cpp \
    computer.cpp \
    dbconnection.cpp \
    deletecomponentdialog.cpp \
    editcomponentdialog.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    user.cpp \
    warehouse.cpp

HEADERS += \
    addcomponentdialog.h \
    characteristic.h \
    component.h \
    computer.h \
    dbconnection.h \
    deletecomponentdialog.h \
    editcomponentdialog.h \
    loginwindow.h \
    mainwindow.h \
    user.h \
    warehouse.h

FORMS += \
    addcomponentdialog.ui \
    deletecomponentdialog.ui \
    editcomponentdialog.ui \
    loginwindow.ui \
    mainwindow.ui
	
INCLUDEPATH += \
    $$PWD/../3rdparty/libpqxx/include

LIBS += Ws2_32.lib \
    "C:/Program Files/PostgreSQL/15/lib/libpq.lib"
	
Release:LIBS += \
    $$PWD/../3rdparty/libpqxx/lib/Release/pqxx.lib
	
Debug:LIBS += \
    $$PWD/../3rdparty/libpqxx/lib/Debug/pqxx.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
