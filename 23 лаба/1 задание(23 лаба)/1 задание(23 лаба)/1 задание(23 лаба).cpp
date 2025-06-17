#include <iostream>
#include <vector>
#include"Header.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

//функция для проверки корректности ввода
bool korrec(const string& a)
{
	if (a.empty())
		return false;// Пустой ввод

	for (char c : a)
	{
		if (!isdigit(c))
		{ // Проверяем, что все символы - цифры
			return false;
		}
	}

	return true;
}
//соеденяет 2 отсортированных списка вместе
void merge(UNode& head, UNode left, UNode right) {
	if (!left) {
		head = right;
		return;
	}
	if (!right)
	{
		head = left;
		return;
	}

	if (left->x <= right->x)
	{
		head = left;
		merge(head->next, left->next, right);
		if (head->next) head->next->prev = head;
	}
	else
	{
		head = right;
		merge(head->next, left, right->next);
		if (head->next) head->next->prev = head;
	}

	head->prev = nullptr;
}
//разделение на два подсписка
void split(UNode& p, UNode& left, UNode& right)
{
	UNode fast = p;
	UNode slow = p;
	UNode prev = nullptr;

	//Использует два указателя - slow (движется на один узел) и fast (движется на два узла), чтобы найти середину списка. Когда fast достигает конца, slow будет на середине.

	while (fast && fast->next)
	{
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}
	//prev сохраняет предшествующий узел для slow, чтобы отделить первую половину списка от второй.
	if (prev) prev->next = nullptr;
	left = p;
	right = slow;

	if (right) right->prev = nullptr;
}
//алгоритм сортировки слиянием для двусвязного списка.
void mergeSort(UNode& head)
{
	if (!head || !head->next) return;

	UNode left = nullptr;
	UNode right = nullptr;

	split(head, left, right);

	mergeSort(left);
	mergeSort(right);

	merge(head, left, right);
}

//добавление элемента в список в конец
void AddLast(UNode& Head, UNode& Tail, int x)
{
	UNode NewUsel = new Usel;
	NewUsel->next = NULL;
	NewUsel->prev = Tail;
	NewUsel->x = x;
	if (Tail) Tail->next = NewUsel;
	Tail = NewUsel;
	if (Head == NULL) Head = Tail; // этот элемент – первый  
}

//заполнение списка с клавиатуры
void Board(UNode& Tree, UNode& Tail)
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string n, x;
	cout << "Введите количество элементов: ";
	getline(cin, n);

	while (!korrec(n))
	{
		cout << "\nНекорректный ввод, повторите ввод: ";
		getline(cin, n);
	}

	for (int i = 0; i < stoi(n); i++)
	{
		cout << "Введите ключ: ";
		getline(cin, x);
		while (!korrec(x))
		{
			cout << "\nНекорректный ввод, введите число: ";
			getline(cin, x);
		}
		AddLast(Tree, Tail, stoi(x));
	}
}

//заполнение списка рандомно
void Rand(UNode& Tree, UNode& Tail)
{
	srand(time(0));
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string n;
	int a;
	cout << "Введите количество элементов: ";
	getline(cin, n);

	while (!korrec(n))
	{
		cout << "\nНекорректный ввод, повторите ввод: ";
		getline(cin, n);
	}
	for (int i = 0; i < stoi(n); i++)
	{
		a = (rand() % 100) + 1;
		AddLast(Tree, Tail, a);
	}
}

//заполнение списка из файла
void File(UNode& Tree, UNode& Tail)
{
	int x;
	fstream f;
	bool isLeft = true; // начинаем с левого поддерева
	f.open("Spisok.txt");
	if (!f.is_open())
	{
		cout << "Повторите попытку!";
		return;
	}
	if (!(f >> x))
	{
		cout << "Файл пуст или содержит некорректные данные, повторите попытку" << endl;
		return;
	}
	cout << "Содержащиеся в файле элементы: " << endl;
	do
	{
		cout << x << " ";
		AddLast(Tree, Tail, x);
	} while (f >> x);
}

//вывод списка
void PrintSpisok(UNode& Tree, UNode& Tail) {
	if (Tree == NULL)
	{
		cout << "Дерево пустое!";
	}
	else
	{
		UNode p = Tree;
		cout << "\nСоставленный список: " << endl;
		while (p)
		{
			cout << p->x << " ";
			p = p->next;
		}
	}
}
//редназначена для преобразования связного списка в сбалансированное бинарное дерево поиска (BST)
void AddToTree(PNode& Tree, UNode& Head)
{
	if (!Head) {
		return;
	}

	// Находим средний элемент списка
	UNode slow = Head;
	UNode fast = Head;
	UNode prev = NULL;

	// Используем два указателя для нахождения среднего элемента
	while (fast && fast->next)
	{
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	// slow на средний элемент
	Tree = new Node;
	Tree->key = slow->x;
	Tree->left = NULL;
	Tree->right = NULL;

	// Теперь нужно разделить список на левую и правую стороны
	if (prev)
	{
		prev->next = NULL; // Разделяем список на две части
		AddToTree(Tree->left, Head);
	}

	// Отделяем средний элемент от левой части списка
	UNode rightHead = slow->next;
	slow->next = NULL;
	AddToTree(Tree->right, rightHead);
}




//вывод дерева
void Print(PNode& Tree, string const& rpref, string const& cpref, string const& lpref)
{
	if (!Tree) return;
	if (Tree->right)
		Print(Tree->right, rpref + "   ", rpref + " +--", rpref + " | ");
	cout << cpref << to_string(Tree->key) << endl;
	if (Tree->left)
		Print(Tree->left, lpref + " | ", lpref + " +--", lpref + "   ");
}

//вывод дерева алгоритмом Мориса
vector<int> inOrder(Node* root)
{
	vector<int> res;
	Node* curr = root;

	while (curr != nullptr)
	{
		// Если нет правого потомка, значит нужно посетить текущий узел
		if (curr->right == nullptr)
		{
			res.push_back(curr->key);
			curr = curr->left;
		}
		else {
			// Находим правый потомок текущего узла
			Node* prev = curr->right;

			// Ищем самый левый узел в правом поддереве
			while (prev->left != nullptr && prev->left != curr)
			{
				prev = prev->left;
			}

			// Если левый указатель свободен, значит нужно перейти в правое поддерево
			if (prev->left == nullptr)
			{
				res.push_back(curr->key);
				prev->left = curr;
				curr = curr->right;
			}
			else
			{
				// Если связь уже есть, значит нужно перейти в левое поддерево
				prev->left = nullptr;
				curr = curr->left;
			}
		}
	}

	return res;
}

int main()
{
	setlocale(LC_ALL, "rus");
	PNode head = NULL; // Указатель на корень дерева в первом задании
	PNode Head = NULL;//Указатель на корень для второго дерева
	UNode UHead = NULL, Tail = NULL;//указатели на двухсвязный список
	int c;//выбор для заполнения списка
	cout << "Программа работает только с целыми неотрицательными числами" << endl;
	cout << "1 - с клавиатуры, 2 - рандомно, 3 - из файла" << endl << "Выберите способ заполнения двухсвязного списка: ";
	cin >> c;

	switch (c) {
	case 1:
		Board(UHead, Tail);
		break;
	case 2:
		Rand(UHead, Tail);
		break;
	case 3:
		File(UHead, Tail);
		break;
	default:
		cout << "Нет такого способа заполнения";
		return 1;
	}
	PrintSpisok(UHead, Tail);
	mergeSort(UHead);
	cout << "\nИзменённый список " << endl;
	PrintSpisok(UHead, Tail);
	cout << "Дерево: " << endl;
	AddToTree(head, UHead);
	string rpref = "";
	string cpref = "";
	string lpref = "";
	Print(head, rpref, cpref, lpref);
	cout << "Вывод дерева обходом Мориса: ";
	vector<int> res = inOrder(head);
	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << " ";
	};
	return 0;



}