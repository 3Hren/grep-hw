#include "PathWalker.h"

PathWalker::PathWalker(const std::string &startPathName, const boost::regex &pattern) :
    startPath(startPathName),
    pattern(pattern)
{
}

void PathWalker::execute(std::function<void(const std::string &)> action) const
{
    try {
        boost::filesystem::recursive_directory_iterator it(startPath);
        boost::filesystem::recursive_directory_iterator end;
        while (it != end) {
            std::string name = it->path().leaf().string();
            if (boost::regex_match(name, pattern))
                action(it->path().string());

            try {
                ++it;
            } catch (boost::filesystem::filesystem_error &error) {
                std::cerr << error.what() << std::endl;
                it.no_push();
            }
        }
    } catch (boost::filesystem::filesystem_error &error) {
        std::cerr << "Error occured while creating directory iterator - " << error.what() << std::endl;
    }
}
