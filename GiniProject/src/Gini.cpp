#include<Gini.hpp>


Gini::Gini(int rowC,int colC,vector<vector<float>> d)
{
    this->data = new Data(rowC,colC,d);
}


map<int,map<float,int>> Gini::AllColValueCounts(vector<vector<float>> d,int rowC,int colC) //tum sutunların value countlarini dondurur
{
    map<int,map<float,int>> colValueCounts;
    for (size_t i = 0; i < colC; i++)
    {
        map<float,int> col=this->data->ValueCounts(d,i,rowC,colC);
        colValueCounts[i] = col;    
    }
    
    return colValueCounts;
}

map<int,float>Gini::GiniCalculate(vector<vector<float>> d,int targetIndex,int rowC,int colC) //sutunlarin gini degerleri maplenir
{
    map<int,map<float,int>> colValueCounts = AllColValueCounts(d,rowC,colC);
    vector<vector<vector<float>>>dataframe = data->GroupBy(d,targetIndex,rowC,colC);

     

    float karelerToplam=0;
    map<int,float> colGini; //key=sutun value = ginidegeri
    for (int i = 0; i < dataframe[0][0].size()-1; i++) //sutun sayisi
    {
        float gini =0;
        float ginileftright;
        for (const auto& pair : colValueCounts[i])  //sutunlarin key sayisi
        {
            int key = pair.first; //key
            //cout << "Anahtar: " << key <<endl;
            float keyTotal = colValueCounts[i][key];  //1.parametre sutun  2.parametre key degeri
            for (int k = 0; k < dataframe.size(); k++)  //layer sayisi
            {
                map<float, int> col;
                col = data->ValueCounts(dataframe[k], i, dataframe[k].size(), dataframe[k][0].size());
                //cout<<"col[key]/keyTotal:"<<col[key]<<"/"<<keyTotal<<endl;
                if(col[key]==0)
                    ginileftright =0;
                                    
                else
                {
                    float kare = pow(col[key]/keyTotal,2);  //col[0] 0=key
                    //cout<<"kare: "<<kare<<endl;
                    karelerToplam +=kare;
                    //cout<<"kare toplami: "<<karelerToplam<<endl;
                    
                }
                //cout<<"layer bitti"<<endl;
            }
            
            ginileftright = 1-karelerToplam;
            gini += ginileftright*keyTotal;  //kat sayi
            karelerToplam = 0;
            //cout<<"key bitti"<<endl;
        }
        gini /=rowC; //row size
        colGini[i] = gini;
        //cout<<"sutun bitti"<<endl;
    }
    
    return colGini;
}

Gini::~Gini()
{
    delete data;
}