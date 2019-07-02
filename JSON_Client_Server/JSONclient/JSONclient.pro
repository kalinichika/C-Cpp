TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../net_resource/log.cpp \
    ../net_resource/net_resource.cpp \
    jsonclient.cpp

HEADERS += \
    ../net_resource/log.h \
    ../net_resource/net_resource.h \
    jsonclient.h
