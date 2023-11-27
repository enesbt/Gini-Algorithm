#ifndef DATA_HPP
#define DATA_HPP
#include <iostream>
#include <vector>
#include <map>
#include "random"

using namespace std;

class Data
{
    public:
        int rowCount;
        int colCount;
        vector<vector<float>> data; //row and column
        Data();
        Data(int,int,vector<vector<float>>); //create data 2d array
        vector<float> GetColumn(int); //input column index return column all row
        map<float,int> ValueCounts(vector<vector<float>>,int,int,int); //input column index return         
        vector<vector<vector<float>>> GroupBy(vector<vector<float>>,int,int,int);  //group by column and return rows 3d vector 1.layer 2.row 3.column
        vector<vector<vector<float>>> TrainTestSplit(vector<vector<float>>,float);
        ~Data();


};
#endif