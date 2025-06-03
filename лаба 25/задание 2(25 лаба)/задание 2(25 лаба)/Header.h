
#include <iostream>
#include <stdexcept>

using namespace std;

// Класс для представления прямоугольного треугольника
class RightTriangle
{
private:
    double a; // Длина первого катета
    double b; // Длина второго катета 
    double c;

public:
    // Конструктор по умолчанию
    RightTriangle();

    // Конструктор с параметрами
    RightTriangle(double a, double b,double c);

    // Конструктор копирования
    RightTriangle(const RightTriangle& other);

    // Метод для установки сторон с проверкой корректности
    void setSides(double a, double b,double c);

    // Метод для вычисления площади треугольника
    double area() const;

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const RightTriangle& triangle);

    // Унарная операция ++ (умножает стороны на 2)
    RightTriangle& operator++();

    // Унарная операция -- (делит стороны на 2)
    RightTriangle& operator--();

    // Операция приведения типа (неявная) для площади
    operator double() const;

    // Неявное приведение к bool для проверки существования треугольника
    operator bool() const;

    // Бинарная операция <= для сравнения площадей
    bool operator<=(const RightTriangle& other) const;

    // Бинарная операция >= для сравнения площадей
    bool operator>=(const RightTriangle& other) const;
};




