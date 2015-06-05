#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T17:23:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSIP
TEMPLATE = app


SOURCES += main.cpp\
        qsip.cpp \
    SipThread.cpp

HEADERS  += qsip.h \
    SipThread.h

FORMS    += qsip.ui

LIBS += -losipparser2 \
    -losip2 \
    -leXosip2 \
    -lortp \
    -lmediastreamer_voip

RESOURCES += \
    image.qrc
