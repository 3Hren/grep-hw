#include <iostream>

#include <string>
#include <boost/filesystem.hpp>
#include <boost/progress.hpp>

#include "PathWalker.h"
#include "WordCountManager.h"

int main(int argc, char *argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: " << boost::filesystem::path(argv[0]).filename().string() << " [PATH]" << std::endl;
        std::cerr << "Example: '" << boost::filesystem::path(argv[0]).filename().string() << " /home' - work in '/home' directory" << std::endl;
        std::cerr << "Example: '" << boost::filesystem::path(argv[0]).filename().string() << "' - work in current directory" << std::endl;
        return 1;
    }

    std::string path = argc == 1 ? "." : argv[1];

    boost::progress_timer t;
    WordCountManager wordCountManager;
    wordCountManager.calculateWordCount(path);
    return 0;
}
