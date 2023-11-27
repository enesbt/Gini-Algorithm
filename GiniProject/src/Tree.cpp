#include<Tree.hpp>


Tree::Tree(int rowC,int colC,int targetIndex,vector<vector<float>> data)
{
    this->gini = new Gini(rowC,colC,data);
    this->targetIndex = targetIndex;
}


int Tree::MinGiniIndex(map<int,float> colGini) //min giniye sahip sutun belirlenir
{
    int minKey = -1;
    float minValue = numeric_limits<float>::max();

    for (const auto& pair : colGini) 
    {
        if (pair.second < minValue) {
            minValue = pair.second;
            minKey = pair.first;
        }
    }

    return minKey;
}

bool Tree::Control(vector<vector<float>> dataframe, int index) 
{
    if (dataframe.empty() || index < 0 || index >= dataframe[0].size()) 
    {
        return false;
    }

    float referenceValue = dataframe[0][index];

    for (size_t i = 1; i < dataframe.size(); ++i) {
        if (dataframe[i][index] != referenceValue) {
            return false; // İlgili sütundaki bir değer farklıysa, false döndürür
        }
    }

    return true; // Tüm sütun verileri aynı ise, true döndürür.
}


NodeTree* Tree::Fit(int rowC,int colC,bool leaf,vector<vector<float>> data,int min) //agac olustur
{
    
    if(leaf||data.empty())
    {
        return nullptr;
    }

    NodeTree* node = new NodeTree(min,data[0][min],data);
    if (Control(data, this->targetIndex)) //tum target degerler ayni ise yaprak dugum olur
    {
        node->leaf = true;
        return node;
    }
    
    map<int,float> colGini = gini->GiniCalculate(data,this->targetIndex,rowC,colC); //sutunlarin gini degerleri hesaplanir
    int minCol = MinGiniIndex(colGini); //en kucuk gini degerine sahip sutun belirlenir
    vector<vector<vector<float>>>dataframe = gini->data->GroupBy(data,minCol,rowC,colC); //en kucuk sutuna gore gruplanidirilir

    
    if(dataframe.size()>1)
    {
        node->left = Fit(dataframe[0].size(), dataframe[0][0].size(), false, dataframe[0],minCol);
        node->right = Fit(dataframe[1].size(), dataframe[1][0].size(), false, dataframe[1],minCol);
    }

    return node;
}


float Tree::Score(NodeTree* node,vector<vector<float>>testData)
{
    vector<float> result;
    for (size_t i = 0; i < testData.size(); i++) //tum test satirlari tahmin et ve kaydet
    {
        result.push_back(predict(node,testData[i]));
    }
    float dogru=0;
    float yanlis =0;
    for (size_t i = 0; i < result.size(); i++)
    {
        if(result[i]==testData[i][targetIndex])
            dogru++;
        else
            yanlis++;
    }
    cout<<"dogru: "<<dogru<<endl;
    
    cout<<"yanlis: "<<yanlis<<endl;
    
    float skor = dogru/(dogru+yanlis);

    return skor;
}


float Tree::predict(NodeTree* current,vector<float> inputData)
{
    while (current != nullptr) 
    {
        int currentNodeColumnIndex = current->left->columnIndex; //left right farketmez hangi sutuna gore bolundugu
        
        if (inputData[currentNodeColumnIndex] == current->left->columnValue) //ilerleme
            current = current->left;
        
        else 
            current = current->right;
        

        if (current->leaf||(current->left==NULL&&current->right==NULL)) //yaprak ise sonuc dondur
            return current->data[0][targetIndex];
            
        
    }
    return -1;
}

void Tree::printTreeStructure(NodeTree* node) //agac yazdir levelorder
{

    std::queue<NodeTree*> nodeQueue;
    nodeQueue.push(node);

    while (!nodeQueue.empty()) {
        int levelNodes = nodeQueue.size();

        while (levelNodes > 0) {
            NodeTree* current = nodeQueue.front();
            nodeQueue.pop();

            std::cout << "Sutun: " << current->columnIndex << std::endl
                        << "Column Value: " << current->columnValue << std::endl
                        << "isLeaf: " << current->leaf << std::endl
                        << "target: " << current->data[0][targetIndex] << std::endl;

            if (current->left) {
                nodeQueue.push(current->left);
            }

            if (current->right) {
                nodeQueue.push(current->right);
            }

            levelNodes--;
        }

        cout << endl; // Seviye sonu için bir satır boşluğu
    }

}
