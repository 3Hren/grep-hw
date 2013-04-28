TEMPLATE = app
TARGET = tests
ROOT_PATH = ../..
APP_PATH = $${ROOT_PATH}/src/app

LIBS += -lgtest

include($${APP_PATH}/Grep.pri)
INCLUDEPATH += $${APP_PATH}
DEPENDPATH += $${APP_PATH}

SOURCES += \
    main.cpp \
    _test_WordCounter.cpp

HEADERS += \
    Mocks.h
