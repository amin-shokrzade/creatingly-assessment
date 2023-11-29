

#include "fileio.h"

namespace creatingly {


    fileio::fileio(void) {
        _filebuffer= nullptr;
        _buffersize=0;
        _seekCounter=0;
        _filePath="";
    }

    fileio::~fileio(void) {
        if (_filebuffer != nullptr) {
            free(_filebuffer);
        }
    }

    fileio::fileio(const std::string filePath) {
        _filePath = filePath;
        Reload();
    }

    bool fileio::Exists(void) {
        auto f = fopen(_filePath.c_str(), "r");
        if (f == nullptr) {
            return false;
        }
        fclose(f);
        return true;
    }

    long long fileio::Size(void) {
        std::ifstream fileReader(_filePath.c_str(), std::ifstream::ate | std::ifstream::binary);
        auto fileSize = fileReader.tellg();
        fileReader.close();
        return fileSize;
    }

    char *fileio::GetAllBytes(void) {

        if (_filebuffer != nullptr) {
            return _filebuffer;
        }

        Reload();

        return _filebuffer;
    }

    void fileio::Reload(void) {

        if (Exists() == false) {
            std::cout << "File does not exists/not accessible at " << _filePath << std::endl;
            return;
        }

        _buffersize = Size();

        if (_filebuffer != nullptr) {
            free(_filebuffer);
        }

        _filebuffer = new char[_buffersize];

        std::ifstream fileReader(_filePath, std::ios_base::in | std::ios_base::binary);

        fileReader.read(_filebuffer, _buffersize);

        if (!fileReader) {
            std::cout << "Error reading file" << std::endl;
        }

        fileReader.close();
    }

    char fileio::GetbyteAt(const long long index)  {

        if (isNotInRange(index)) {
            std::cout << "char index is out of range" << std::endl;
            return 0;
        }
        return _filebuffer[index];
    }

    void fileio::SetbyteAt(const long long index, const char value)  {

        if (isNotInRange(index)) {
            std::cout << "char index is out of range" << std::endl;
            return;
        }

        _filebuffer[index] = value;
    }

    void fileio::Save(void) {
        auto fileWriter = std::fstream(_filePath, std::ios_base::binary);
        fileWriter.write((char *) _filebuffer, _buffersize);
        fileWriter.close();
    }

    void fileio::SaveAt(const std::string saveFilePath) {
        auto fileWriter = std::fstream(saveFilePath, std::ios_base::out | std::ios_base::binary);
        fileWriter.write(_filebuffer, _buffersize);
        fileWriter.close();
    }

    fileio &fileio::operator++(void) {
        Increament();
        return *this;
    }

    fileio &fileio::operator--(void) {
        Decreament();
        return *this;
    }

    char fileio::GetNextByte(void) {
        if (endOfFile()) {
            std::cout << "Seek reached EOF" << std::endl;
            return 0;
        }
        Increament();
        return _filebuffer[_seekCounter - 1];
    }

    char fileio::GetPreviousByte(void) {
        if (_seekCounter <= 0) {
            std::cout << "Seek reached BOF" << std::endl;
            return 0;
        }
        Decreament();
        return _filebuffer[_seekCounter + 1];
    }

    bool fileio::endOfFile(void) {
        return _seekCounter >= _buffersize;
    }

    void fileio::SeekTo(const long long index) {
        if (isNotInRange(index)) {
            std::cout << "Seek index is out of range" << std::endl;
            return;
        }
        _seekCounter = index;
    }

    short fileio::GetWordAt(const long long index, const bool reverse)const  {

        if (isNotInRange(index)) {
            std::cout << "word index is out of range" << std::endl;
            return 0;
        }

        char a = _filebuffer[index];

        char b = (index + 1 < _buffersize) ? _filebuffer[index + 1] : 0;

        if (reverse) {
            return (((short) b) << 8) | (0x00ff & a);
        } else {
            return (((short) a) << 8) | (0x00ff & b);
        }
    }

    int fileio::GetDWordAt(const long long index, const bool reverse)  const{

        if (isNotInRange(index)) {
            std::cout << "word index is out of range" << std::endl;
            return 0;
        }
        char a = _filebuffer[index];
        char b = (index + 1 < _buffersize) ? _filebuffer[index + 1] : 0;
        char c = (index + 2 < _buffersize) ? _filebuffer[index + 2] : 0;
        char d = (index + 3 < _buffersize) ? _filebuffer[index + 3] : 0;
        if (reverse) {
            return (unsigned char) (d) << 24 |
                   (unsigned char) (c) << 16 |
                   (unsigned char) (b) << 8 |
                   (unsigned char) (a);
        } else {
            return (unsigned char) (a) << 24 |
                   (unsigned char) (b) << 16 |
                   (unsigned char) (c) << 8 |
                   (unsigned char) (d);
        }
    }

    char *fileio::GetBytes(const long long start, const long long length) {
        char *result = new char[length];
        for (int i = 0; i < length; ++i) {
            result[i] = start + i;
        }
        return result;
    }

}
