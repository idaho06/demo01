#include "fastsin.h"
#include <cmath>
#include <valarray>

FastSin::FastSin(const int lenght, const int amplitude){
    floatTable = nullptr;
    intTable = nullptr;
    float pitwo = M_PI*(float)2.0;
    float interval[lenght];
    for(int i = 0; i < lenght; ++i){
        interval[i] = (pitwo/(float)lenght)*(float)i;
    }

    std::valarray<float> varrInterval (interval, lenght);

    std::valarray<float> varrSin = std::sin (varrInterval);

    for(int i = 0; i<lenght; ++i){
        varrSin[i] = varrSin[i]*(float)amplitude;
    }

    this->floatTable = new std::valarray<float>(varrSin);


    std::valarray<int> varriSin((int)0, lenght);
    for(int i = 0; i<lenght; ++i){
        varriSin[i] = (int)std::round(varrSin[i]);
    }

    this->intTable = new std::valarray<int>(varriSin);

    /*
    for(int i = 0; i<lenght; ++i){
        std::cout << " | " << this->intTable->operator[](i);
    }
    */

};

int FastSin::reduce(const int angle){
    int size = this->intTable->size();
    int rangle = angle;
    while(rangle < -size){
        rangle += size;
    }
    while(rangle > size){
        rangle -= size;
    }
    if (rangle<0){
        rangle = size+rangle;
    }
    return rangle;
}



int FastSin::isin(const int angle){
    int rangle = this->reduce(angle);
    return this->intTable->operator[](rangle);
}

float FastSin::fsin(const int angle){
    int rangle = this->reduce(angle);
    return this->floatTable->operator[](rangle);
}

FastSin::~FastSin(){
    if(floatTable != nullptr){
        delete floatTable;
        floatTable = nullptr;
    }
    if(intTable != nullptr){
        delete intTable;
        intTable = nullptr;
    }

};

