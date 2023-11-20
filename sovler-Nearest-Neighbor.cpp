// Nearest Neighbor法 (NN)
// 計算量 O(N^2)
// 精度保証 : O(logN)

#include<bits/stdc++.h>
#include"posIOFile.hpp"
using namespace std;

vector<int> solve(vector<Position>);

int main(int argc, char *argv[]){

    assert(argc >= 3);
    string inputFile = argv[1];
    string outputFile = argv[2];

    vector<Position> points;

    readFile(inputFile, points);
    vector<int> answer = solve(points);
    outFile(outputFile, answer);
}

vector<int> solve(vector<Position> points){
    int n = points.size();
    vector<int> result;
    vector<bool> usePoint(n, false);

    int nowPoint = 0;
    result.push_back(nowPoint + 1);

    for(int turn = 0; turn < n - 1; turn++){
        double minDist = 1e9;
        int nextPoint = -1;
        usePoint[nowPoint] = true;
        for(int i = 0; i < n; i++){
            if(!usePoint[i] && points[nowPoint].dist(points[i]) < minDist){
                minDist = points[nowPoint].dist(points[i]);
                nextPoint = i;
            }
        }
        nowPoint = nextPoint;
        result.push_back(nowPoint + 1);
    }

    return result;
}