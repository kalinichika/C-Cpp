TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    jsonserver.cpp \
    ../resource/log.cpp \
    ../resource/cJSON.c \
    ../resource/counters_view_json.cpp \
    ../resource/net_resource.cpp \
    ../resource/counters.cpp \
    ../resource/counters_manager.cpp

HEADERS += \
    jsonserver.h \
    ../resource/bad_c_s_exception.h \
    ../resource/cJSON.h \
    ../resource/headers.h \
    ../resource/log.h \
    ../resource/counters.h \
    ../resource/counters_manager.h \
    ../resource/counters_view_json.h \
    ../resource/net_resource.h
