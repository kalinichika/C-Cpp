TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../net_resource/log.cpp \
    ../net_resource/net_resource.cpp \
    jsonclient.cpp \
    ../net_resource/bad_c_s_exception.cpp \
    ../net_resource/cJSON.c

HEADERS += \
    ../net_resource/log.h \
    ../net_resource/net_resource.h \
    jsonclient.h \
    ../net_resource/bad_c_s_exception.h \
    ../net_resource/cJSON.h
