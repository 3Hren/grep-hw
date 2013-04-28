#pragma once

#include <string>
#include <functional>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

class PathWalker
{
    const boost::filesystem::path startPath;
    const boost::regex pattern;
public:
    PathWalker(const std::string &startPathName = ".", const boost::regex &pattern = boost::regex(".+\\.txt"));

    void execute(std::function<void(const std::string &)> action) const;
};
