#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Knapsack{
public:
    int weight=0;
    int value=0;
};

Knapsack originKnapsacks[16];
Knapsack allKnapsacks[65536];
int currentAmount=0;

int N,maxCapacity;


void readFile(string name){
    ifstream infile(name);
    infile>>N>>maxCapacity;
    for(int i=0;i<N;i++){
        infile>>originKnapsacks[i].weight;
    }
    for(int j=0;j<N;j++){
        infile>>originKnapsacks[j].value;
    }

}

void fillKnapsack(int start,int end,Knapsack knapsack){
    if(start>=end) {
        allKnapsacks[currentAmount++] = knapsack;
        return;
    }
    else{
        Knapsack include = knapsack;
        include.weight+=originKnapsacks[start].weight;
        include.value+=originKnapsacks[start].value;
        fillKnapsack(start+1,end,include);

        fillKnapsack(start+1,end,knapsack);
    }
}

int main(){
    readFile("input.txt");
    Knapsack knap,maxKnap;
    fillKnapsack(0,N,knap);
    for(int i=0;i<currentAmount;i++) {
        if (allKnapsacks[i].weight <= maxCapacity && allKnapsacks[i].value > maxKnap.value)
            maxKnap.value = allKnapsacks[i].value;
    }
    cout<<maxKnap.value;
    return 0;

}
