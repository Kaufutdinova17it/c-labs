#include "Header.h"

// ����������� �� ���������
RightTriangle::RightTriangle() : a(1.0), b(1.0) {}

// ����������� � �����������
RightTriangle::RightTriangle(double a, double b)
{
    setSides(a, b);
}

// ����������� �����������
RightTriangle::RightTriangle(const RightTriangle& other) : a(other.a), b(other.b) {}

// ����� ��� ��������� ������ � ��������� ������������
void RightTriangle::setSides(double a, double b)
{
    if (a <= 0 || b <= 0)
    {
        throw invalid_argument("����� ������� ������ ���� ��������������.");
    }
    this->a = a;
    this->b = b;
}

// ����� ��� ���������� �������
double RightTriangle::area() const
{
    return (a * b) / 2;
}

// ���������� ��������� ������
ostream& operator<<(ostream& os, const RightTriangle& triangle)
{
    os << "����� a: " << triangle.a << ", ����� b: " << triangle.b
        << ", �������: " << triangle.area();
    return os;
}
