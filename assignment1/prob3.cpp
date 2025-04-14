#include <iostream>

using namespace std;

const int MAX_SIZE=16;
const int PATH=0;
const int WALL=1;
const int VISITED=2;
const int BLOCKED=3;

int maze[MAX_SIZE][MAX_SIZE];
int N,K;


void readMaze(){
    cin>>N;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++) {
            cin >> maze[i][j];
        }
    cin>>K;
}

int findPathsUnderN(int x,int y,int count){
    int n=0;
    if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] != PATH || count > K)
        return 0;
    else if(x==N-1 && y==N-1 && count<=K) {
        return 1;
    }
    else {
        maze[x][y] = VISITED;  // 방문 표시
        n += findPathsUnderN(x - 1, y, count + 1);
        n += findPathsUnderN(x, y + 1, count + 1);
        n += findPathsUnderN(x + 1, y, count + 1);
        n += findPathsUnderN(x, y - 1, count + 1);
        maze[x][y] = PATH;  // 백트래킹: 원래 상태로 복구
    }
    return n;
}

int main(){
    readMaze();
    cout<<findPathsUnderN(0,0,0);
    cout<<endl;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)
            cout<<maze[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}