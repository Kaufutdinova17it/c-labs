
#include <iostream>
#include <stdexcept>

using namespace std;

// ����� ��� ������������� �������������� ������������
class RightTriangle
{
private:
    double a; // ����� ������� ������
    double b; // ����� ������� ������ 

public:
    // ����������� �� ���������
    RightTriangle();

    // ����������� � �����������
    RightTriangle(double a, double b);

    // ����������� �����������
    RightTriangle(const RightTriangle& other);

    // ����� ��� ��������� ������ � ��������� ������������
    void setSides(double a, double b);

    // ����� ��� ���������� ������� ������������
    double area() const;

    // ���������� ��������� ������
    friend ostream& operator<<(ostream& os, const RightTriangle& triangle);
};



