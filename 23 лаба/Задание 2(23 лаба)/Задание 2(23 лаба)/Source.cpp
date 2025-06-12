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

//������� ��� �������� ������������ �����
bool korrec(const string& a)
{
	if (a.empty())
		return false;// ������ ����

	for (char c : a)
	{
		if (!isdigit(c))
		{ // ���������, ��� ��� ������� - �����
			return false;
		}
	}

	return true;
}

// ���������� �������� � �������� ������ 
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

	queue<PNode> q;//���������� �������
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

//���� � ����������
void Keyboard(PNode& Tree, vector<int>& inputValues)
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string n, x;
	cout << "������� ���������� ���������: ";
	getline(cin, n);

	while (!korrec(n)) {
		cout << "\n������������ ����, ��������� ����: ";
		getline(cin, n);
	}

	for (int i = 0; i < stoi(n); i++) 
	{
		cout << "������� ����: ";
		getline(cin, x);
		while (!korrec(x)) 
		{
			cout << "\n������������ ����, ������� �����: ";
			getline(cin, x);
		}
		int value = stoi(x);
		AddToOneEl(Tree, value);
		inputValues.push_back(value); // ��������� ��������� ��������
	}
}
//���� ��������
void Random(PNode& Tree, vector<int>& inputValues)
{
	srand(static_cast<unsigned int>(time(0)));
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string n;
	cout << "������� ���������� ���������: ";
	getline(cin, n);

	while (!korrec(n)) 
	{
		cout << "\n������������ ����, ��������� ����: ";
		getline(cin, n);
	}

	for (int i = 0; i < stoi(n); i++)
	{
		int x = (rand() % 100) + 1;
		AddToOneEl(Tree, x);
		inputValues.push_back(x); // ��������� ��������� ��������
	}
}
//���� �� �����
void ToFile(PNode& Tree, vector<int>& inputValues)
{
	fstream f;
	f.open("data.txt");

	if (!f.is_open())
	{
		cout << "�� ������� ������� ����! ��������� �������." << endl;
		exit(EXIT_FAILURE); // ���������� ���������
	}

	cout << "������������ � ����� ��������: " << endl;

	string line;
	while (getline(f, line))
	{ // ������ ���� ���������
		stringstream ss(line);
		int x;

		while (ss >> x) 
		{ // ������� ������� ����� �����
			cout << x << " ";
			AddToOneEl(Tree, x);
			inputValues.push_back(x); // ��������� �������� �� �����
		}

		// �������� �� ������� ������������ ������ � ������
		if (ss.fail() && !ss.eof())
		{
			cout << "\n������������ ������ � ������: " << line << endl;
			exit(EXIT_FAILURE); // ���������� ��������� ��� ������
		}
	}

	f.close(); // ��������� ����
}
//����� ������
void Print(PNode& Tree, int level) 
{
	if (!Tree) return;

	// ������� ������� ������ ���������
	Print(Tree->right, level + 1);

	// ����� ������� ������� ���� � ��������
	cout << string(level * 4, ' ') << Tree->key << endl; // 4 ������� �� �������

	// �������, ������� ����� ���������
	Print(Tree->left, level + 1);
}


//����� ������ � ������� ������-�����-����
vector<int> inOrder(Node* root) 
{
	vector<int> res;
	Node* curr = root;

	while (curr != nullptr) 
	{
		// ���� ��� ������� �������, ������ ����� �������� ������� ����
		if (curr->right == nullptr)
		{
			res.push_back(curr->key);
			curr = curr->left;
		}
		else
		{
			// ������� ������ ������� �������� ����
			Node* prev = curr->right;

			// ���� ����� ����� ���� � ������ ���������
			while (prev->left != nullptr && prev->left != curr)
			{
				prev = prev->left;
			}

			// ���� ����� ��������� ��������, ������ ����� ������� � ������ ���������
			if (prev->left == nullptr) 
			{
				res.push_back(curr->key);
				prev->left = curr;
				curr = curr->right;
			}
			else 
			{
				// ���� ����� ��� ����, ������ ����� ������� � ����� ���������
				prev->left = nullptr;
				curr = curr->left;
			}
		}
	}

	return res;
}

