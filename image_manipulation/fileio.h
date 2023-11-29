


#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

#ifndef RGB2GRAY_FILEIO_H
#define RGB2GRAY_FILEIO_H

namespace creatingly {

    class fileio{

    private:

        std::string _filePath="";

        char * _filebuffer= nullptr;

        long long _buffersize=0;

        long long _seekCounter=0;

        inline bool isInRange(const long long index) const{
            return (index>=0 && index<_buffersize);
        }

        inline bool isNotInRange(const long long index) const{
            return (index<0 || index>=_buffersize);
        }

        inline void Increament(void){
            if(_seekCounter<_buffersize){
                _seekCounter++;
            }
        }

        inline void Decreament(void){
            if(_seekCounter>0){
                _seekCounter--;
            }
        }

    public:

        fileio();

        ~fileio();

        fileio(const std::string filePath);

        bool Exists(void);

        long long Size(void);

        void Reload(void);

        char * GetAllBytes(void);

        char GetbyteAt(const long long index) ;

        void SetbyteAt(const long long index,const char value) ;

        short GetWordAt(const long long index,const bool reverse= false) const ;

        int GetDWordAt(const long long index,const bool reverse=false) const;

        char * GetBytes(const long long start,const long long length);

        char GetNextByte(void);

        char GetPreviousByte(void);

        void Save(void);

        void SaveAt(const std::string saveFilePath);

        void SeekTo(const long long index);

        bool endOfFile(void);

        fileio& operator++(void);

        fileio& operator--(void);
    };

}


#endif //RGB2GRAY_FILEIO_H
