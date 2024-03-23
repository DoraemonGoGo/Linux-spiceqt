#-------------------------------------------------
#
# Project created by QtCreator 2024-03-02T20:31:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spice-client1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

CXXFLAGS += -g

UI_DIR = ./UI

QMAKE_LFLAGS += -L../
INCLUDEPATH += /usr/include/glib-2.0 /usr/include/glib-2.0/gobject /usr/lib/x86_64-linux-gnu/glib-2.0/include /usr/include/spice-client-glib-2.0 /usr/include/pixman-1 /usr/include/spice-1 ../common ../headers
LIBS += -lspice-qt
LIBS += -L/home/doraemon/Downloads/spice-qt/build -lspice-qt

LIBS += -lgobject-2.0 -lglib-2.0

SOURCES += \
        main.cpp \
        widget.cpp \
    spicemainwindow.cpp \
    resizeto.cpp \
    resdialog.cpp \
    spicetest.cpp

HEADERS += \
        widget.h \
    spicemainwindow.h \
    resizeto.h \
    resdialog.h \
    spicetest.h

FORMS += \
        widget.ui \
    spicemainwindow.ui \
    resizeto.ui \
    resdialog.ui \
    spicetest.ui

CONFIG += no_keywords

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
