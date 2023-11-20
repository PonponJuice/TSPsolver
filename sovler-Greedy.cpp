// Greedy法
// 計算量 O(N^2 logN)
// 精度保証 : O(logN)

#include<bits/stdc++.h>
#include"posIOfile.hpp"
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

struct UnionFind{
    private:
    //長点数
    int N;
    //負の数→-1*その木の大きさ 正の数→親のindex
    vector<int> par;

    public:

    UnionFind(int n) : par(n, -1){}

    int root(int p){
        if(par[p]<0)return p;
        return par[p] = root(par[p]);
    }

    int size(int p){
        return -par[root(p)];
    }

    bool same(int a, int b){
        return root(a) == root(b);
    }

    bool unite(int a, int b){
        a = root(a), b = root(b);
        if(a == b)return false;
        if(size(a) < size(b) )std::swap(a,b);
        par[a] += par[b];
        par[b] = a;
        return true;
    }
};

vector<int> solve(vector<Position> points){
    int n = points.size();
    vector<int> result;
    UnionFind dsu(n);
    vector<int> outdegree(n, 0);

    // 辺の距離が小さい順になるようにソートする
    vector<pair<double, pair<int, int>>> edges; // 距離とその両端の頂点のindexを距離が小さい順に持つ
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            edges.push_back({points[i].dist(points[j]), {i, j}}); 
        }
    }
    sort(edges.begin(), edges.end());

    // どの辺を使うかを決める
    vector<pair<int,int>> useEdge; // 使う辺を保存する
    for(int i = 0; i < edges.size(); i++){
        auto [l, r] = edges[i].second;
        if(!dsu.same(l, r) && outdegree[l] < 2 && outdegree[r] < 2){
            dsu.unite(l, r);
            outdegree[l]++;
            outdegree[r]++;
            useEdge.push_back({l, r}); 
        }
    }

    // 使う辺の情報からどの順番に訪れるか復元する
    vector<vector<int>> graph(n); // 隣接リスト
    for(int i = 0; i < useEdge.size(); i++){
        graph[useEdge[i].first].push_back(useEdge[i].second);
        graph[useEdge[i].second].push_back(useEdge[i].first);
    }
    int st = -1, par = -1;
    for(int i = 0; i < n; i++){
        if(graph[i].size() == 1){
            par = i;
            st = graph[i][0];
            result = {i + 1, graph[i][0] + 1};
            break;
        }
    }
    while(graph[st].size() != 1){
        if(graph[st][0] == par){
            par = st;
            st = graph[st][1];
        }else{
            par = st;
            st = graph[st][0];
        }
        result.push_back(st + 1);
    }

    return result;
}