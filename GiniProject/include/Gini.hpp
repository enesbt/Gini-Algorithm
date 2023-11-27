#ifndef GINI_HPP
#define GINI_HPP
#include <iostream>
#include "Data.hpp"
#include<cmath>


using namespace std;

class Gini
{
    
    public:
        Data* data;
        Gini(int rowC,int colC,vector<vector<float>> d);
        map<int,map<float,int>> AllColValueCounts(vector<vector<float>> d,int rowC,int colC);
        map<int,float>GiniCalculate(vector<vector<float>> d,int targetIndex,int rowC,int colC);   //1.parametre data ,2.parametre hedef degisken col indexi
        ~Gini();

};
#endif
