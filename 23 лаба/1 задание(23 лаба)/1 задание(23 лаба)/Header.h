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

//добавление элемента в список в конец
void AddLast(UNode& Head, UNode& Tail, int x);

//проверка на корректный ввод
bool korrec(const string& a);

//заполнение списка с клавиатуры
void Board(UNode& Tree, UNode& Tail);

//заполнение списка рандомно
void Rand(UNode& Tree, UNode& Tail);

//заполнение списка из файла
void File(UNode& Tree, UNode& Tail);

//вывод списка
void PrintSpisok(UNode& Tree, UNode& Tail);


//сортировка массива из списка
void merge(UNode& head, UNode left, UNode right);
void split(UNode& source, UNode& left, UNode& right);
void mergeSort(UNode& head);

void AddToTree(PNode& Tree, UNode& Head);

//вывод дерева при помощи обхода Мориса
vector<int> inOrder(Node* root);
