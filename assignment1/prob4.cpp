#include <iostream>

using namespace std;

const int MAX_SIZE=16;
const int PATH=0;
const int WALL=1;
const int BOMB=2;
const int VISITED=3;


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

bool findPathsUnderN(int x,int y,int count) {
    if (x < 0 || y < 0 || x >= N || y >= N || (maze[x][y] != PATH && maze[x][y] != BOMB) || count > K)
        return false;

    else if (x == N - 1 && y == N - 1 && count <= K) {
        return true;
    }

    int undo = maze[x][y];
    if (maze[x][y] == BOMB)
        count += 1;
    maze[x][y] = VISITED;

    if (findPathsUnderN(x - 1, y, count) || findPathsUnderN(x, y + 1, count)
        || findPathsUnderN(x + 1, y, count) || findPathsUnderN(x, y - 1, count))
        return true;

    maze[x][y] = undo;

    return false;
}

int main(){
    readMaze();
    if(findPathsUnderN(0,0,0))
        cout<<"Yes";
    else
        cout<<"No";
    return 0;
}