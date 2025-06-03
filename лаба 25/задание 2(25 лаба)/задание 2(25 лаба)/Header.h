
#include <iostream>
#include <stdexcept>

using namespace std;

// ����� ��� ������������� �������������� ������������
class RightTriangle
{
private:
    double a; // ����� ������� ������
    double b; // ����� ������� ������ 
    double c;

public:
    // ����������� �� ���������
    RightTriangle();

    // ����������� � �����������
    RightTriangle(double a, double b,double c);

    // ����������� �����������
    RightTriangle(const RightTriangle& other);

    // ����� ��� ��������� ������ � ��������� ������������
    void setSides(double a, double b,double c);

    // ����� ��� ���������� ������� ������������
    double area() const;

    // ���������� ��������� ������
    friend ostream& operator<<(ostream& os, const RightTriangle& triangle);

    // ������� �������� ++ (�������� ������� �� 2)
    RightTriangle& operator++();

    // ������� �������� -- (����� ������� �� 2)
    RightTriangle& operator--();

    // �������� ���������� ���� (�������) ��� �������
    operator double() const;

    // ������� ���������� � bool ��� �������� ������������� ������������
    operator bool() const;

    // �������� �������� <= ��� ��������� ��������
    bool operator<=(const RightTriangle& other) const;

    // �������� �������� >= ��� ��������� ��������
    bool operator>=(const RightTriangle& other) const;
};




