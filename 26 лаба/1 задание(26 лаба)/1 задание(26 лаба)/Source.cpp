#include "Header.h"
using namespace std;

// ����������� ������ ��� �������� ������� ��������� �� �����
Graph::Graph(const string& inputFileName)
{
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        throw runtime_error("������: �� ������� ������� ���� " + inputFileName);
    }

    // ������ ���������� ������
    if (!(inputFile >> n) || n <= 0)
    {
        throw runtime_error("������: �������� ���������� ������ � �����.");
    }

    // ������ ������� ���������
    adjacencyMatrix.resize(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (!(inputFile >> adjacencyMatrix[i][j]) || (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != 1))
            {
                throw runtime_error("������: �������� ������ � ������� ���������.");
            }
        }
    }

    // ��������� �������������� ������� ���������
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i])
            {
                throw runtime_error("������: ������� ��������� �������������.");
            }
        }
    }

    // ���������� ������ ����
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        { // �������� ��� ��������� ����������
            if (adjacencyMatrix[i][j] == 1)
            {
                edges.emplace_back(i, j); // ��������� ����� (i, j)
            }
        }
    }
}

// ����� ��� �������� ������� ������������� � ������ � ����
void Graph::constructIncidenceMatrix(const string& outputFileName) const
{
    int m = edges.size(); // ���������� ����
    vector<vector<int>> incidenceMatrix(n, vector<int>(m, 0));

    for (int edgeIndex = 0; edgeIndex < m; ++edgeIndex)
    {
        int u = edges[edgeIndex].first;
        int v = edges[edgeIndex].second;

        // ���������, ��� u � v ��������� � �������� ���������� ������
        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            throw runtime_error("������: ������� ������� �� ������� ���������");
        }

        // ������������� ������������� ��� ����� ������ (��� ������������������ �����)
        incidenceMatrix[u][edgeIndex] = 1; // ������������� ��� ������� u
        incidenceMatrix[v][edgeIndex] = 1; // ������������� ��� ������� v
    }

    // ���������� ������� ������������� � ����
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
        throw runtime_error("������: �� ������� ������� ���� " + outputFileName);
    }

    // ���������� ������ ������� �������������
    outputFile << n << " " << m << endl;

    // ���������� ���� ������� �������������
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            outputFile << incidenceMatrix[i][j] << " ";
        }
        outputFile << endl;
    }

    if (outputFile.bad())
    {
        throw runtime_error("������: �� ������� �������� ������ � ���� " + outputFileName);
    }

    outputFile.close();
}






