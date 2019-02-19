TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lboost_system -lboost_filesystem

SOURCES += \
        main.cpp \
    markov_automaton.cpp

DISTFILES += \
    ars.txt

HEADERS += \
    markov_automaton.h
