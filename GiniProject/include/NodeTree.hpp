#ifndef NODETREE_HPP
#define NODETREE_HPP

#include<iostream>
#include<vector>
using namespace std;


class NodeTree
{
    public:
        NodeTree* left;
        NodeTree* right;
        int columnIndex;   //secilen sutun
        float columnValue;  // secilen sutunun degeri hangi degere gore bolunecegi icin
        vector<vector<float>> data; //satir sutun data
        bool leaf=false; //kok dugum olup olmadigi
        NodeTree(int columnIndex,float columnValue,vector<vector<float>> data,NodeTree*left =nullptr,NodeTree*right=nullptr);
        NodeTree(vector<vector<float>>,NodeTree*left =nullptr,NodeTree*right=nullptr);
        
};

#endif