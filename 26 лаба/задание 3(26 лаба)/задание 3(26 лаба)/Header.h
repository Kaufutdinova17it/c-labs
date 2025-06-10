#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <stdexcept>

using namespace std;

class Graph 
{
private:
    vector<vector<int>> adjacencyMatrix;
    int numCities;

public:
    Graph(int n);
    void readFromFile(const string& filename);
    bool isSymmetric() const;
    set<int> reachableCities(int startCity, int maxTransfers) const;
    int getNumCities() const;
};

