#include "Mocks.h"

TEST(WordCounter, Class) {
    WordCounter counter;
    (void)counter;
}

TEST(WordCounter, CountsWords) {
    std::stringstream stream;
    stream << "simple text";
    WordCountMap expected = {
        {"simple", 1},
        {"text", 1}
    };

    WordCounter counter;
    EXPECT_EQ(expected, counter.countWords(stream));
}

TEST(WordCounter, CountsWordsIgnoreCase) {
    std::stringstream stream;
    stream << "Simple text is simple";
    WordCountMap expected = {
        {"simple", 2},
        {"text", 1},
        {"is", 1}
    };

    WordCounter counter;
    EXPECT_EQ(expected, counter.countWords(stream));
}

TEST(WordCounter, CountsWordsWithNumbers) {
    std::stringstream stream;
    stream << "simple text 100 200 100";
    WordCountMap expected = {
        {"simple", 1},
        {"text", 1},
        {"100", 2},
        {"200", 1},
    };

    WordCounter counter;
    EXPECT_EQ(expected, counter.countWords(stream));
}

TEST(WordCounter, CountsWordsWithSomeSeparatorsInWords) {
    std::stringstream stream;
    stream << "simple,text.100!200@ 100#$%^&*()hey!";
    WordCountMap expected = {
        {"simple", 1},
        {"text", 1},
        {"100", 2},
        {"200", 1},
        {"hey", 1}
    };

    WordCounter counter;
    EXPECT_EQ(expected, counter.countWords(stream));
}

TEST(WordCounter, CountsWordsNonAsciiCharactersIgnored) {
    std::stringstream stream;
    stream << u8"simple text привет";
    WordCountMap expected = {
        {"simple", 1},
        {"text", 1}
    };

    WordCounter counter;
    EXPECT_EQ(expected, counter.countWords(stream));
}

TEST(WordCounter, CountsWordsNoWords) {
    std::stringstream stream;
    stream << "~!@#$%^&*() -=_+ ;:' \" \\ |/ ,.? \r\n\t";
    WordCountMap expected = {};

    WordCounter counter;
    EXPECT_EQ(expected, counter.countWords(stream));
}
