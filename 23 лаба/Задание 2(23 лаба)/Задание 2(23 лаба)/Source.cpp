#include <iostream>
#include "Header.h"
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>
#include <stack>
#include <sstream>

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

// Добавление элемента в бинарное дерево 
void AddToOneEl(PNode& Tree, int data)
{
	if (!Tree) 
	{
		Tree = new Node;
		Tree->key = data;
		Tree->left = NULL;
		Tree->right = NULL;
		return;
	}

	queue<PNode> q;//используем очередь
	q.push(Tree);

	while (!q.empty()) 
	{
		PNode current = q.front();
		q.pop();

		if (!current->left) 
		{
			current->left = new Node;
			current->left->key = data;
			current->left->left = NULL;
			current->left->right = NULL;
			return;
		}
		else if (!current->right)
		{
			current->right = new Node;
			current->right->key = data;
			current->right->left = NULL;
			current->right->right = NULL;
			return;
		}
		else {
			q.push(current->left);
			q.push(current->right);
		}
	}
}

//ввод с клавиатуры
void Keyboard(PNode& Tree, vector<int>& inputValues)
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string n, x;
	cout << "Введите количество элементов: ";
	getline(cin, n);

	while (!korrec(n)) {
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
		int value = stoi(x);
		AddToOneEl(Tree, value);
		inputValues.push_back(value); // Сохраняем введенное значение
	}
}
//ввод рандомом
void Random(PNode& Tree, vector<int>& inputValues)
{
	srand(static_cast<unsigned int>(time(0)));
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string n;
	cout << "Введите количество элементов: ";
	getline(cin, n);

	while (!korrec(n)) 
	{
		cout << "\nНекорректный ввод, повторите ввод: ";
		getline(cin, n);
	}

	for (int i = 0; i < stoi(n); i++)
	{
		int x = (rand() % 100) + 1;
		AddToOneEl(Tree, x);
		inputValues.push_back(x); // Сохраняем случайное значение
	}
}
//ввод из файла
void ToFile(PNode& Tree, vector<int>& inputValues)
{
	fstream f;
	f.open("data.txt");

	if (!f.is_open())
	{
		cout << "Не удалось открыть файл! Повторите попытку." << endl;
		exit(EXIT_FAILURE); // Завершение программы
	}

	cout << "Содержащиеся в файле элементы: " << endl;

	string line;
	while (getline(f, line))
	{ // Читаем файл построчно
		stringstream ss(line);
		int x;

		while (ss >> x) 
		{ // Попытка извлечь целое число
			cout << x << " ";
			AddToOneEl(Tree, x);
			inputValues.push_back(x); // Сохраняем значение из файла
		}

		// Проверка на наличие некорректных данных в строке
		if (ss.fail() && !ss.eof())
		{
			cout << "\nНекорректные данные в строке: " << line << endl;
			exit(EXIT_FAILURE); // Завершение программы при ошибке
		}
	}

	f.close(); // Закрываем файл
}
//вывод дерева
void Print(PNode& Tree, int level) 
{
	if (!Tree) return;

	// Сначала выводим правое поддерево
	Print(Tree->right, level + 1);

	// Затем выводим текущий узел с отступом
	cout << string(level * 4, ' ') << Tree->key << endl; // 4 пробела на уровень

	// Наконец, выводим левое поддерево
	Print(Tree->left, level + 1);
}


//вывод дерева в порядке корень-право-лево
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
		else
		{
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

