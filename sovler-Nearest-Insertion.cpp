// Nearest Insertion法 (NI)　
// 計算量  O(N^2)
// 精度保証 : 2

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
    vector<double> distFromRes(n, 1e9); // 集合resultに含まれる点からの最短距離
    vector<bool> useEdge(n,false);

    auto addPoint = [&](int ind){
        result.push_back(ind);
        useEdge[ind] = true;
        for(int i = 0; i < n; i++){
            if(distFromRes[i] > points[ind].dist(points[i])){
                distFromRes[i] = points[ind].dist(points[i]);
            }
        }
    };


    result.push_back(0);
    useEdge[0] = true;
    for(int i = 0; i < n; i++){
        if(distFromRes[i] > points[0].dist(points[i])){
            distFromRes[i] = points[0].dist(points[i]);
        }
    }

    for(int turn = 0; turn < n - 1; turn++){
        double minDist = 1e9;
        int useInd = -1;
        for(int i = 0; i < n; i++){
            if(!useEdge[i] && distFromRes[i] < minDist){
                useInd = i;
                minDist = distFromRes[i];
            }
        }

        const auto diffDist = [&](int l, int r, int in)->double {
            return points[in].dist(points[l]) + points[in].dist(points[r]) - points[l].dist(points[r]);
        };
        int insertInd = 0;
        double minAddDist = diffDist(result.back(), result[0], useInd);

        for(int i = 0; i < result.size() - 1; i++){
            if(diffDist(result[i], result[i + 1], useInd) < minAddDist){
                minAddDist = diffDist(result[i], result[i + 1], useInd);
                insertInd = i + 1;
            }
        }
        result.insert(result.begin() + insertInd, useInd);

        useEdge[useInd] = true;
        for(int i = 0; i < n; i++){
            if(distFromRes[i] > points[useInd].dist(points[i])){
                distFromRes[i] = points[useInd].dist(points[i]);
            }
        }
    }

    for(int i = 0; i < result.size(); i++) result[i]++;
    return result;
}