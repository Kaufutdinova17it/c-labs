#include "Header.h" 
#include <iostream>   
#include <fstream>   
#include <cstdlib>    // ��� rand(), srand()
#include <ctime>      // ��� time()
#include <limits>     // ��� std::numeric_limits
#include <cctype>     // ��� isdigit
#include <string>    
#include <vector>     
#include <set>
#include <iomanip>
#include <sstream> 


using namespace std;

// ���������� ������� ������ BinaryTree
BinaryTree::BinaryTree() : root(nullptr) {}

TreeNode* BinaryTree::addNode(TreeNode* node, int value) 
{
    if (!node) 
    {
        return new TreeNode(value);
    }
    if (value < node->value) 
    {
        node->left = addNode(node->left, value);
    }
    else 
    {
        node->right = addNode(node->right, value);
    }
    return node;
}

void BinaryTree::add(int value) 
{
    root = addNode(root, value);
}
//��������� �����
void BinaryTree::installCameras(TreeNode* node, std::vector<bool>& covered, std::set<int>& cameraNodes)
{
    if (!node) return;

    // ���������� ������������� ������ ��� ������ � ������� �����������
    installCameras(node->left, covered, cameraNodes);
    installCameras(node->right, covered, cameraNodes);

    // ��������� ��������� �������� ���� � ��� �����
    bool leftCovered = (node->left == nullptr || covered[node->left->value]);
    bool rightCovered = (node->right == nullptr || covered[node->right->value]);
    bool currentCovered = covered[node->value];

    // ���� ������� ���� �� ������ � ���� �� ���� �� �������� ����� �� ������,
    // �������� ������ � ������� ����
    if (!currentCovered && (!leftCovered || !rightCovered)) {
        cameraNodes.insert(node->value); // ��������� ���� � ������������� �������
        covered[node->value] = true; // �������������, ��� ������� ���� ������

        // �������������, ��� ���� ����� �������
        if (node->left) covered[node->left->value] = true;
        if (node->right) covered[node->right->value] = true;
    }
}
void BinaryTree::cover(TreeNode* node, std::vector<bool>& covered, std::set<int>& cameraNodes) {
    if (!node) return;

    // ���� ������� ���� �� ������, ������������� ������ �� ������������ ����
    if (!covered[node->value]) {
        cameraNodes.insert(node->value);
        covered[node->value] = true; // ������������� ������� ���� ��� ��������
        if (node->left) covered[node->left->value] = true; // ��������� ������ �������
        if (node->right) covered[node->right->value] = true; // ��������� ������� �������
    }
}
//����� ���� ��� ����� ������
void BinaryTree::coverTree() 
{
    int maxSize = 100; // ������������ ���������� �����
    vector<bool> covered(maxSize, false);
    set<int> cameraNodes; // ��� �������� ����� � ��������
    installCameras(root, covered, cameraNodes);

    // ������� ���������� � �������� �����, � ������� ����������� ������
    cout << "����������� ���������� �����, ����������� ��� �������� ������: " << cameraNodes.size() << endl;
    cout << "������ ����������� � �����: ";
    for (int node : cameraNodes)
    {
        cout << node << " ";
    }
    cout << endl;
}
//����� ��������� ������
void BinaryTree::printTree(TreeNode* node)
{
    if (!node) return;
    printTree(node->left);
    cout << node->value << " ";
    printTree(node->right);
}

// ����� ��� �������� ������ ������
void BinaryTree::printTreeSideways(TreeNode* node, int level) 
{
    if (!node) return;

    // ������� ���������� �������� ������ ���������
    printTreeSideways(node->right, level + 1);

    // �������� ������� ���� � ���������
    
    cout << string(4 * level,' ') <<node->value<<endl ; // ������ ��� ������������

    // ����� ���������� �������� ����� ���������
    printTreeSideways(node->left, level + 1);
}


TreeNode* BinaryTree::getRoot() 
{
    return root;
}

// �������� ������������ �����
bool korrec(const string& a)
{
    if (a.empty()) return false;
    for (char c : a) 
    {
        if (!isdigit(c)) return false;
    }
    return true;
}

// ���� ������ � ����������
void userInput(BinaryTree& tree)
{
    string n, x;
    cout << "������� ���������� ���������: ";
    getline(cin, n);

    while (!korrec(n))
    {
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
        tree.add(stoi(x));
    }
}

// ���� ��������� ������
void randomInput(BinaryTree& tree)
{
    srand(static_cast<unsigned>(time(0)));
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
        int value = rand() % 100; // ��������� �������� �� 0 �� 99
        tree.add(value);
    }
}
//���� �� �����
void fileInput(BinaryTree& tree) 
{
    ifstream f("data.txt");
    if (!f.is_open()) {
        cout << "�� ������� ������� ����!" << endl;
        return;
    }

    string line;
    while (getline(f, line)) 
    {
        // ������� ��������� ����� ��� ��������� ������
        istringstream iss(line);
        int value;

        while (iss >> value)
        {
            tree.add(value);
        }

        // �������� �� ������� ��������, ������� �� ������� ���������
        if (iss.fail() && !iss.eof()) 
        {
            cout << "������ �����: ������������ ������ � ������: " << line << endl;
            exit(EXIT_FAILURE); // ��������� ��������� � ����� ������
        }
    }

    f.close();
}

