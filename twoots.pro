#-------------------------------------------------
#
# Project created by QtCreator 2015-07-27T21:31:22
#
#-------------------------------------------------

QT       += core gui network script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = twoots
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    o2/o1.cpp \
    o2/o1requestor.cpp \
    o2/o2.cpp \
    o2/o2facebook.cpp \
    o2/o2gft.cpp \
    o2/o2hubic.cpp \
    o2/o2reply.cpp \
    o2/o2replyserver.cpp \
    o2/o2requestor.cpp \
    o2/o2settingsstore.cpp \
    o2/o2skydrive.cpp \
    o2/oxtwitter.cpp \
    o2/simplecrypt.cpp \
    twitterapi.cpp

HEADERS  += mainwindow.h \
    o2/o1.h \
    o2/o1dropbox.h \
    o2/o1flickr.h \
    o2/o1freshbooks.h \
    o2/o1requestor.h \
    o2/o1twitter.h \
    o2/o2.h \
    o2/o2abstractstore.h \
    o2/o2facebook.h \
    o2/o2gft.h \
    o2/o2globals.h \
    o2/o2hubic.h \
    o2/o2reply.h \
    o2/o2replyserver.h \
    o2/o2requestor.h \
    o2/o2settingsstore.h \
    o2/o2skydrive.h \
    o2/oxtwitter.h \
    o2/simplecrypt.h \
    twitterapi.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    o2/src.pri

