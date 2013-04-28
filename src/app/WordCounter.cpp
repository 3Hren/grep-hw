#include "WordCounter.h"

#include <fstream>
#include <algorithm>
#include <string.h>

WordCountMap WordCounter::countWords(std::istream &stream)
{
    WordCountMap wordCountMap;
    for (std::string unparsedWord; stream >> unparsedWord;) {
        std::string word;
        word.reserve(unparsedWord.length());
        for (auto it = unparsedWord.begin(); it != unparsedWord.end(); ++it) {
            char character = *it;
            if (isalnum(character)) {
                word += character;
            } else {
                if (!word.empty()) {
                    std::transform(word.begin(), word.end(), word.begin(), tolower);
                    wordCountMap[word]++;
                    word.clear();
                }
            }
        }

        if (!word.empty()) {
            std::transform(word.begin(), word.end(), word.begin(), tolower);
            wordCountMap[word]++;
        }
    }
    return wordCountMap;
}

WordCountMap WordCounter::countWords(const std::string &filename)
{
    std::ifstream stream;
    stream.open(filename);
    if (!stream) {
        std::cerr << "Unable to open file '" << filename << "' - " << strerror(errno) << " [" << errno << "]" << std::endl;
        return WordCountMap();
    }
    return countWords(stream);
}
