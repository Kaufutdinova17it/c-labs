#include <iostream>
#include "Header.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    try
    {
        double a, b;
        cout << "Приветствую, вам нужно придумать катеты для прямоугольного треугольника." << endl;
        cout << "Введите длину первого катета (a): ";
        cin >> a;
        cout << "Введите длину второго катета (b): ";
        cin >> b;

        RightTriangle triangle(a, b);
        cout << triangle << endl;

        // Создание треугольника по умолчанию
        RightTriangle defaultTriangle;
        cout << "Треугольник по умолчанию: " << defaultTriangle << endl;

        // Создание треугольника копированием
        RightTriangle copyTriangle(triangle);
        cout << "Копия треугольника: " << copyTriangle << endl;

    }
    catch (const invalid_argument& e)
    {
        cout << "Ошибка: " << e.what() << endl;
    }
    catch (const exception& e)
    {
        cout << "Произошла ошибка: " << e.what() << endl;
    }

    return 0;
}


