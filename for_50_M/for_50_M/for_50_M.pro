DEFINES += QT_DLL QWT_DLL
LIBS += -L"C:\Qt\6.2.2\mingw_64\lib" -lqwtd
LIBS += -L"C:\Qt\6.2.2\mingw_64\lib" -lqwt
INCLUDEPATH += C:\Qt\6.2.2\mingw_64\include\qwt

QT += serialport

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serial_osc
TEMPLATE = app
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
