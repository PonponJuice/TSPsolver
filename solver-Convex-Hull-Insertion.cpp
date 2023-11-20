// Convex Hull Insertion法 (CHI)
// 計算量
// 精度保証

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

bool operator<(const Position& a, const Position& b){
    if(a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
bool operator==(const Position& a, const Position& b){
    return a.x == b.x && a.y == b.y;
}

Position operator-(const Position& a, const Position& b){
    return Position{a.x - b.x, a.y - b.y};
}

// 凸包の計算
vector<int> convex_hull(vector<Position> points){
    int n = points.size(), k = 0;
    vector<Position> p = points;
    sort(p.begin(), p.end());
    vector<Position> ch(2 * n);

    auto cross = [&](Position a, Position b)->long long {
        return 1LL * a.x * b.y - 1LL * a.y * b.x;
    };

    for(int i = 0; i < n; ch[k++] = p[i++]){
        while(k >= 2 && cross(ch[k-1] - ch[k-2], p[i] - ch[k-1]) < 0) --k;
    }
    for(int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]){
        while(k >= t && cross(ch[k-1] - ch[k-2], p[i] - ch[k-1]) < 0) --k;
    }
    ch.resize(k-1);

    vector<int> result;

    for(int i = 0; i < ch.size(); i++){
        for(int j = 0; j < n; j++){
            if(ch[i] == points[j]){
                result.push_back(j);
            }
        }
    }
    return result;
}

vector<int> solve(vector<Position> points){
    int n = points.size();
    vector<int> notUse;
    vector<int> result = convex_hull(points);
    for(int i = 0; i < n; i++){
        if(find(result.begin(), result.end(), i) == result.end()){
            notUse.emplace_back(i);
        }
    }

    while(result.size() < n){
        int bestI = -1, bestJ = -1;
        double mn = 1e9;

        const auto diffDist = [&](int l, int r, int in)->double {
            return points[in].dist(points[l]) + points[in].dist(points[r]) - points[l].dist(points[r]);
        };

        for(int i = 0; i < result.size(); i++){
            for(int j = 0; j < notUse.size(); j++){
                if(mn > diffDist(result[(result.size() + i - 1) % result.size()], result[i], notUse[j])){
                    mn = diffDist(result[(result.size() + i - 1) % result.size()], result[i], notUse[j]);
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        result.insert(result.begin() + bestI, notUse[bestJ]);
        swap(notUse.back(), notUse[bestJ]);
        notUse.pop_back();
    }

    for(int i = 0; i < n; i++){
        result[i]++;
    }

    return result;
}