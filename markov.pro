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
    hello_test \
    t.txt \
    debug.txt \
    wp_utf8.txt \
    matrix_00 \
    hello_test_00.txt \
    hello_test_01.txt

HEADERS += \
    markov_automaton.h \
    localized_charfilter.h
