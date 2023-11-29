


#include "bitmap.h"
#include <vector>
#include <mutex>
#include <thread>
#ifndef RGB2GRAY_BMPBUFFER_H
#define RGB2GRAY_BMPBUFFER_H


namespace creatingly{

    class bmpbuffer{

    public:

        struct bitmapCell{

        public:

            int index=0;
            bool isBuffered= false;
            bool isprocessing= false;
            std::string filename;
            bitmap *bmp= nullptr;

            bitmapCell(){}
        };

        bmpbuffer(void){}

        bmpbuffer(const int size,const std::string filesPath,const std::string savePath, const std::vector<std::string> files);

        void Start(void);

        void Loader(void);

        bitmapCell* GetNext(void);

        void FreeCell(const int cellIndex);

        void SaveAndFreeCell(const int cellIndex);

        bool HasAny(void);

    private:

        int fileCounter=0;

        std::vector<bitmapCell> cells;

        std::vector<std::string> _files;

        std::string _filesPath;

        std::string _savePath;

        int _bufferSize=0;

        void UpdateCell(const int cellIndex,const bool clean,const bool setProcess,const bool bitmapFile);

    };
}


#endif //RGB2GRAY_BMPBUFFER_H
