#-------------------------------------------------
#
# Project created by QtCreator 2013-03-11T13:05:59
#
#-------------------------------------------------

QT       += core gui network xml

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = MultiScreenClient
CONFIG(debug, debug|release){
    TARGET = MultiScreenClientd
} else {
    TARGET = MultiScreenClient
}
DESTDIR = ../MultiscreenClient/bin/$$TARGET
TEMPLATE = app


SOURCES += main.cpp

RC_FILE = logo.rc

LIBS  += ../MultiscreenClient/lib/WS2_32.Lib

include(MultiScreenClient.pri)

HEADERS +=

FORMS +=
