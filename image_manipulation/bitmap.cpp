
#include "bitmap.h"
namespace creatingly {


    bitmap::bitmap(std::string bitmapFilePath){
        _bitmapFilePath=bitmapFilePath;
        _bmpfile=new fileio(_bitmapFilePath);
        _bitmapdata=bitmapdata(_bmpfile);

        bytesPerPixel=_bitmapdata.dib.bitsPerPixel/8;

        paddingSize=0;
        while (((_bitmapdata.dib.width*bytesPerPixel+paddingSize)%4)!=0){
            paddingSize++;
        }

        rowsize=_bitmapdata.dib.width*
                bytesPerPixel+
                paddingSize;
    }

    bitmapdata::Pixel bitmap::GetPixel(int x,int y){
        bitmapdata::Pixel result;
        if(x>=_bitmapdata.dib.width){
            std::cout<<"Error: x is out of range"<<std::endl;
            return result;
        }

        if(y>=_bitmapdata.dib.height){
            std::cout<<"Error: y is out of range"<<std::endl;
            return result;
        }

        auto locationFile = Converxy2Location(x,y);
        result.Blue=_bmpfile->GetbyteAt(locationFile);
        result.Green=_bmpfile->GetbyteAt(locationFile+1);
        result.Red=_bmpfile->GetbyteAt(locationFile+2);
        if(bytesPerPixel>=4){
            result.Alpha=_bmpfile->GetbyteAt(locationFile+3);
        }

        return result;
    }

    void bitmap::SetPixel(int x,int y,bitmapdata::Pixel pixel){
        if(x>=_bitmapdata.dib.width){
            std::cout<<"Error: x is out of range"<<std::endl;
            return;
        }

        if(y>=_bitmapdata.dib.height){
            std::cout<<"Error: y is out of range"<<std::endl;
            return;
        }

        auto locationFile = Converxy2Location(x,y);
        _bmpfile->SetbyteAt(locationFile,pixel.Blue);
        _bmpfile->SetbyteAt(locationFile+1,pixel.Green);
        _bmpfile->SetbyteAt(locationFile+2,pixel.Red);
        if(bytesPerPixel>=4){
            _bmpfile->SetbyteAt(locationFile+3,pixel.Alpha);
        }
    }

    void bitmap::SetPixel(int x,int y,char red, char green,char blue,char alpha){
        if(x>=_bitmapdata.dib.width){
            std::cout<<"Error: x is out of range"<<std::endl;
            return;
        }

        if(y>=_bitmapdata.dib.height){
            std::cout<<"Error: y is out of range"<<std::endl;
            return;
        }

        auto locationFile = Converxy2Location(x,y);
        _bmpfile->SetbyteAt(locationFile,blue);
        _bmpfile->SetbyteAt(locationFile+1,green);
        _bmpfile->SetbyteAt(locationFile+2,red);
        if(bytesPerPixel>=4){
            _bmpfile->SetbyteAt(locationFile+3,alpha);
        }
    }

    void bitmap::SaveAt(std::string saveFilePath){
        _bmpfile->SaveAt(saveFilePath);
    }

}
