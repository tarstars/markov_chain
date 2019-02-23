TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lboost_system -lboost_filesystem

SOURCES += \
        main.cpp \
    markov_automaton.cpp \
    util.cpp \
    locale_services.cpp \
    poly_hash.cpp

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
    hello_test_01.txt \
    automaton_00.idx \
    automaton_00.mtx

HEADERS += \
    markov_automaton.h \
    util.h \
    locale_services.h \
    poly_hash.h
