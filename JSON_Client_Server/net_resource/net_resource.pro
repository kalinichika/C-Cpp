TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    net_resource.cpp \
    log.cpp

HEADERS += \
    net_resource.h \
    log.h
