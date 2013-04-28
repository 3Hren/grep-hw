ROOT_PATH = ../..
TEMPLATE = app
TARGET = grep-hw

LIBS += \
    #-lboost_system \
    -lboost_filesystem

include(Grep.pri)

SOURCES += \
    main.cpp

HEADERS +=
