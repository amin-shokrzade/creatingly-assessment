

#include "bmpbuffer.h"

namespace creatingly {

    bmpbuffer::bmpbuffer(const int size,const std::string filesPath,const std::string savePath, const std::vector<std::string> files){
        _filesPath=filesPath;

        _savePath=savePath;

        _bufferSize=size;

        for(auto file:files){
            _files.push_back(file);
        }

        cells=std::vector<bitmapCell>(size);

        for(int i=0; i<cells.size() && fileCounter<_files.size(); ++i){
            cells[i].index=i;
            cells[i].filename=_files[fileCounter];
            cells[i].bmp=new bitmap(_filesPath+'\\'+cells[i].filename);
            cells[i].isBuffered= true;
            cells[i].isprocessing= false;
            fileCounter++;
        }
    }

    void bmpbuffer::Start(void){
        std::thread(&bmpbuffer::Loader,this).detach();
    }

    void bmpbuffer::Loader(void){
        while (fileCounter<bmpbuffer::_files.size()) {
            for (int i = 0; i < _bufferSize && fileCounter < bmpbuffer::_files.size(); ++i) {
                if (cells[i].isBuffered == false) {
                    bmpbuffer::UpdateCell(i, false, false, true);
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }

    bmpbuffer::bitmapCell* bmpbuffer::GetNext(void){

        int index=-1;
        for(int i=0; i<_bufferSize; ++i){
            if(cells[i].isBuffered && cells[i].isprocessing== false){
                UpdateCell(i,false,true, false);
                index=i;
                break;
            }
        }
        if(index!=-1) {
            return &cells[index];
        }
        return nullptr;
    }

    void bmpbuffer::FreeCell(const int cellIndex){
        UpdateCell(cellIndex,true, false, false);
    }

    void bmpbuffer::SaveAndFreeCell(const int cellIndex){
        cells[cellIndex].bmp->SaveAt(_savePath+'\\'+cells[cellIndex].filename);
        UpdateCell(cellIndex, true ,false, false);
    }

    bool bmpbuffer::HasAny(void){
        if(fileCounter<_files.size())
        {
            return true;
        }
        for(int i=0; i<_bufferSize; ++i){
            if(cells[i].isBuffered)
            {
                return true;
            }
        }
        return false;
    }

    void bmpbuffer::UpdateCell(const int cellIndex,const bool clean,const bool setProcess,const bool bitmapFile){

        if (clean){
            cells[cellIndex].bmp->~bitmap();
            cells[cellIndex].filename="";
            cells[cellIndex].isprocessing = false;
            cells[cellIndex].isBuffered = false;
        }
        else if (setProcess)
        {
            cells[cellIndex].isprocessing= true;
        }
        else if (bitmapFile)
        {
            cells[cellIndex].filename = _files[fileCounter];
            cells[cellIndex].bmp = new bitmap(_filesPath + '\\' + cells[cellIndex].filename);
            cells[cellIndex].isprocessing = false;
            cells[cellIndex].isBuffered = true;
            fileCounter++;
        }
    }

}
