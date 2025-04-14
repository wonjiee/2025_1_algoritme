#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE=1000;

int nums[MAX_SIZE];

int find_rank(int num, int start, int end){
    if(start>=end)
        return 0;
    if(num>nums[start])
        return 1+find_rank(num,start+1,end);
    else
        return find_rank(num,start+1,end);
}

int main(){
    int n,num;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    cin>>num;
    cout<<find_rank(num,0,n)+1;



}