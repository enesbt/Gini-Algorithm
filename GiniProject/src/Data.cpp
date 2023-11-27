#include <Data.hpp>

Data::Data(int rowCount,int colCount,vector<vector<float>>data)
{
    this->rowCount = rowCount;
    this->colCount = colCount;
    this->data = data;
}

Data::Data()
{
    
}
vector<float> Data::GetColumn(int index) //get column data vector
{
    vector<float> col;
    for (size_t i = 0; i < rowCount; i++)
    {
        col.push_back(data[i][index]);
    }
    return col;
}

map<float,int> Data::ValueCounts(vector<vector<float>>dataframe,int colIndex,int rowC,int colC) 
{
    map<float,int> columnValueCounts;

    for (int j = 0; j < rowC; j++) {
        float value = dataframe[j][colIndex];
        columnValueCounts[value]++;
    }

    if (columnValueCounts.size()<4) // categoric value count
        return columnValueCounts;

    else  //numeric value count
    {
        columnValueCounts.clear();
        float sum =0;
        float mean = 0;
        for (size_t i = 0; i < rowC; i++)
        {
            sum += dataframe[i][colIndex];
        }
        mean = sum / rowC;
        for (size_t i = 0; i < rowC; i++)
        {
            if(dataframe[i][colIndex]>mean)    // > mean
                columnValueCounts[mean]++;
            else                    // <= mean
                columnValueCounts[mean-1]++;
            
        }
        return columnValueCounts;
    }
    

    return columnValueCounts;
}


vector<vector<vector<float>>> Data::GroupBy(vector<vector<float>>dataf,int colindex,int rowC,int colC) //verilen sutuna gore satirlari ayirir key sayisi kadar 2d dizi olusturur ve  bunlari 3d dizide saklar
{
    vector<vector<vector<float>>> dataframe;

    if (dataf.size() == 2) 
    {
        dataframe.push_back({dataf[0]});
        dataframe.push_back({dataf[1]});
    }
    else
    {
        map<float,int> target_values; //value ,count
        target_values = ValueCounts(dataf,colindex,rowC,colC); //map 

        map<float, int>::iterator it = target_values.begin();
        vector<float> targetKeys;

        while (it != target_values.end()) // value count
        {        
            targetKeys.push_back(it->first);  
            it++;     
        }

        // float sum =0;
        // float mean = 0;
        // for (size_t i = 0; i < rowC; i++)
        // {
        //     sum += dataf[i][colindex];
        // }
        // mean = sum / rowC;
        // if(mean>2)
        // {
            
        //     for (size_t j = 0; j < rowC; j++)
        //     {
        //         if(dataf[j][colindex]>mean)
        //             dataf[j][colindex] = mean;
        //         else
        //             dataf[j][colindex] = mean-1;

        //     }
        // }

        
        for (size_t i = 0; i < targetKeys.size(); i++) //key sayisi
        {
            vector<vector<float>>newData;
            for (size_t j = 0; j < rowC; j++)
            {           
                vector<float>row;
                if(dataf[j][colindex]==targetKeys[i])
                {
                    for (size_t k= 0; k< colC; k++)
                    {
                        row.push_back(dataf[j][k]);      
                    }
                }
                // for (size_t k= 0; k< colC; k++)
                // {
                //     if(data[j][colindex]==targetKeys[i])
                //         row.push_back(data[j][k]);      
                // }
                if(!row.empty())
                    newData.push_back(row);
                row.clear();
            }
            if (!newData.empty())
                dataframe.push_back(newData);
            newData.clear();
        }
    }

    
    return dataframe;
}


vector<vector<vector<float>>> Data::TrainTestSplit(vector<vector<float>>data,float testSize)
{
    vector<vector<float>> train;
    vector<vector<float>> test;
    vector<vector<vector<float>>> result;
    vector<int>selectedRowsArray;
    int maxNumber = data.size();
    int selectedRows = maxNumber*testSize; //secilecek satir sayisi
    //cout<<"selectedRows: "<<selectedRows<<endl;
    while (selectedRows>0) //secilecek satir sayisi kadar 
    {
        int randomRow = rand()%maxNumber;
        selectedRowsArray.push_back(randomRow); //secilen indisi diziye ekle
        test.push_back(data[randomRow]);  //test datasına ekle
        selectedRows--;
    }
    
    for (size_t i = 0; i < selectedRowsArray.size(); i++) //test icin secilen satirlari cikar
    {
        data.erase(data.begin()+selectedRowsArray[i]);
    }
    
    
    
    for (size_t i = 0; i < data.size(); i++) //kalan satirlari traine ekle
    {
        train.push_back(data[i]);
    }
    
    
    result.push_back(train);
    result.push_back(test);
    return result;

}


Data::~Data()
{

}