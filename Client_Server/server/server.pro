TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    server.cpp \
    ../net_resource/net_resource.cpp \
    ../net_resource/log.cpp

HEADERS += \
    server.h \
    ../net_resource/net_resource.h \
    ../net_resource/log.h
