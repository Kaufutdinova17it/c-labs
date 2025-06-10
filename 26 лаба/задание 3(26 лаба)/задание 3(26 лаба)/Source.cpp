#include "Header.h"

Graph::Graph(int n) : numCities(n)
{   //размер матрицы смежности
    adjacencyMatrix.resize(n, vector<int>(n));
}
//функция для чтения из файла
void Graph::readFromFile(const string& filename)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw runtime_error("Ошибка: Не удалось открыть файл " + filename);
    }

    // Читаем количество городов из первой строки
    inputFile >> numCities;

    // Проверка корректности количества городов
    if (numCities <= 0 || numCities > 15) 
    {
        throw runtime_error("Ошибка: Неверное количество городов в файле.");
    }

    adjacencyMatrix.resize(numCities, vector<int>(numCities));

    //считывание данных из файла и заполнение матрицы смежности для графа, представляющего связь между городами
    for (int i = 0; i < numCities; ++i)
    {
        for (int j = 0; j < numCities; ++j) 
        {
            if (!(inputFile >> adjacencyMatrix[i][j]) || (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != 1)) 
            {
                throw runtime_error("Ошибка: Неверный формат данных в матрице. Значения должны быть 0 или 1.");
            }
        }
    }
    inputFile.close();
}
//проверка на симметричность матрицы
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
//нахождения всех достижимых городов из заданного стартового города
set<int> Graph::reachableCities(int startCity, int maxTransfers) const 
{
    set<int> reachable;
    queue<pair<int, int>> q; // Пара (город, количество пересадок)

    q.push({ startCity, 0 });
    reachable.insert(startCity); // Добавляем стартовый город

    while (!q.empty()) 
    {
        auto [currentCity, transfers] = q.front();
        q.pop();

        if (transfers < maxTransfers) 
        {
            for (int nextCity = 0; nextCity < numCities; ++nextCity) 
            {
                // Проверяем, есть ли связь и не был ли уже посещён следующий город
                if (adjacencyMatrix[currentCity][nextCity] == 1 && reachable.find(nextCity) == reachable.end()) 
                {
                    reachable.insert(nextCity);
                    q.push({ nextCity, transfers + 1 });
                }
            }
        }
    }

    // Удаляем стартовый город из результата, если он там есть
    reachable.erase(startCity);

    return reachable;
}

int Graph::getNumCities() const
{
    return numCities;
}

