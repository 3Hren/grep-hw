QMAKE_CXXFLAGS += -std=c++11

LIBS += \
    -lboost_system \
    -lboost_filesystem \
    -lboost_regex

SOURCES += \
    WordCounter.cpp \
    PathWalker.cpp \
    WordCountManager.cpp

HEADERS += \
    WordCounter.h \
    PathWalker.h \
    WordCountManager.h \
    ThreadSafeQueue.h \
    GrepGlobal.h
