#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//описание узла бинарного дерева
class Node
{
public:
	int key; // информационное поле (ключ)
	Node* left, * right; // указатели на сыновей
};
typedef Node* PNode; // указатель на вершину

//описание узла двухсвязного списка
class Usel
{
public:
	int x;
	Usel* next, * prev; // ссылки на соседние узлы 
};
typedef Usel* UNode; // тип данных «указатель на узел» 

//проверка на корректный ввод
bool korrec(const string& a);

//добавление элемента в дерево
void AddToOneEl(PNode& Tree, int data);

void Keyboard(PNode& Tree, vector<int>& inputValues); // Исправлено на vector<int>

// Заполнение дерева случайными числами
void Random(PNode& Tree, vector<int>& inputValues); // Исправлено на vector<int>

// Заполнение дерева из файла
void ToFile(PNode& Tree, vector<int>& inputValues);

//вывод дерева
void Print(PNode& Tree,int level=0);

//вывод дерева корень-право-лево
vector<int> inOrder(Node* root);



