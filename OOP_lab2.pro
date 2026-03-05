TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        iterator_exception.cpp \
        main.cpp \
        matrix_base_exception.cpp \
        matrix_index_exception.cpp

HEADERS += \
    iterator.h \
    iterator_exception.h \
    iterator_impl.h \
    matrix.h \
    matrix_base_exception.h \
    matrix_impl.h \
    matrix_index_exception.h
