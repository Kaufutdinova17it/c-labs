/*Graf8. Юный путешественник решил изучить схему авиационного сообщения Схема
авиационного сообщения задана в текстовом файле с именем FileName. в виде матрицы
смежности. Первая строка файла содержит количество городов (n) n<=15, связанных
авиационным сообщением, а следующие n строк хранят матрицу (m), m[i][j]=0, если не
имеется возможности перелета из города i в город j, иначе m[i][j]=1. Определить номера
городов, в которые из города K можно долететь не менее чем с L пересадками и более
коротких путей к таким городам не существует. Перечислите номера таких городов в
порядке возрастания. Нумерация городов начинается с 1. Если таких городов нет, выведите
число (-1)*/
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include<string>
#include "Header.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    const string filename = "FileName.txt";

    // Открываем файл для чтения и вывода его содержимого
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cout << "Ошибка: Не удалось открыть файл " << filename << endl;
        return 1;
    }

    // Чтение содержимого файла и вывод его на экран
    cout << "Содержимое файла:" << endl;
    string line;
    while (getline(inputFile, line))
    {
        cout << line << endl; 
    }
    inputFile.close(); 

    Graph graph(0); // Создаем граф с нулевым количеством городов

    try
    {
        graph.readFromFile(filename);
    }
    catch (const runtime_error& e)
    {
        cout << e.what() << endl;
        return 1;
    }

    int K, L;
    cout << "Введите номер города (K): ";
    cin >> K;
    cout << "Введите максимальное количество пересадок (L): ";
    cin >> L;

    // Приводим номер города к индексации с нуля
    K--;

    // Проверка корректности ввода города
    if (K < 0 || K >= graph.getNumCities() || L < 0) // Исправлено условие проверки
    {
        cout << "\nОшибка: Неверный номер города или значение L." << endl;
        return 1;
    }

    // Получаем доступные города из указанного города K
    set<int> citiesFromK = graph.reachableCities(K, L);

    // Сортируем результаты для вывода
    vector<int> result(citiesFromK.begin(), citiesFromK.end());

    // Возвращаем к индексации с единицы
    for (int& city : result)
    {
        city++;
    }

    // Выводим результат
    if (result.empty())
    {
        cout << -1 << endl;
    }
    else
    {
        sort(result.begin(), result.end());
        for (int city : result)
        {
            cout << city << " ";
        }
        cout << endl;
    }

    return 0;
}



