TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lboost_system -lboost_filesystem
VPATH += ../common_code
DESTDIR = ../bin

SOURCES += \
        main.cpp \
    ../common_code/util.cpp \
    ../common_code/locale_services.cpp \
    ../common_code/markov_automaton.cpp \
    ../common_code/poly_hash.cpp \
    ../common_code/discrete_distribution.cpp \
    ../common_code/markov_sampler.cpp \
    ../common_code/generation_context.cpp \
    random_singleton.cpp

DISTFILES += \
    ../markov_chain.md \
    ../data/hello_test_01_start_context

HEADERS += \
    ../common_code/markov_sampler.h \
    ../common_code/generator.h \
    ../common_code/generator.h \
    ../common_code/locale_services.h \
    ../common_code/markov_automaton.h \
    ../common_code/markov_sampler.h \
    ../common_code/poly_hash.h \
    ../common_code/util.h \
    ../common_code/discrete_distribution.h \
    ../common_code/generation_context.h \
    random_singleton.h
