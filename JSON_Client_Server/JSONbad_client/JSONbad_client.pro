TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../resource/log.cpp \
    ../resource/net_resource.cpp \
    ../resource/cJSON.c \
    jsonbad_client.cpp

HEADERS += \
    ../resource/bad_c_s_exception.h \
    ../resource/headers.h \
    ../resource/log.h \
    ../resource/net_resource.h \
    ../resource/cJSON.h \
    jsonbad_client.h
