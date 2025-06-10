#include "Header.h"

Graph::Graph(int n) : numCities(n)
{   //������ ������� ���������
    adjacencyMatrix.resize(n, vector<int>(n));
}
//������� ��� ������ �� �����
void Graph::readFromFile(const string& filename)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw runtime_error("������: �� ������� ������� ���� " + filename);
    }

    // ������ ���������� ������� �� ������ ������
    inputFile >> numCities;

    // �������� ������������ ���������� �������
    if (numCities <= 0 || numCities > 15) 
    {
        throw runtime_error("������: �������� ���������� ������� � �����.");
    }

    adjacencyMatrix.resize(numCities, vector<int>(numCities));

    //���������� ������ �� ����� � ���������� ������� ��������� ��� �����, ��������������� ����� ����� ��������
    for (int i = 0; i < numCities; ++i)
    {
        for (int j = 0; j < numCities; ++j) 
        {
            if (!(inputFile >> adjacencyMatrix[i][j]) || (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != 1)) 
            {
                throw runtime_error("������: �������� ������ ������ � �������. �������� ������ ���� 0 ��� 1.");
            }
        }
    }
    inputFile.close();
}
//�������� �� �������������� �������
bool Graph::isSymmetric() const 
{
    for (int i = 0; i < numCities; ++i) 
    {
        for (int j = 0; j < numCities; ++j) 
        {
            if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i]) 
            {
                return false;
            }
        }
    }
    return true;
}
//���������� ���� ���������� ������� �� ��������� ���������� ������
set<int> Graph::reachableCities(int startCity, int maxTransfers) const 
{
    set<int> reachable;
    queue<pair<int, int>> q; // ���� (�����, ���������� ���������)

    q.push({ startCity, 0 });
    reachable.insert(startCity); // ��������� ��������� �����

    while (!q.empty()) 
    {
        auto [currentCity, transfers] = q.front();
        q.pop();

        if (transfers < maxTransfers) 
        {
            for (int nextCity = 0; nextCity < numCities; ++nextCity) 
            {
                // ���������, ���� �� ����� � �� ��� �� ��� ������� ��������� �����
                if (adjacencyMatrix[currentCity][nextCity] == 1 && reachable.find(nextCity) == reachable.end()) 
                {
                    reachable.insert(nextCity);
                    q.push({ nextCity, transfers + 1 });
                }
            }
        }
    }

    // ������� ��������� ����� �� ����������, ���� �� ��� ����
    reachable.erase(startCity);

    return reachable;
}

int Graph::getNumCities() const
{
    return numCities;
}

