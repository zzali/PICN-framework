#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T13:40:27
#
#-------------------------------------------------

QT       += core network gui

TARGET = Seeker
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    PublisherFinder.cpp \
    Client.cpp \
    ActiveClients.cpp \
    Request.cpp \
    RegisterRequest.cpp \
    HelloRequest.cpp \
    SeekRequest.cpp \
    RequestHandler.cpp \
    Server.cpp \
    Definitions.cpp \
    LogThread.cpp \
    ProcessDatagramThread.cpp

HEADERS += \
    PublisherFinder.h \
    ContentKey.h \
    Client.h \
    ActiveClients.h \
    Request.h \
    RegisterRequest.h \
    HelloRequest.h \
    SeekRequest.h \
    RequestHandler.h \
    Server.h \
    Definitions.h \
    LogThread.h \
    ProcessDatagramThread.h
