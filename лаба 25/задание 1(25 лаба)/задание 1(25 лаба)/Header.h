
#include <iostream>
#include <stdexcept>

using namespace std;

// Класс для представления прямоугольного треугольника
class RightTriangle
{
private:
    double a; // Длина первого катета
    double b; // Длина второго катета 

public:
    // Конструктор по умолчанию
    RightTriangle();

    // Конструктор с параметрами
    RightTriangle(double a, double b);

    // Конструктор копирования
    RightTriangle(const RightTriangle& other);

    // Метод для установки сторон с проверкой корректности
    void setSides(double a, double b);

    // Метод для вычисления площади треугольника
    double area() const;

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const RightTriangle& triangle);
};



