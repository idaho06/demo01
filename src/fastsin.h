#pragma once
// #include <iostream>
#include <cmath>
#include <valarray>
class FastSin {
    private:
        std::valarray<float> * floatTable;
        std::valarray<int> * intTable;
        int reduce(const int angle);
        
    public:
        FastSin(const int lenght, const int amplitude);
        int isin(const int angle);
        float fsin(const int angle);
        // float fsin(const float angle);
        ~FastSin();
};

