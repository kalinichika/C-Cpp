TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    jsonclient.cpp \
    ../resource/log.cpp \
    ../resource/net_resource.cpp \
    ../resource/cJSON.c

HEADERS += \
    jsonclient.h \
    ../resource/bad_c_s_exception.h \
    ../resource/headers.h \
    ../resource/log.h \
    ../resource/net_resource.h \
    ../resource/cJSON.h
