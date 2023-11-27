#include<Data.hpp>
#include<Gini.hpp>
#include<Tree.hpp>
#include<cmath>
#include<fstream>
#include<string>
#include<sstream>
#include <ctime>
using namespace std;




int main()
{
    system("cls");
    srand(time(0));
    vector<vector<float>> data;
    vector<float> lineVector;

    fstream file;
    int sayi;
    string satir;
    file.open("veri.txt",ios::in);
    if(file.is_open()) //veri okuma
    {
        while(getline(file,satir))
        {
            stringstream ss(satir);
            while(ss>>sayi)
            {
                lineVector.push_back(sayi);
            }
            data.push_back(lineVector);
            lineVector.clear();
        }
    }

    file.close();



    Data* d = new Data();

    vector<vector<vector<float>>>train_test_data;
    train_test_data = d->TrainTestSplit(data,0.2); //[0]:Train [1]:test
    vector<vector<float>>trainData = train_test_data[0];
    vector<vector<float>>testData = train_test_data[1];

    Tree* tree = new Tree(trainData.size(),trainData[0].size(),trainData[0].size()-1,trainData); //row,col,target col,data
    
    //egitim
    NodeTree* root = tree->Fit(trainData.size(),trainData[0].size(),false,trainData,0); //row,col,isleaf=false,data,min col:baslangic icin 0 bir degeri yok
   
    //agac yazdirma
    //tree->printTreeStructure(root);
    
    float skor=tree->Score(root,testData);
    cout<<"skor: "<<skor<<endl;
   

    return 0;
    
}



