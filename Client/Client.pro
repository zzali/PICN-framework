#-------------------------------------------------
#
# Project created by QtCreator 2013-12-30T13:17:36
#
#-------------------------------------------------

QT       += core network gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += embed_manifest_exe
TEMPLATE = app


SOURCES += main.cpp \
    ProxyServer.cpp \
    ClientCore.cpp \
    Request.cpp \
    Provider.cpp \
    HTTPProvider.cpp \
    sICNProvider.cpp \
    PublisherThread.cpp \
    Publisher.cpp \
    Globals.cpp \
    MainWidget.cpp \
    RepositoryCreatorThread.cpp \
    RepositoryCreator.cpp \
    PublisherServer.cpp \
    PeerRequest.cpp \
    Neighbor.cpp \
    Content.cpp \
    RequestHandlerThread.cpp \
    SendHelloThread.cpp \
    RegisterRepository.cpp \
    LogThread.cpp

HEADERS += \
    ProxyServer.h \
    ClientCore.h \
    Request.h \
    Provider.h \
    HTTPProvider.h \
    sICNProvider.h \
    PublisherThread.h \
    Publisher.h \
    MainWidget.h \
    RepositoryCreatorThread.h \
    RepositoryCreator.h \
    PublisherServer.h \
    PeerRequest.h \
    Neighbor.h \
    Content.h \
    RequestHandlerThread.h \
    Definitions.h \
    SendHelloThread.h \
    RegisterRepository.h \
    LogThread.h
