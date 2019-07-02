TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../net_resource/net_resource.cpp \
    ../net_resource/log.cpp \
    jsonserver.cpp

HEADERS += \
    ../net_resource/net_resource.h \
    ../net_resource/log.h \
    jsonserver.h
