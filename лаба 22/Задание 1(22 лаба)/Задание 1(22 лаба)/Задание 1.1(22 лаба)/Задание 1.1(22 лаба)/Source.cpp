#include "Header.h"
#include <regex>
#include <fstream>
#include <stack>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

Tree::Tree() : Root(nullptr) {}
void Tree::PrintTree()
{
    Print(Root, 0);
}

void Tree::TransformTree()
{
    Root = Transform(Root);
}

int Tree::Calculate()
{
    return Calc(Root);
}

Tree::~Tree()
{
    Del(Root);
}


int Tree::Trans(const string& str)
{
    if (str == "+") return -1;
    if (str == "-") return -2;
    if (str == "*") return -3;
    if (str == "/") return -4;
    if (str == "%") return -5;
    if (str == "^") return -6;
    // преобразование строки в число
    return stoi(str);
}

char Tree::Printing(int x)
{
    if (x == -1) return '+';
    if (x == -2) return '-';
    if (x == -3) return '*';
    if (x == -4) return '/';
    if (x == -5) return '%';
    if (x == -6) return '^';
    return '?'; // если неизвестный код
}

// вывод дерева боком
void Tree::Print(PNode& Root, int level)
{
    if (Root != nullptr)
    {
        Print(Root->Right, level + 1);
        for (int i = 0; i < level; i++)
            cout << setw(4) << ' ';
        if (Root->Data < 0)
            cout << setw(4) << Printing(Root->Data) << endl;
        else
            cout << setw(4) << Root->Data << endl;
        Print(Root->Left, level + 1);
    }
}

// рекурсивное вычисление результата выражени€
int Tree::Calc(PNode Root)
{
    if (Root == nullptr) {
        cout << "ќшибка: пустой узел в Calc" << endl;
        return 0;
    }
    if (Root->Data >= 0)
        return Root->Data;

    int leftVal = Calc(Root->Left);
    int rightVal = Calc(Root->Right);

    switch (Root->Data)
    {
    case -1: return leftVal + rightVal;
    case -2: return leftVal - rightVal;
    case -3: return leftVal * rightVal;
    case -4:
        if (rightVal == 0) {
            cout << "ќшибка: деление на ноль!" << endl;
            return 0; 
        }
        return leftVal / rightVal;
    case -5:
        if (rightVal == 0) {
            cout << "ќшибка: деление по модулю на ноль!" << endl;
            return 0;
        }
        return leftVal % rightVal;
    case -6: return static_cast<int>(pow(leftVal, rightVal));
    default:
        cout << "ќшибка: неизвестный оператор в Calc" << endl;
        return 0;
    }
}

// функци€ очистки пам€ти (рекурсивное удаление)
void Tree::Del(PNode Root)
{
    if (Root != nullptr)
    {
        Del(Root->Left);
        Del(Root->Right);
        delete Root;
    }
}

// функци€ замены узлов делени€ и остатка их вычисленным значением
Tree::PNode Tree::Transform(PNode& Root)
{
    if (Root == nullptr) return nullptr;

    Root->Left = Transform(Root->Left);
    Root->Right = Transform(Root->Right);

    if (Root->Data == -4 || Root->Data == -5)
    {
        int value = Calc(Root);
        Del(Root);
        PNode newNode = new TNode;
        newNode->Data = value;
        newNode->Left = newNode->Right = nullptr;
        return newNode;
    }
    return Root;
}

// функци€ построени€ дерева из файла (на вход подаЄм им€ файла)
void Tree::BuildTreeFromFile(const char* filename)
{
    ifstream f(filename);
    if (!f) {
        cout << "ќшибка: не удалось открыть файл " << filename << endl;
        return;
    }

    string str;
    stack<PNode> st; // стек узлов

    // –егул€рное выражение дл€ проверки допустимых символов (числа или знаки +-*/%^)
    regex allowed_pattern(R"(^[0-9+\-*/%^]+$)");

    while (f >> str) {
        if (!regex_match(str, allowed_pattern)) {
            cout << "ќшибка: недопустимый символ в строке \"" << str << "\"" << endl;
            // ќчистка стека перед выходом:
            while (!st.empty()) {
                Del(st.top());
                st.pop();
            }

            return;
        }

        int op;
        try {
            op = Trans(str);
        }
        catch (const invalid_argument&) {
            cout << "ќшибка: невозможно преобразовать строку \"" << str << "\" в число" << endl;
            while (!st.empty()) {
                Del(st.top());
                st.pop();
            }
            return;
        }
        catch (const out_of_range&) {
            cout << "ќшибка: число вне допустимого диапазона в строке \"" << str << "\"" << endl;
            while (!st.empty()) {
                Del(st.top());
                st.pop();
            }
            return;
        }

        PNode t = new TNode;
        t->Data = op;
        t->Left = t->Right = nullptr;

        if (op >= 0) {
            // число Ч помещаем в стек
            st.push(t);
        }
        else {
            // операци€ Ч нужно минимум два элемента в стеке
            if (st.size() < 2) {
                cout << "ќшибка: недостаточно элементов в стеке дл€ операции \"" << str << "\"" << endl;
                delete t;
                while (!st.empty()) {
                    Del(st.top());
                    st.pop();
                }
                return;
            }
            // выт€гиваем операнды из стека
            t->Right = st.top();
            st.pop();
            t->Left = st.top();
            st.pop();

            // помещаем вновь созданный подузел обратно в стек
            st.push(t);
        }
    }

    // ¬ конце стек должен содержать только корень дерева
    if (st.size() == 1)
        Root = st.top();
    else {
        cout << "ќшибка: некорректное выражение - в стеке осталось " << st.size() << " элементов." << endl;
        while (!st.empty()) {
            Del(st.top());
            st.pop();
        }
        Root = nullptr;
    }
}

