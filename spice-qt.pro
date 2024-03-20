TEMPLATE = lib

QT += widgets
QT += core gui
QT += gui x11extras
CONFIG += no_keywords
CXXFLAGS += -g

INCLUDEPATH += /usr/include/glib-2.0 /usr/include/glib-2.0/gobject /usr/include/glib-2.0/glib /usr/lib/x86_64-linux-gnu/glib-2.0/include /usr/include/spice-client-glib-2.0 /usr/include/pixman-1 /usr/include/spice-1 ./common ./headers
LIBS += `pkg-config --libs glib-2.0 spice-client-glib-2.0`
HEADERS += headers/spice-common.h \
           headers/spice-widget.h \
           headers/spice-widget-priv.h \
           headers/spice-gtk-session.h \
           headers/spiceqt.h \
    spicewidget.h \
    spicemainwindow.h

SOURCES += src/spice-widget.cpp \
           src/spiceqt.cpp \
    spicewidget.cpp \
    spicemainwindow.cpp

CONFIG += no_keywords

FORMS += \
    spicewidget.ui \
    spicemainwindow.ui
