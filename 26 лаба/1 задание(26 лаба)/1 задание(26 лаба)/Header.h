#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>

using namespace std;
class Graph 
{
private:
    int n; // Количество вершин
    vector<vector<int>> adjacencyMatrix;
    vector<pair<int, int>> edges;
 

public:
    Graph(const string& inputFileName);
    void constructIncidenceMatrix(const string& outputFileName) const;
};



