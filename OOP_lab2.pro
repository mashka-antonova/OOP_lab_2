TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        iterator_exception.cpp \
        main.cpp \
        matrix_base_exception.cpp \
        test.cpp

HEADERS += \
    iterator.h \
    iterator_exception.h \
    matrix.h \
    matrix_base_exception.h \
    test.h
