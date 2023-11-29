#include "algorithm.h"

namespace creatingly {

    void algorithm::ParseRunFile(const std::string runFilePath) {

        std::fstream fileReader(runFilePath, std::ios_base::in);

        std::string line;

        while (!fileReader.eof()) {

            std::getline(fileReader, line);

            if (line.empty()) continue;

            if (line.rfind("InputPath:") == 0) {
                _inputPath = utilities::trim(line.substr(10, line.size() - 10));
            } else if (line.rfind("OutputPath:") == 0) {
                _outputPath = utilities::trim(line.substr(11, line.size() - 11));
            } else if (line.rfind("Algorithm:") == 0) {
                _algorithm = utilities::trim(line.substr(10, line.size() - 10));
            }else if (line.rfind("SaveResults:") == 0) {
                _saveResults = utilities::trim(line.substr(12, line.size() - 12));
            }
        }

        fileReader.close();
    }

    void algorithm::Engine(const int index) {
        while (bitmapsBuff.HasAny()) {
            getNextBitmap.lock();
            auto bitmapObject=bitmapsBuff.GetNext();
            getNextBitmap.unlock();
            if(bitmapObject== nullptr) {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                continue;
            }
            if (_algorithm == "rgb2gray") {
                rgb2gray(bitmapObject->bmp);
            }
            else if (_algorithm == "rgb2bin") {
                rgb2bin(bitmapObject->bmp);
            }
            freeBufferCell.lock();
            if(_saveResults.size()>0 && _saveResults=="Yes") {
                bitmapsBuff.SaveAndFreeCell(bitmapObject->index);
            }
            else {
                bitmapsBuff.FreeCell(bitmapObject->index);
            }
            freeBufferCell.unlock();
        }
        threadsPool[index]= false;
    }

    bool algorithm::IsRunningThread(void){
        for(const auto thread:threadsPool){
            if(thread){
                return true;
            }
        }
        return false;
    }

    void algorithm::rgb2gray(bitmap *bmp) {

        register int h = bmp->Height();

        register int w = bmp->Width();

        for ( int j = 0; j < h; ++j) {

            for ( int i = 0; i < w; ++i) {

                auto pixel = bmp->GetPixel(i, j);

                auto color = (char) ((pixel.Red + pixel.Green + pixel.Blue) / 3);

                bmp->SetPixel(i, j, color, color, color);
            }
        }
    }

    void algorithm::rgb2bin(bitmap *bmp) {

        register int h = bmp->Height();

        register int w = bmp->Width();

        for ( int j = 0; j < h; ++j) {

            for ( int i = 0; i < w; ++i) {

                auto pixel = bmp->GetPixel(i, j);

                auto color = (char) ((pixel.Red + pixel.Green + pixel.Blue) / 3);

                color=color>70?255:0;

                bmp->SetPixel(i, j, color, color, color);
            }
        }
    }

    void algorithm::Run(const std::string runFilePath) {

        _inputPath = "";

        _outputPath = "";

        _algorithm = "";

        _saveResults="";

        ParseRunFile(runFilePath);

        if (_inputPath.empty() || _outputPath.empty() || _algorithm.empty()) {

            std::cout << "Invalid run file";
            return;
        }

        auto bitmapFiles = utilities::GetDirectoryFiles(_inputPath);

        std::thread(&algorithm::Processor,this,bitmapFiles).join();
    }

    void algorithm::Processor(const std::vector<std::string> bitmapFiles){

        int parallelCount=std::thread::hardware_concurrency()+2;

        threadsPool=std::vector<bool>(parallelCount,true);

        bitmapsBuff = bmpbuffer(parallelCount*2,_inputPath,_outputPath,bitmapFiles);

        bitmapsBuff.Start();

        for(int i=0; i<parallelCount; ++i){
            std::thread(& algorithm::Engine,this,i).detach();
        }

        while (IsRunningThread()){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

}
