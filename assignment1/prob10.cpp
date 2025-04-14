#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Item{
public:
    int itemNumber=0;
    int weight=0;
    int value=0;
    int cost=0;
};

vector<Item>items;
vector<vector<Item>>combineItems;


int N;
int volumeLimit;
int number=0;

void readFile(string name){
    ifstream infile(name);
    infile>>N;
    for(int i=0;i<N;i++) {
        Item tmp;
        tmp.itemNumber=number++;
        infile >> tmp.weight >> tmp.value >> tmp.cost;
        items.push_back(tmp);
    }
    infile>>volumeLimit;
}

void generateItemCombinations(int start, int end, vector<Item>currentItems ){
    if(start>=end)
        combineItems.push_back(currentItems);
    else{
        vector<Item>incert=currentItems;
        currentItems.push_back(items[start]);
        generateItemCombinations(start+1,end,incert);
        generateItemCombinations(start+1,end,currentItems);
    }
}

int findMaxValue(){
    int MaxSumValue=0;
    bool isFirst=true;
    int start = 0;
    int itemWeights = 0;
    int sumItemValues = 0;
    for(int i=0;i<combineItems.size();i++) {
        start = 0;
        itemWeights = 0;
        sumItemValues = 0;
        for (int j = 0; j < items.size(); j++) {
            if ( combineItems[i].size()>0 && j == combineItems[i][start].itemNumber) {
                itemWeights += combineItems[i][start].weight;
                sumItemValues += combineItems[i][start++].value;
            } else
                sumItemValues -= items[j].cost;
        }
        if (isFirst && itemWeights <= volumeLimit) {
            MaxSumValue = sumItemValues;
            isFirst = false;
        }
        else if (itemWeights <= volumeLimit)
            MaxSumValue=(MaxSumValue>sumItemValues?MaxSumValue:sumItemValues);
    }
    return MaxSumValue;
}

int main(){
    readFile("input.txt");
    vector<Item>tmp;
    generateItemCombinations(0,N,tmp);
    cout<<findMaxValue();
    return 0;
}