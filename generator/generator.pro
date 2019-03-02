TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lboost_system -lboost_filesystem
VPATH += ../common_code
DESTDIR = ../bin

SOURCES += \
        main.cpp \
    util.cpp \
    markov_automaton.cpp \
    poly_hash.cpp \
    discrete_distribution.cpp \
    markov_sampler.cpp \
    generation_context.cpp \
    random_singleton.cpp \
    global_locale.cpp \
    ../common_code/automaton_updater.cpp

DISTFILES += \
    ../markov_chain.md \
    ../data/hello_test_01_start_context

HEADERS += \
    markov_sampler.h \
    generator.h \
    generator.h \
    markov_automaton.h \
    markov_sampler.h \
    poly_hash.h \
    util.h \
    discrete_distribution.h \
    generation_context.h \
    random_singleton.h \
    global_locale.h
