TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../net_resource/net_resource.cpp \
    ../net_resource/log.cpp \
    jsonserver.cpp \
    ../net_resource/create_epoll.cpp \
    ../net_resource/bad_c_s_exception.cpp \
    ../net_resource/cJSON.c

HEADERS += \
    ../net_resource/net_resource.h \
    ../net_resource/log.h \
    jsonserver.h \
    ../net_resource/create_epoll.h \
    ../net_resource/headers.h \
    ../net_resource/bad_c_s_exception.h \
    ../net_resource/cJSON.h
