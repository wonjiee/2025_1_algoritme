#include <iostream>
#include <cmath>

using namespace std;

const int MAX_SIZE=1000;
int nums[MAX_SIZE];

int nearest(int num, int start, int end,int result){
    if(start>end)
        return result;
    int current=(start+end)/2;
    int diff=nums[current]-num;

    if(diff==0)
        return nums[current];

    int absDiffCurrent = abs(diff);
    int absDiffResult = abs(num-result);
    if(absDiffCurrent<absDiffResult || (absDiffCurrent==absDiffResult && nums[current]<result))
        result=nums[current];

    if(diff>0)
        return nearest(num,start,current-1,result);
    else
        return nearest(num,current+1,end,result);
}

int main(){
    int n,num;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    cin>>num;
    cout<<nearest(num,0,n-1,nums[0]);
}