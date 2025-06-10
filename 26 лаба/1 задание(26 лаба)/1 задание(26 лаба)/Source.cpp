#include "Header.h"
using namespace std;

// Конструктор класса для загрузки матрицы смежности из файла
Graph::Graph(const string& inputFileName)
{
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        throw runtime_error("Ошибка: Не удалось открыть файл " + inputFileName);
    }

    // Читаем количество вершин
    if (!(inputFile >> n) || n <= 0)
    {
        throw runtime_error("Ошибка: Неверное количество вершин в файле.");
    }

    // Чтение матрицы смежности
    adjacencyMatrix.resize(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (!(inputFile >> adjacencyMatrix[i][j]) || (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != 1))
            {
                throw runtime_error("Ошибка: Неверные данные в матрице смежности.");
            }
        }
    }

    // Проверяем симметричность матрицы смежности
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i])
            {
                throw runtime_error("Ошибка: Матрица смежности несимметрична.");
            }
        }
    }

    // Заполнение списка рёбер
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        { // Изменено для избегания дубликатов
            if (adjacencyMatrix[i][j] == 1)
            {
                edges.emplace_back(i, j); // Сохраняем ребро (i, j)
            }
        }
    }
}

// Метод для создания матрицы инцидентности и записи в файл
void Graph::constructIncidenceMatrix(const string& outputFileName) const
{
    int m = edges.size(); // Количество рёбер
    vector<vector<int>> incidenceMatrix(n, vector<int>(m, 0));

    for (int edgeIndex = 0; edgeIndex < m; ++edgeIndex)
    {
        int u = edges[edgeIndex].first;
        int v = edges[edgeIndex].second;

        // Проверяем, что u и v находятся в пределах количества вершин
        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            throw runtime_error("Ошибка: Вершина выходит за пределы диапазона");
        }

        // Устанавливаем инцидентность для обеих вершин (для неориентированного графа)
        incidenceMatrix[u][edgeIndex] = 1; // Инцидентность для вершины u
        incidenceMatrix[v][edgeIndex] = 1; // Инцидентность для вершины v
    }

    // Записываем матрицу инцидентности в файл
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
        throw runtime_error("Ошибка: Не удалось открыть файл " + outputFileName);
    }

    // Записываем размер матрицы инцидентности
    outputFile << n << " " << m << endl;

    // Записываем саму матрицу инцидентности
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
        throw runtime_error("Ошибка: Не удалось записать данные в файл " + outputFileName);
    }

    outputFile.close();
}






