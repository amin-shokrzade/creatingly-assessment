

#include <string>
#include <regex>
#include <dirent.h>

#ifndef RGB2GRAY_UTILITIES_H
#define RGB2GRAY_UTILITIES_H

namespace creatingly {

    class utilities{

    public:

        static std::string ltrim(const std::string &s);

        static std::string rtrim(const std::string &s);

        static std::string trim(const std::string &s);

        static bool isBitmapFile(const std::string filename);

        static std::vector<std::string> GetDirectoryFiles(const std::string dirPath);
    };
}
#endif //RGB2GRAY_UTILITIES_H
