#pragma once

#include <iostream>
#include "GrepGlobal.h"

class WordCounter
{
public:    
    static WordCountMap countWords(std::istream &stream);
    static WordCountMap countWords(const std::string &filename);
};
