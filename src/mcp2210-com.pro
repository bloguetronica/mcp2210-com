QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Added to provide backwards compatibility (C++11 support)
greaterThan(QT_MAJOR_VERSION, 4) {
    CONFIG += c++11
} else {
    QMAKE_CXXFLAGS += -std=c++11
}

TARGET = mcp2210-com
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    chipsettingsdialog.cpp \
    common.cpp \
    data.cpp \
    delaysdialog.cpp \
    devicewindow.cpp \
    informationdialog.cpp \
    libusb-extra.c \
    main.cpp \
    mainwindow.cpp \
    mcp2210.cpp \
    statusdialog.cpp

HEADERS += \
    aboutdialog.h \
    chipsettingsdialog.h \
    common.h \
    data.h \
    delaysdialog.h \
    devicewindow.h \
    informationdialog.h \
    libusb-extra.h \
    mainwindow.h \
    mcp2210.h \
    statusdialog.h

FORMS += \
    aboutdialog.ui \
    chipsettingsdialog.ui \
    delaysdialog.ui \
    devicewindow.ui \
    informationdialog.ui \
    mainwindow.ui \
    statusdialog.ui

LIBS += -lusb-1.0

# Added installation option
unix {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    target.path = $$PREFIX/bin
    icon.files += icons/mcp2210-com.png
    icon.path = $$PREFIX/share/icons/hicolor/128x128/apps
    shortcut.files = misc/mcp2210-com.desktop
    shortcut.path = $$PREFIX/share/applications
    INSTALLS += icon
    INSTALLS += shortcut
}

!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
