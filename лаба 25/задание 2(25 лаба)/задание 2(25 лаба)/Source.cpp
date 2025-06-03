#include "Header.h"
RightTriangle::RightTriangle() : a(1.0), b(1.0), c(1.0) {}

// Конструктор с параметрами
RightTriangle::RightTriangle(double a, double b, double c) {
    setSides(a, b, c);
}

// Конструктор копирования
RightTriangle::RightTriangle(const RightTriangle& other) : a(other.a), b(other.b), c(other.c) {}

// Метод для установки сторон с проверкой корректности
void RightTriangle::setSides(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw invalid_argument("Длины катетов должны быть положительными.");
    }

    // Проверка неравенства треугольника
    if (a + b <= c || a + c <= b || b + c <= a) {
        throw invalid_argument("Стороны не могут образовать треугольник.");
    }

    this->a = a;
    this->b = b;
    this->c = c;
}

// Метод для вычисления площади по формуле Герона
double RightTriangle::area() const {
    double s = (a + b + c) / 2; 
    return sqrt(s * (s - a) * (s - b) * (s - c)); 
}

// Перегрузка оператора вывода
ostream& operator<<(ostream& os, const RightTriangle& triangle) {
    os << "Сторона a: " << triangle.a << ", Сторона b: " << triangle.b << ", Сторона c: " << triangle.c
        << ", Площадь: " << triangle.area();
    return os;
}

// Унарная операция ++ (умножает стороны на 2)
RightTriangle& RightTriangle::operator++() 
{
    a *= 2;
    b *= 2;
    c *= 2; 
    setSides(a, b, c); 
    return *this;
}

// Унарная операция -- (делит стороны на 2)
RightTriangle& RightTriangle::operator--()
{
    if (a / 2 <= 0 || b / 2 <= 0 || c / 2 <= 0) 
    {
        throw invalid_argument("Длины катетов не могут быть меньше или равны нулю.");
    }
    a /= 2;
    b /= 2;
    c /= 2;
    setSides(a, b, c); // Обновляем стороны и проверяем
    return *this;
}

// Операция приведения типа (неявная) для площади
RightTriangle::operator double() const 
{
    return area(); // Возвращает площадь
}

// Операция приведения типа (неявная) для проверки существования треугольника
RightTriangle::operator bool() const 
{
    return (a + b > c && a + c > b && b + c > a); // Возвращает true, если стороны могут образовать треугольник
}

// Бинарная операция <= для сравнения площадей
bool RightTriangle::operator<=(const RightTriangle& other) const
{
    return area() <= other.area();
}

// Бинарная операция >= для сравнения площадей
bool RightTriangle::operator>=(const RightTriangle& other) const 
{
    return area() >= other.area();
}