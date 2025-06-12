#include <set>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <set>  // Для хранения узлов с установленными камерами

using namespace std;

struct TreeNode 
{
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinaryTree
{
private:
    TreeNode* root;

    // Рекурсивная функция для добавления узлов в дерево
    TreeNode* addNode(TreeNode* node, int value);
    // Обход для размещения камер
    void installCameras(TreeNode* node, vector<bool>& covered, set<int>& cameraNodes);

public:
    BinaryTree();
    void add(int value);
    void coverTree();
    void printTree(TreeNode* node);
    void printTreeSideways(TreeNode* node, int level = 0); // Обновленный метод
    TreeNode* getRoot();
    void cover(TreeNode* node, std::vector<bool>& covered, std::set<int>& cameraNodes);
};

bool korrec(const string& a);
void userInput(BinaryTree& tree);
void randomInput(BinaryTree& tree);
void fileInput(BinaryTree& tree);



