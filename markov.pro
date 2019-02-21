TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lboost_system -lboost_filesystem

SOURCES += \
        main.cpp \
    markov_automaton.cpp \
    localized_charfilter.cpp

DISTFILES += \
    ars.txt \
    bash.txt \
    hello_test \
    dict_00 \
    automaton_00 \
    hello_test

HEADERS += \
    markov_automaton.h \
    localized_charfilter.h
