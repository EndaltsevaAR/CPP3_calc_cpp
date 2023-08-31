QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    qcustomplot.cpp \
    creditwindow.cpp \
    depositwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    ../Controller/Controller.cc

HEADERS += \
    qcustomplot.h \
    creditwindow.h \
    depositwindow.h \
    mainwindow.h \
    ../Controller/Controller.h

FORMS += \
    creditwindow.ui \
    depositwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
