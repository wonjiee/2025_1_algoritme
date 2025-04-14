#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Point{
    int x,y;
};

vector<Point>points;
int N;

bool compareX(const Point &a,const Point &b){
    return a.x<b.x;
}

void readFile(string fileName){
    ifstream infile(fileName);
    infile>>N;
    for(int i=0;i<N;i++) {
        Point point;
        infile >> point.x >> point.y;
        points.push_back(point);
    }
    sort(points.begin(),points.end(),compareX);
}

int ccw(const Point &a, const Point &b, const Point &c){
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

vector<Point> minimalHull(vector<Point>&points){
    if(points.size()<=1)
        return points;
    else if(points.size()<=2){
        if(points[0].y>points[1].y ||
           (points[0].y==points[1].y && points[0].x<points[1].x)) {
            return points;
        }
        else {
            swap(points[0], points[1]);
            return points;
        }
    }
    else{
        int index=0;
        for(int i=0;i<3;i++){
            if(points[index].y<points[i].y ||
               (points[index].y==points[i].y && points[index].x>points[i].x)){
                index=i;
            }
        }
        swap(points[0],points[index]);

        if(ccw(points[0],points[1],points[2])<0){
            swap(points[1],points[2]);
        }
        return points;
    }
}

int nextIdx(const vector<Point>&points,int Idx){
    return (Idx+1)%points.size();
}

int prevIdx(const vector<Point>&points,int Idx){
    return (Idx-1+points.size())%points.size();
}

vector<Point> mergeHull(vector<Point>&left,vector<Point>&right){
    // 예외 처리
    if(left.size() == 1){
        vector<Point> tmp=right;
        tmp.push_back(left[0]);
        return minimalHull(tmp);
    }
    if(right.size()==1){
        vector<Point> tmp=left;
        tmp.push_back(right[0]);
        return minimalHull(tmp);
    }
    if(left.size()==0) return right;
    if(right.size()==0) return left;

    // 가까운 x값 찾기
    int leftIdx=0;
    int rightIdx=0;
    for(int i=0;i<left.size();i++)
        if(left[leftIdx].x<left[i].x)
            leftIdx=i;
    for(int j=0;j<right.size();j++)
        if(right[rightIdx].x>right[j].x)
            rightIdx=j;

    // 위쪽 방향 선 찾기
    int leftUpIdx=leftIdx;
    int rightUpIdx=rightIdx;
    while(true){
        int changed=0;
        while(ccw(right[rightUpIdx],left[leftUpIdx],left[nextIdx(left,leftUpIdx)])<=0){
            leftUpIdx= nextIdx(left,leftUpIdx);
            changed++;
        }
        while(ccw(left[leftUpIdx],right[rightUpIdx],right[prevIdx(right,rightUpIdx)])>=0){
            rightUpIdx= prevIdx(right,rightUpIdx);
            changed++;
        }
        if(changed==0)
            break;
    }

    // 아래 방향 선 찾기
    int leftDownIdx=leftIdx;
    int rightDownIdx=rightIdx;
    while(true){
        int changed=0;
        while(ccw(left[leftDownIdx],right[rightDownIdx],right[nextIdx(right,rightDownIdx)])<=0){
            rightDownIdx= nextIdx(right,rightDownIdx);
            changed++;
        }
        while(ccw(right[rightDownIdx],left[leftDownIdx],left[prevIdx(left,leftDownIdx)])>=0){
            leftDownIdx= prevIdx(left,leftDownIdx);
            changed++;
        }
        if(changed==0)
            break;
    }

    // 합치기
    vector<Point>result;
    while(leftUpIdx!=leftDownIdx){
        result.push_back(left[leftUpIdx]);
        leftUpIdx= nextIdx(left,leftUpIdx);
    }
    result.push_back(left[leftUpIdx]);
    while(rightDownIdx!=rightUpIdx){
        result.push_back(right[rightDownIdx]);
        rightDownIdx= nextIdx(right,rightDownIdx);
    }
    result.push_back(right[rightDownIdx]);
    return result;
}

vector<Point> findConvexHull(vector<Point>&points){
    if(points.size()<=3)
        return minimalHull(points);

    int mid=points.size()/2;
    vector<Point>left(points.begin(),points.begin()+mid);
    vector<Point>right(points.begin()+mid,points.end());

    vector<Point>leftHull= findConvexHull(left);
    vector<Point>rightHull = findConvexHull(right);

    return mergeHull(leftHull,rightHull);
}

void printConvexHul(const vector<Point>&points){
    for(int i=0;i<points.size();i++)
        cout<<points[i].x<<" "<<points[i].y<<endl;
}

int main(){
    readFile("input.txt");
    vector<Point> result=findConvexHull(points);
    printConvexHul(result);

    return 0;
}