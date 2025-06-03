#include "Header.h"
RightTriangle::RightTriangle() : a(1.0), b(1.0), c(1.0) {}

// ����������� � �����������
RightTriangle::RightTriangle(double a, double b, double c) {
    setSides(a, b, c);
}

// ����������� �����������
RightTriangle::RightTriangle(const RightTriangle& other) : a(other.a), b(other.b), c(other.c) {}

// ����� ��� ��������� ������ � ��������� ������������
void RightTriangle::setSides(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw invalid_argument("����� ������� ������ ���� ��������������.");
    }

    // �������� ����������� ������������
    if (a + b <= c || a + c <= b || b + c <= a) {
        throw invalid_argument("������� �� ����� ���������� �����������.");
    }

    this->a = a;
    this->b = b;
    this->c = c;
}

// ����� ��� ���������� ������� �� ������� ������
double RightTriangle::area() const {
    double s = (a + b + c) / 2; 
    return sqrt(s * (s - a) * (s - b) * (s - c)); 
}

// ���������� ��������� ������
ostream& operator<<(ostream& os, const RightTriangle& triangle) {
    os << "������� a: " << triangle.a << ", ������� b: " << triangle.b << ", ������� c: " << triangle.c
        << ", �������: " << triangle.area();
    return os;
}

// ������� �������� ++ (�������� ������� �� 2)
RightTriangle& RightTriangle::operator++() 
{
    a *= 2;
    b *= 2;
    c *= 2; 
    setSides(a, b, c); 
    return *this;
}

// ������� �������� -- (����� ������� �� 2)
RightTriangle& RightTriangle::operator--()
{
    if (a / 2 <= 0 || b / 2 <= 0 || c / 2 <= 0) 
    {
        throw invalid_argument("����� ������� �� ����� ���� ������ ��� ����� ����.");
    }
    a /= 2;
    b /= 2;
    c /= 2;
    setSides(a, b, c); // ��������� ������� � ���������
    return *this;
}

// �������� ���������� ���� (�������) ��� �������
RightTriangle::operator double() const 
{
    return area(); // ���������� �������
}

// �������� ���������� ���� (�������) ��� �������� ������������� ������������
RightTriangle::operator bool() const 
{
    return (a + b > c && a + c > b && b + c > a); // ���������� true, ���� ������� ����� ���������� �����������
}

// �������� �������� <= ��� ��������� ��������
bool RightTriangle::operator<=(const RightTriangle& other) const
{
    return area() <= other.area();
}

// �������� �������� >= ��� ��������� ��������
bool RightTriangle::operator>=(const RightTriangle& other) const 
{
    return area() >= other.area();
}