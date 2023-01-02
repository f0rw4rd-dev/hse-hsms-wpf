QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcomponentdialog.cpp \
    addcomputerdialog.cpp \
    adduserdialog.cpp \
    addwarehousedialog.cpp \
    characteristic.cpp \
    component.cpp \
    computer.cpp \
    dbconnection.cpp \
    deletecomponentdialog.cpp \
    deleteuserdialog.cpp \
    group.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    regularexpressions.cpp \
    setcomponentdialog.cpp \
    setuserdialog.cpp \
    user.cpp \
    warehouse.cpp

HEADERS += \
    addcomponentdialog.h \
    addcomputerdialog.h \
    adduserdialog.h \
    addwarehousedialog.h \
    characteristic.h \
    component.h \
    computer.h \
    dbconnection.h \
    deletecomponentdialog.h \
    deleteuserdialog.h \
    group.h \
    loginwindow.h \
    mainwindow.h \
    regularexpressions.h \
    setcomponentdialog.h \
    setuserdialog.h \
    user.h \
    warehouse.h

FORMS += \
    addcomponentdialog.ui \
    addcomputerdialog.ui \
    adduserdialog.ui \
    addwarehousedialog.ui \
    deletecomponentdialog.ui \
    deleteuserdialog.ui \
    loginwindow.ui \
    mainwindow.ui \
    setcomponentdialog.ui \
    setuserdialog.ui
	
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

RESOURCES += \
    icons.qrc
