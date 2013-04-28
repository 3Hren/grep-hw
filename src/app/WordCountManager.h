#pragma once

#include <vector>
#include <atomic>
#include <thread>

#include "GrepGlobal.h"
#include "ThreadSafeQueue.h"

class WordCountManager
{
    const int threadCount = 4;
    std::vector<std::thread> threads;
    std::atomic_bool done;
    ThreadSafeQueue<std::string> queue;

    WordCountMap wordCounts;
    std::mutex wordCountsMutex;
public:
    WordCountManager();
    ~WordCountManager();

    void calculateWordCount(const std::string &path);

private:
    void runProducer(const std::string &path);
    void runConsumers();
    void runConsumer();

    void waitAll();

    void showMostPopularWords(std::size_t number);
};
