struct Position{
    int x, y;

    double dist(Position& others){
        return std::hypotl(this->x - others.x, this->y - others.y);
    }
};

void readFile(std::string fileName, std::vector<Position>& points){
    std::ifstream inputFile(fileName);

    int n;
    inputFile >> n;
    points.resize(n);
    for(int i = 0; i < n; i++){
        inputFile >> points[i].x >> points[i].y;
    }

    inputFile.close();
}

void outFile(std::string fileName, const std::vector<int>& answer){
    std::ofstream outputFile(fileName);

    for(int i = 0; i < answer.size(); i++){
        outputFile << answer[i] << " ";
    }
    outputFile << std::endl;
}
