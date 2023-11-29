


#include "utilities.h"

namespace creatingly {

    std::string utilities::ltrim(const std::string &s) {
        return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
    }

    std::string utilities::rtrim(const std::string &s) {
        return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
    }

    std::string utilities::trim(const std::string &s) {
        return ltrim(rtrim(s));
    }

    bool utilities::isBitmapFile(const std::string filename) {
        return filename.size() >= 4 &&
               filename[filename.size() - 1] == 'p' &&
               filename[filename.size() - 2] == 'm' &&
               filename[filename.size() - 3] == 'b' &&
               filename[filename.size() - 4] == '.';
    }

    std::vector<std::string> utilities::GetDirectoryFiles(const std::string dirPath) {

        std::vector<std::string> result;

        DIR *bitmapsDirectory;

        struct dirent *epdf;

        bitmapsDirectory = opendir(dirPath.c_str());

        if (bitmapsDirectory != NULL) {

            while (epdf = readdir(bitmapsDirectory)) {

                std::string filemname = epdf->d_name;

                if (isBitmapFile(filemname)) {

                    result.push_back(filemname);
                }
            }
        }

        closedir(bitmapsDirectory);

        return result;
    }
}
