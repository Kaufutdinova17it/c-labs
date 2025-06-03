#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <stack>
#include <cmath> // для pow
//5+7-8/2+9
//5 7 + 8 2 / - 9 +  
//=17

//8+4/2-6+9*8
//8 4 2 / + 6 - 9 8 * +
//=76

//4+2/1-2+8/4
//4 2 1 / + 2 - 8 4 / +
//=6
using namespace std;

class Tree
{
private:
    struct TNode
    {
        int Data;
        TNode* Left;
        TNode* Right;
    };
    typedef TNode* PNode;

    PNode Root;

    int Trans(const string& str);
    char Printing(int x);
    void Print(PNode& Root, int level);
    int Calc(PNode Root);
    void Del(PNode Root);
    PNode Transform(PNode& Root);

public:
    Tree();
    void BuildTreeFromFile(const char* filename);
    void PrintTree();
    void TransformTree();
    int Calculate();
    ~Tree();
};