#include <iostream>
#include <string>

using namespace std;

const int MAX_SIZE=65536;

string binarySecuences[MAX_SIZE];
int currentCapacity=0;

void generateBinarySecuences(string secuence,int n){
    if(n==1) {
        binarySecuences[currentCapacity++] = secuence + "0";
        binarySecuences[currentCapacity++] = secuence + "1";
    }
    else {
        binarySecuences[currentCapacity++] = secuence + "0";
        binarySecuences[currentCapacity++] = secuence + "1";
        generateBinarySecuences(secuence + "0", n - 1);
        generateBinarySecuences(secuence + "1", n - 1);
    }
}

bool noConsecutiveZero(string secuence,char previousNum,int start,int end){
    if(start>=end)
        return true;
    else if(secuence[start]=='0' && previousNum=='0')
        return false;
    else
        return noConsecutiveZero(secuence, secuence[start],start+1,end);
}

int main() {
    int n;
    cin >> n;
    generateBinarySecuences("", n);

    int count = 0;
    for (int i = 0; i < currentCapacity; i++)
        if (binarySecuences[i].length()==n && noConsecutiveZero(binarySecuences[i], ' ', 0, binarySecuences[i].length()))
            count++;
    cout<<count;
    return 0;
}