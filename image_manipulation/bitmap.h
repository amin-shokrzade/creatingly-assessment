

#include <iostream>
#include <string>
#include "bitmapdata.h"

#ifndef RGB2GRAY_BITMAP_H
#define RGB2GRAY_BITMAP_H

namespace creatingly{
    class bitmap{

    private:

        int rowsize=0;

        std::string _bitmapFilePath;

        bitmapdata  _bitmapdata;

        fileio      *_bmpfile;

        int         bytesPerPixel=0;

        int         paddingSize=0;

        inline bool isTopDown(){
            return _bitmapdata.dib.height<0;
        }

        inline bool isBottonTop(){
            return _bitmapdata.dib.height>0;
        }

        inline int Converxy2Location(const int x,const int y){

            auto locationFile=0;

            if(isBottonTop()) {
                locationFile =
                        _bitmapdata.header.offset +
                        (_bitmapdata.dib.height - y - 1) *
                        rowsize +
                        (x * bytesPerPixel);
            } else{
                locationFile =
                        _bitmapdata.header.offset +
                        (y * rowsize) +
                        (x * bytesPerPixel);
            }
            return locationFile;
        }

    public:

        ~bitmap(){
            _bmpfile->~fileio();
        }

        bitmap(std::string bitmapFilePath);

        bitmap(){};

        bitmapdata::Pixel GetPixel(int x,int y);

        void SetPixel(int x,int y,bitmapdata::Pixel pixel);

        void SetPixel(int x,int y,char red, char green,char blue,char alpha=0);

        void SaveAt(std::string saveFilePath);

        inline int Width(){
            return _bitmapdata.dib.width;
        }

        inline int Height(){
            return _bitmapdata.dib.height;
        }
    };
}


#endif //RGB2GRAY_BITMAP_H
