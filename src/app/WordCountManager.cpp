#include "WordCountManager.h"

#include <cstdio>

#include <iostream>
#include <unistd.h>
#include <sstream>

#include "PathWalker.h"
#include "WordCounter.h"

inline void print(std::ostream &s) {
    std::cout << s.rdbuf();
    std::cout.flush();
    s.clear();
}

WordCountManager::WordCountManager() :
    done(false)
{
}

WordCountManager::~WordCountManager()
{
    done = true;
    waitAll();
}

void WordCountManager::calculateWordCount(const std::string &path)
{    
    runProducer(path);
    runConsumers();
    waitAll();
    showMostPopularWords(10);
}

void WordCountManager::runProducer(const std::string &path)
{
    std::thread producer([this, path]{
        PathWalker pathWalker(path);
        auto onFileFoundAction = [this](const std::string &filename){
            queue.push(filename);
#ifdef GREP_DEBUG
            print(std::stringstream() << "[" << std::this_thread::get_id() << "]Producer pushed " << filename << " in queue\n");
#endif
        };
        pathWalker.execute(onFileFoundAction);
        done = true;
#ifdef GREP_DEBUG
        print(std::stringstream() << ">>> PRODUCER FINISHED <<<" << std::endl);
#endif
    });
    threads.push_back(std::move(producer));
}

void WordCountManager::runConsumers()
{
    for (int threadId = 0; threadId < threadCount; ++threadId)
        runConsumer();
}

void WordCountManager::runConsumer()
{
    std::thread consumer([this]{
        while (!done || !queue.isEmpty()) {
            std::string filename;
            if (queue.tryPop(filename)) {
#ifdef GREP_DEBUG
                print(std::stringstream() << "[" << std::this_thread::get_id() << "] Consumer popped " << filename << " from queue\n");
#endif
                WordCountMap wordCountMap = WordCounter::countWords(filename);
                std::lock_guard<std::mutex> lock(wordCountsMutex);
                for (const auto &wordCount : wordCountMap)
                    wordCounts[wordCount.first] += wordCount.second;
#ifdef GREP_DEBUG
                print(std::stringstream() << "[" << std::this_thread::get_id() << "] Consumer finished work: " << filename << "\n");
#endif
            } else {
                std::this_thread::yield();
            }
        }
    });
    threads.push_back(std::move(consumer));
}

void WordCountManager::waitAll()
{
    for (std::thread &thread : threads)
        if (thread.joinable())
            thread.join();
}

void WordCountManager::showMostPopularWords(std::size_t number)
{
    std::vector<WordCountMap::iterator> wordIterators;
    wordIterators.reserve(std::distance(wordCounts.begin(), wordCounts.end()));
    for (auto it = wordCounts.begin(); it != wordCounts.end(); ++it)
        wordIterators.push_back(it);

    auto middle = wordIterators.begin() + std::min(number, wordCounts.size());
    std::partial_sort(wordIterators.begin(), middle, wordIterators.end(), [](WordCountMap::iterator lhs, WordCountMap::iterator rhs){
        return lhs->second > rhs->second;
    });

    std::printf("%-20s %20s\n", "[Word]", "[Count]");
    for (auto it = wordIterators.cbegin(); it != middle; ++it) {
        std::printf("%-20s %20zu\n", (*it)->first.c_str(), (*it)->second);
    }
}
