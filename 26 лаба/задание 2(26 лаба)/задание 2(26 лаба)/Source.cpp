#include "Header.h"
#include <queue>
using namespace std;
Graph::Graph(const vector<vector<int>>& matrix) : adjacencyMatrix(matrix) {}

set<int> Graph::reachableCities(int startCity, int maxSteps) const
{
    int n = adjacencyMatrix.size();
    set<int> reachable;
    queue<pair<int, int>> q; // ���� (�����, ���������� �����)

    // ���������, ��� startCity ��������� � ���������� ��������
    if (startCity < 0 || startCity >= n) {
        throw invalid_argument("�������� ����� ���������� ������.");
    }

    q.push({ startCity, 0 });
    reachable.insert(startCity); // ��������� ��������� �����

    while (!q.empty()) 
    {
        auto [currentCity, steps] = q.front();
        q.pop();

        if (steps < maxSteps) {
            for (int nextCity = 0; nextCity < n; ++nextCity) 
            {
                // ���������, ���� �� ����� � �� ��� �� ��� ������� ��������� �����
                if (adjacencyMatrix[currentCity][nextCity] == 1 && reachable.find(nextCity) == reachable.end())
                {
                    reachable.insert(nextCity);
                    q.push({ nextCity, steps + 1 });
                }
            }
        }
    }

    // ������� ��������� ����� �� ����������, ���� �� ��� ����
    reachable.erase(startCity);
    return reachable;
}

bool Graph::isSymmetric() const 
{
    int n = adjacencyMatrix.size();
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) {
            if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i])
            {
                return false;
            }
        }
    }
    return true;
}
