#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T12:04:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = timer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    timer.cpp

HEADERS  += mainwindow.h \
    timer.h

FORMS    += mainwindow.ui

RESOURCES += \
    play.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qtspeech/lib/release/ -lQt5TextToSpeech
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qtspeech/lib/debug/ -lQt5TextToSpeech
else:unix: LIBS += -L$$PWD/../qtspeech/lib/ -lQt5TextToSpeech

INCLUDEPATH += $$PWD/../qtspeech/include
DEPENDPATH += $$PWD/../qtspeech/include
