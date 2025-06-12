#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//�������� ���� ��������� ������
class Node
{
public:
	int key; // �������������� ���� (����)
	Node* left, * right; // ��������� �� �������
};
typedef Node* PNode; // ��������� �� �������

//�������� ���� ������������ ������
class Usel
{
public:
	int x;
	Usel* next, * prev; // ������ �� �������� ���� 
};
typedef Usel* UNode; // ��� ������ ���������� �� ���� 

//�������� �� ���������� ����
bool korrec(const string& a);

//���������� �������� � ������
void AddToOneEl(PNode& Tree, int data);

void Keyboard(PNode& Tree, vector<int>& inputValues); // ���������� �� vector<int>

// ���������� ������ ���������� �������
void Random(PNode& Tree, vector<int>& inputValues); // ���������� �� vector<int>

// ���������� ������ �� �����
void ToFile(PNode& Tree, vector<int>& inputValues);

//����� ������
void Print(PNode& Tree,int level=0);

//����� ������ ������-�����-����
vector<int> inOrder(Node* root);



