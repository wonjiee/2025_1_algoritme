#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

class ArrayMaxHeap{
private:
    vector<int>arr;
public:
    int findMaxIdx(){
        int maxIdx=0;
        for(int i=0;i<arr.size();i++)
            if(arr[i]>arr[maxIdx])
                maxIdx=i;
        return maxIdx;
    }

    void add(int n){
        arr.push_back(n);
    }

    void extractMax(){
        int i=findMaxIdx();
        arr[i]=arr[arr.size()-1];
        arr.pop_back();
    }

    bool empty(){
        return arr.empty();
    }
};

class MaxHeap{
private:
    vector<int>arr;
public:
    void maxHeapify(int i,int heapSize){
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
        maxHeapify(k,heapSize);
    }
    void add(int n) {
        arr.push_back(n);
        int i = arr.size() - 1;
        while (i > 0 && arr[i] > arr[(i - 1) / 2]) {
            swap(arr[i], arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    void extractMax() {
        if (arr.empty()) return;
        swap(arr[0], arr[arr.size() - 1]);
        arr.pop_back();
        maxHeapify(0, arr.size());
    }

    bool empty(){
        return arr.empty();
    }
};

int randNum(int n){
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(0,n-1);

    return dis(gen);
}

template<typename PQueue>
void test(int N, int M, PQueue &pqueue) {
    for (int i=0; i<N; i++)
        pqueue.add(randNum(N));
    for (int i=0; i<M; i++) {
        if (randNum(2)==0 || pqueue.empty() ) pqueue.add(randNum(N));
        else
            pqueue.extractMax();
    }
}
template<typename PQueue>
double timedTest(int N,int M, PQueue &pqueue){
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    test(N,M,pqueue);

    auto end=high_resolution_clock ::now();
    duration<double>elapsed =end-start;
    return elapsed.count();

}

int main(){
    int N=100000;
    int M=100000;
    ArrayMaxHeap amh;
    MaxHeap mh;
    cout<<"ArrayMaxHeap: "<<timedTest(N,M,amh)<<" sec"<<endl;
    cout<<"MaxHeap: "<<timedTest(N,M,mh)<<" sec";

    return 0;
}