#include "Header.h" 
#include <iostream>   
#include <fstream>   
#include <cstdlib>    // Для rand(), srand()
#include <ctime>      // Для time()
#include <limits>     // Для std::numeric_limits
#include <cctype>     // Для isdigit
#include <string>    
#include <vector>     
#include <set>
#include <iomanip>
#include <sstream> 


using namespace std;

// Реализация методов класса BinaryTree
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
//установка камер
void BinaryTree::installCameras(TreeNode* node, std::vector<bool>& covered, std::set<int>& cameraNodes)
{
    if (!node) return;

    // Рекурсивно устанавливаем камеры для левого и правого поддеревьев
    installCameras(node->left, covered, cameraNodes);
    installCameras(node->right, covered, cameraNodes);

    // Проверяем состояние текущего узла и его детей
    bool leftCovered = (node->left == nullptr || covered[node->left->value]);
    bool rightCovered = (node->right == nullptr || covered[node->right->value]);
    bool currentCovered = covered[node->value];

    // Если текущий узел не покрыт и хотя бы один из дочерних узлов не покрыт,
    // помещаем камеру в текущий узел
    if (!currentCovered && (!leftCovered || !rightCovered)) {
        cameraNodes.insert(node->value); // Сохраняем узел с установленной камерой
        covered[node->value] = true; // Устанавливаем, что текущий узел покрыт

        // Устанавливаем, что дети также покрыты
        if (node->left) covered[node->left->value] = true;
        if (node->right) covered[node->right->value] = true;
    }
}
void BinaryTree::cover(TreeNode* node, std::vector<bool>& covered, std::set<int>& cameraNodes) {
    if (!node) return;

    // Если текущий узел не покрыт, устанавливаем камеру на родительский узел
    if (!covered[node->value]) {
        cameraNodes.insert(node->value);
        covered[node->value] = true; // Устанавливаем текущий узел как покрытый
        if (node->left) covered[node->left->value] = true; // Покрываем левого ребенка
        if (node->right) covered[node->right->value] = true; // Покрываем правого ребенка
    }
}
//вывод мест где стоят камеры
void BinaryTree::coverTree() 
{
    int maxSize = 100; // Максимальное количество узлов
    vector<bool> covered(maxSize, false);
    set<int> cameraNodes; // Для хранения узлов с камерами
    installCameras(root, covered, cameraNodes);

    // Выводим количество и значения узлов, в которых расположены камеры
    cout << "Минимальное количество камер, необходимых для покрытия дерева: " << cameraNodes.size() << endl;
    cout << "Камеры установлены в узлах: ";
    for (int node : cameraNodes)
    {
        cout << node << " ";
    }
    cout << endl;
}
//вывод элементов дерева
void BinaryTree::printTree(TreeNode* node)
{
    if (!node) return;
    printTree(node->left);
    cout << node->value << " ";
    printTree(node->right);
}

// метод для бокового вывода дерева
void BinaryTree::printTreeSideways(TreeNode* node, int level) 
{
    if (!node) return;

    // Сначала рекурсивно печатаем правое поддерево
    printTreeSideways(node->right, level + 1);

    // Печатаем текущий узел с отступами
    
    cout << string(4 * level,' ') <<node->value<<endl ; // Отступ для визуализации

    // Затем рекурсивно печатаем левое поддерево
    printTreeSideways(node->left, level + 1);
}


TreeNode* BinaryTree::getRoot() 
{
    return root;
}

// Проверка корректности ввода
bool korrec(const string& a)
{
    if (a.empty()) return false;
    for (char c : a) 
    {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Ввод данных с клавиатуры
void userInput(BinaryTree& tree)
{
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
        tree.add(stoi(x));
    }
}

// Ввод случайных данных
void randomInput(BinaryTree& tree)
{
    srand(static_cast<unsigned>(time(0)));
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
        int value = rand() % 100; // Случайное значение от 0 до 99
        tree.add(value);
    }
}
//ввод из файла
void fileInput(BinaryTree& tree) 
{
    ifstream f("data.txt");
    if (!f.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return;
    }

    string line;
    while (getline(f, line)) 
    {
        // Создаем строковый поток для обработки строки
        istringstream iss(line);
        int value;

        while (iss >> value)
        {
            tree.add(value);
        }

        // Проверка на наличие символов, которые не удалось прочитать
        if (iss.fail() && !iss.eof()) 
        {
            cout << "Ошибка ввода: некорректные данные в строке: " << line << endl;
            exit(EXIT_FAILURE); // Завершаем программу с кодом ошибки
        }
    }

    f.close();
}

