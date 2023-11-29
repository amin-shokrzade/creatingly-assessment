#include <iostream>
#include <string>
#include <chrono>
#include "algorithm.h"

using namespace std;

int main(int argc,char** args) {

    string runFilePath=args[1];

    creatingly::algorithm imagealg;

    auto t1 = chrono::high_resolution_clock::now();

    imagealg.Run(runFilePath);

    auto t2 = chrono::high_resolution_clock::now();

    auto s_int =chrono::duration_cast<chrono::seconds>(t2 - t1);

    auto ms_int =chrono::duration_cast<chrono::microseconds>(t2 - t1);

    std::cout <<"Run time = "<< s_int.count() << " seconds or " << ms_int.count() <<" ms"<<std::endl;

    return 0;
}
