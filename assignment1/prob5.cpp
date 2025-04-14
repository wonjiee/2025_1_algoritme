#include <iostream>
#include <fstream>

using namespace std;

const int MAX_SIZE = 20;
const int PATH = 0;
const int WALL = 1;
const int VISITED = 2;

const int dir[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int maze[MAX_SIZE][MAX_SIZE];
int N, K;
int minRest = -1;

void readMaze() {
    ifstream infile("maze.txt");

    infile >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            infile >> maze[i][j];

    infile >> K;
    infile.close();
}

void findMinRestPath(int x, int y, int count) {
    if (x == N - 1 && y == N - 1) {
        if (minRest == -1)
            minRest = count;
        else
            minRest = min(minRest, count);
        return;
    }

    if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] != PATH)
        return;

    maze[x][y] = VISITED;

    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= K; j++) {
            int nx = x + dir[i][0] * j;
            int ny = y + dir[i][1] * j;

            if (nx >= 0 && ny >= 0 && nx < N && ny < N && maze[nx][ny] == PATH) {
                for(int k=1;k<j;k++){
                    maze[nx-dir[i][0]*k][ny-dir[i][1]*k]=VISITED;
                }
                findMinRestPath(nx, ny, count + 1);
                for(int k=1;k<j;k++){
                    maze[nx-dir[i][0]*k][ny-dir[i][1]*k]=PATH;
                }
            } else break;
        }
    }

    maze[x][y] = PATH;
}

int main() {
    readMaze();
    findMinRestPath(0, 0, 0);
    cout << minRest;
    return 0;
}
