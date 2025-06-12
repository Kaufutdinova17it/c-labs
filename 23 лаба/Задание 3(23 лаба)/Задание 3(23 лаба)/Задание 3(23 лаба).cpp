#include "Header.h"
#include <set>
#include <iomanip>
#include <iostream>
#include <iostream>   // Для  cin
#include <string>     // Для std::string, std::getline, stoi
#include <clocale>    // Для setlocale
#include <limits>   
/*TreeFun9. Ученые изучают поведение птиц, вьющих гнезда на бинарном дереве, и хотят
разместить в его узлах камеры. Каждая камера может обозревать узел, в котором она
расположена, а также непосредственного предка и непосредственных потомков этого узла. По
заданному бинарному дереву требуется определить, какое минимальное количество камер
потребуется ученым для того, чтобы полностью покрыть наблюдением все узлы дерева.*/


using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    BinaryTree tree;

    int choice;
    cout << "Выберите способ ввода данных:\n1. С клавиатуры\n2. Случайно\n3. Из файла\n";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем поток ввода после выбора

    switch (choice) 
    {
    case 1:
        userInput(tree);
        break;
    case 2:
        randomInput(tree);
        break;
    case 3:
        fileInput(tree);
        break;
    default:
        cout << "Некорректный выбор!" << endl;
        return 1;
    }

    cout << "Содержимое дерева в порядке возрастания: ";
    tree.printTree(tree.getRoot());
    cout << endl;
    // Вывод дерева боком
    cout << "Дерево в боковом виде:\n";
    tree.printTreeSideways(tree.getRoot());
    cout << endl;

    tree.coverTree();
    return 0;
}


