

#include "bmpbuffer.h"
#include "bitmap.h"
#include "utilities.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

#ifndef RGB2GRAY_ALGORITHM_H
#define RGB2GRAY_ALGORITHM_H

namespace creatingly {

    class algorithm {

    private:

        std::string _inputPath;

        std::string _outputPath;

        std::string _algorithm;

        std::string _saveResults;

        std::vector<bool> threadsPool;

        bmpbuffer bitmapsBuff;

        std::mutex getNextBitmap,freeBufferCell;

        void ParseRunFile(const std::string runFilePath);

        void Engine(const int index);

        bool IsRunningThread(void);

        void rgb2gray(bitmap *bmp);

        void rgb2bin(bitmap *bmp);

    public:

        void Run(const std::string runFilePath);

        void Processor(const std::vector<std::string> bitmapFiles);
    };
}

#endif //RGB2GRAY_ALGORITHM_H
