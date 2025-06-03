#include "Header.h"

// Конструктор по умолчанию
RightTriangle::RightTriangle() : a(1.0), b(1.0) {}

// Конструктор с параметрами
RightTriangle::RightTriangle(double a, double b)
{
    setSides(a, b);
}

// Конструктор копирования
RightTriangle::RightTriangle(const RightTriangle& other) : a(other.a), b(other.b) {}

// Метод для установки сторон с проверкой корректности
void RightTriangle::setSides(double a, double b)
{
    if (a <= 0 || b <= 0)
    {
        throw invalid_argument("Длины катетов должны быть положительными.");
    }
    this->a = a;
    this->b = b;
}

// Метод для вычисления площади
double RightTriangle::area() const
{
    return (a * b) / 2;
}

// Перегрузка оператора вывода
ostream& operator<<(ostream& os, const RightTriangle& triangle)
{
    os << "Катет a: " << triangle.a << ", Катет b: " << triangle.b
        << ", Площадь: " << triangle.area();
    return os;
}
