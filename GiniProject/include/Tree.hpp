#ifndef TREE_HPP
#define TREE_HPP
#include "NodeTree.hpp"
#include "Gini.hpp"
#include "Data.hpp"
#include <limits>
#include"queue"

class Tree
{
    public:
        Gini* gini;
        int targetIndex;
        Tree(int,int,int,vector<vector<float>>);
        NodeTree* Fit(int,int,bool,vector<vector<float>>,int); //agaci olustur
        int MinGiniIndex( map<int,float>);
        bool Control(vector<vector<float>> dataframe, int index);
        void printTreeStructure(NodeTree*);
        float predict(NodeTree*,vector<float>);
        float Score(NodeTree*,vector<vector<float>>);

};
#endif