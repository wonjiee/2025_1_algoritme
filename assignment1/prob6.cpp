#include <iostream>

using namespace std;

const int MAX_SIZE=20;

int num[MAX_SIZE];
int n;

void readSequence(){
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>num[i];
}

bool canSuccess(int current){
    if(current==n-1)
        return true;
    else if(current<0 || current>=n || num[current]==0)
        return false;
    else{
        int trialNum=num[current];
        for(int i=1;i<=trialNum;i++)
            if(canSuccess(current + i))
                return true;
    }
    return false;
}
int main(){
    readSequence();
    if(canSuccess(0))
        cout<<"Yes";
    else
        cout<<"No";
    return 0;
}
