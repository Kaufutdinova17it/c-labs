
#include <vector>
#include <set>
#include <stdexcept>
#include <utility>
using namespace std;
class Graph 
{
public:
    Graph(const vector<vector<int>>& adjacencyMatrix);
    set<int> reachableCities(int startCity, int maxSteps) const;
    bool isSymmetric() const;

private:
    vector<vector<int>> adjacencyMatrix;
};


