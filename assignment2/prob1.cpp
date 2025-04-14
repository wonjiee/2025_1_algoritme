#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

vector<string>words; // 입력 파일에서 읽은 단어 전체
vector<string>originWords; // 원본 복사본
vector<string>sortedWords; // 정렬 대상 벡터

void readFile(string title){
    string word;
    ifstream infile(title);
    while(infile>>word)
        words.push_back(word);
    originWords=words;
    sortedWords=words;
}

void checkTime(clock_t start,string sortName){
    clock_t finish=clock();
    double duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout<<sortName<<": "<<duration<<endl;
}

void arrClear(){
    words.clear();
    sortedWords=originWords;
}

void startBubbleSort(){
    for(int i=0;i<sortedWords.size()-1;i++) {
        for (int j = i + 1; j < sortedWords.size(); j++)
            if (sortedWords[i] > sortedWords[j])
                swap(sortedWords[i], sortedWords[j]);
    }

}

void startInsertionSort(){
    for(int i=1;i<sortedWords.size();i++){
        string key=sortedWords[i];
        int j=i-1;
        while(j>=0 && sortedWords[j]>key){
            sortedWords[j+1]=sortedWords[j];
            j--;
        }
        sortedWords[j+1]=key;
    }
}

void merge(vector<string>&arr,int start,int middle,int end){
    vector<string>mergeArr;
    int i=start;
    int j=middle+1;
    while(i<=middle && j <= end) {
        if (arr[i] < arr[j])
            mergeArr.push_back(arr[i++]);
        else
            mergeArr.push_back(arr[j++]);
    }

    while(i<=middle)
        mergeArr.push_back(arr[i++]);
    while(j<=end)
        mergeArr.push_back(arr[j++]);

    for(int k=0;k<mergeArr.size();k++)
        arr[start+k]=mergeArr[k];

}

void startMergeSort(vector<string>&arr,int start,int end){
    if(start<end) {
        int middle = (start + end) / 2;
        startMergeSort(arr,start, middle);
        startMergeSort(arr,middle + 1, end);
        merge(arr,start,middle,end);
    }
}

int partition(vector<string>&arr,int start, int end){
    int pivotIdx = start + rand() % (end - start + 1);
    swap(arr[pivotIdx], arr[end]);

    string pivot=arr[end];
    int i=start-1;
    for(int j=start;j<end;j++){
        if(arr[j]<= pivot){
            i+=1;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[end]);
    return i+1;
}
void startQuickSort(vector<string>&arr,int start, int end){
    if(start<end){
        int pivotIdx=partition(arr,start,end);
        startQuickSort(arr,start,pivotIdx-1);
        startQuickSort(arr,pivotIdx+1,end);
    }
}

void maxHeapify(vector<string>&arr,int i,int heapSize){
    if(i*2+1>=heapSize)
        return;
    int k;
    if(i*2+2>=heapSize)
        k=i*2+1;
    else
        k=(arr[2*i+1]>arr[2*i+2]?2*i+1:2*i+2);
    if(arr[i]>arr[k])
        return;
    swap(arr[i],arr[k]);
    maxHeapify(arr,k,heapSize);

}

void startHeapSort(vector<string>&arr){
    int heapSize=arr.size();
    for(int i=arr.size()/2-1;i>=0;i--){
        maxHeapify(arr,i,heapSize);
    }
    for(int i=heapSize-1;i>0;i--){
        swap(arr[i],arr[0]);
        maxHeapify(arr,0,i);
    }
}



int main(){
    clock_t start;

    readFile("harry_full.txt");

    start=clock();
    startBubbleSort();
    checkTime(start,"bubble sort");
    arrClear();

    start=clock();
    startInsertionSort();
    checkTime(start,"insertion sort");
    arrClear();

    start=clock();
    startMergeSort(words,0,sortedWords.size()-1);
    checkTime(start,"merge sort");
    arrClear();

    start=clock();
    startQuickSort(words,0,sortedWords.size()-1);
    checkTime(start,"quick sort");
    arrClear();

    start=clock();
    startHeapSort(sortedWords);
    checkTime(start,"heap sort");
    arrClear();

    start=clock();
    sort(sortedWords.begin(), sortedWords.end());
    checkTime(start,"STL sort");
    arrClear();

    return 0;

}