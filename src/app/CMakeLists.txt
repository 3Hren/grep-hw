cmake_minimum_required(VERSION 2.8)
SET(PROJECT
    grep-hw)

SET(HEADERS
    ThreadSafeQueue.h
    GrepGlobal.h
    PathWalker.h
    WordCounter.h
    WordCountManager.h)

SET(SOURCES
    PathWalker.cpp
    WordCounter.cpp
    WordCountManager.cpp
    main.cpp)

SET(BOOST_COMPONENTS
    thread
    system
    filesystem
    regex)

SET(Boost_USE_MULTITHREADED ON)

add_definitions(-std=c++11)
add_definitions(-DGREP_DEBUG)

PROJECT(${PROJECT})

find_package(Threads)
find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
include_directories("${PROJECT_BINARY_DIR}")
add_executable(${PROJECT} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
SET_TARGET_PROPERTIES(${PROJECT} PROPERTIES ENABLE_EXPORTS true)
