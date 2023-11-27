#include"NodeTree.hpp"

NodeTree::NodeTree(int columnIndex,float columnValue,vector<vector<float>> data,NodeTree*left,NodeTree*right)
{
    this->columnIndex = columnIndex;
    this->columnValue = columnValue;
    this->data = data;
    this->left = left;
    this->right = right;
    this->leaf = false;
}

NodeTree::NodeTree(vector<vector<float>>data,NodeTree*left,NodeTree*right)
{
    this->data = data;
    this->left = left;
    this->right = right;
}
