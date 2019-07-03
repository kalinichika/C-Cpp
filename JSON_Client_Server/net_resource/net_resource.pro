TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    net_resource.cpp \
    log.cpp \
    create_epoll.cpp

HEADERS += \
    net_resource.h \
    log.h \
    headers.h \
    create_epoll.h
