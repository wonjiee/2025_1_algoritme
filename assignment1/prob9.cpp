#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int MAX_SIZE=16;

int N;
int k;
int players[MAX_SIZE][MAX_SIZE];

int playerIndex[16]={0,1,2,3,4,5,6,7,
                     8,9,10,11,12,13,14,15};

vector<vector<int>>combineIndex;


void readFile(string fileName){
    ifstream infile(fileName);
    infile>>N;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            infile>>players[i][j];
    infile>>k;
}

void combineNumbers(int start,int end,vector<int>numbers){
    if(start>=end)
        combineIndex.push_back(numbers);
    else {
        vector<int> insert = numbers;
        insert.push_back(playerIndex[start]);
        combineNumbers(start + 1, end, insert);

        combineNumbers(start + 1, end, numbers);
    }

}

int main(){
    readFile("input9.txt");
    vector<int> number;
    combineNumbers(0,N,number);

    int sum=0;
    int firstSum=0;
    int MaxSum;

    vector<int> bestTeam;

    for(int i=0;i<combineIndex.size();i++){
        sum=0;
        if(combineIndex[i].size()==k) {
            for (int j = 0; j < k; j++)
                for (int q = 0; q < k; q++)
                    sum += players[combineIndex[i][j]][combineIndex[i][q]];
            if(firstSum==0) {
                MaxSum = sum;
                firstSum++;
            }
            else if (sum > MaxSum) {
                MaxSum = sum;
                bestTeam = combineIndex[i];
            }
        }
    }

    cout << MaxSum << endl;
    return 0;

}