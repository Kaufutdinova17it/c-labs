/*TreeFun6. Реализовать для бинарного дерева интерфейс итератора, который будет возвращать
значения элементов, находящихся в узлах дерева, в порядке "корень-право-лево".
Преобразовывать дерево в список или иную структуру данных нельзя, рекурсию использовать
запрещается.*/
#include <iostream>
#include <vector>
#include "Header.h" // Предполагается, что здесь определены необходимые структуры и функции для работы с деревом
#include<fstream>
using namespace std;

int main() 
{
    setlocale(LC_ALL, "rus");
    PNode head = NULL; // Указатель на корень дерева
    vector<int> inputValues; // Вектор для хранения введенных значений

    int ch;
    cout << "1.С клавиатуры\n2.Рандомно\n3.Из файла" << endl << "Выберите способ заполнения дерева: ";
    cin >> ch;

    switch (ch)
    {
    case 1:
        Keyboard(head, inputValues); // Заполнение дерева с клавиатуры
        break;
    case 2:
        Random(head, inputValues); // Заполнение дерева случайными числами
        break;
    case 3:
        ToFile(head, inputValues); // Заполнение дерева из файла
        break;
    default:
        cout << "Нет такого способа заполнения";
        return 1;
    }

    if (head == NULL)
    {
        cout << "\nДерево пустое!";
        return 1;
    }
    else 
    {
        cout << endl;

        cout << "\nПолучившееся дерево:" << endl;
        string rpref = "";
        string cpref = "";
        string lpref = "";
        Print(head); 

        
        cout << "\nВведенные значения: ";
        for (int value : inputValues) 
        {
            cout << value << " ";
        }
        cout << endl;

        cout << "Вывод дерева в порядке (Корень-Право-Лево): ";
        vector<int> res = inOrder(head); // Получение результата обхода
        for (int i = 0; i < res.size(); i++)
        {
            cout << res[i] << " ";
        }
        cout << endl; 
    }

    return 0;
}







