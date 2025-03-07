// Name: Keenan Klinkenborg
// Program: Assignment 4 P1 | BST with Arrays and Lists
// Date: 3/06/25

#include "bstA.h"

BST::BST(int size)
{
    capacity = size;
    tree = new int[capacity];
    for(int i = 0; i < size; i++)
        tree[i] = INT_MIN;
}

BST::~BST()
{
    delete[] tree;
}

int BST::leftChild(int index)
{
    return 2 * index + 1;
}

int BST::rightChild(int index)
{
    return 2 * index + 2;
}

int BST::parent(int index)
{
    return (index - 1) / 2;
}

void BST::insertI(int data)
{
    if(tree[0] == INT_MIN)
    {
        tree[0] = data;
        return;
    }

    int index = 0;

    while(index < capacity)
    {
        if(tree[index] == data) //Klink - Ignore duplicates
            return;

        if(data < tree[index])
        {
            if(leftChild(index) < capacity && tree[leftChild(index)] == INT_MIN)
            {
                tree[leftChild(index)] = data;
                return;
            }
            index = leftChild(index);
        } 
        else 
        {
            if(rightChild(index) < capacity && tree[rightChild(index)] == INT_MIN)
            {
                tree[rightChild(index)] = data;
                return;
            }
            index = rightChild(index);
        }
    }
}

void BST::insertR(int data)
{
    insertRhelper(0, data);
}

void BST::insertRhelper(int index, int data)
{
    // Base case
    if(index >= capacity)
        return;
    if(tree[index] == INT_MIN)
    {
        tree[index] = data;
        return;
    }
    if(tree[index] == data) //Klink - Ignore duplicates
        return;

    // Recursive case
    if (data < tree[index])
        insertRhelper(leftChild(index), data);
    else
        insertRhelper(rightChild(index), data);
}

bool BST::searchI(int data)
{
    int index = 0;

    while(index < capacity)
    {
        if(tree[index] == INT_MIN)
            return false;
        if(tree[index] == data)
            return true;
        if(data < tree[index])
            index = leftChild(index); 
        else
            index = rightChild(index);
    }

    return false;
}

bool BST::searchR(int data)
{
    return searchRhelper(0, data);
}

bool BST::searchRhelper(int index, int data)
{
    // Base case
    if(index >= capacity || tree[index] == INT_MIN)
        return false;
    if(tree[index] == data)
        return true;

    // Recursive case
    if(data < tree[index])
        return searchRhelper(leftChild(index), data);
    else
        return searchRhelper(rightChild(index), data);
}

void BST::preorder(int index) // C-L-R
{
    // base case
    if (index >= capacity || tree[index] == INT_MIN)
        return;

    // recursive case
    cout << tree[index] << " ";
    preorder(leftChild(index));
    preorder(rightChild(index));
}

void BST::inorder(int index) // L-C-R
{
    // base case
    if (index >= capacity || tree[index] == INT_MIN)
        return;

    // recursive case
    inorder(leftChild(index));
    cout << tree[index] << " ";
    inorder(rightChild(index));
}

void BST::postorder(int index) // L-R-C
{
    // base case
    if (index >= capacity || tree[index] == INT_MIN)
        return;

    // recursive case
    postorder(leftChild(index));
    postorder(rightChild(index));
    cout << tree[index] << " ";
}

void BST::printTree(int index, int depth = 0)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;
    
    printTree(rightChild(index), depth + 1);

    for(int i = 0; i < depth; i++)
        cout << "   "; // for indentation
    cout << tree[index] << endl;

    printTree(leftChild(index), depth + 1);
}

//Klink - Computes the height of the BST recursively
int BST::height(int index) {
    if (index >= capacity || tree[index] == INT_MIN)
        return -1; // Base case: empty node contributes -1 to height

    // Recursive case: max depth of left or right subtree
    return 1 + max(height(leftChild(index)), height(rightChild(index)));
}

//Klink - Counts the number of nodes in the BST recursively
int BST::countNodes(int index) {
    if (index >= capacity || tree[index] == INT_MIN)
        return 0; // Base case: no node here

    // Recursive case: count current node + left subtree + right subtree
    return 1 + countNodes(leftChild(index)) + countNodes(rightChild(index));
}


string BST::isBalanced() {
    int height = 0;
    bool balanced = checkBalance(0, height);  // Start from the root (index 0)
    return balanced ? "Yes" : (height > 0 ? "Left-heavy" : "Right-heavy");
}

// This function checks if the subtree is balanced and also calculates its height.
bool BST::checkBalance(int index, int &height) {
    if (index >= capacity || tree[index] == INT_MIN) {
        height = -1;  // Base case: empty node contributes -1 to height
        return true;  // Empty node is considered balanced
    }

    // Recursively check the left subtree
    int leftHeight = 0;
    bool leftBalanced = checkBalance(leftChild(index), leftHeight);

    // Recursively check the right subtree
    int rightHeight = 0;
    bool rightBalanced = checkBalance(rightChild(index), rightHeight);

    // Calculate the height of the current node
    height = max(leftHeight, rightHeight) + 1;

    // If any subtree is unbalanced or if the current node is unbalanced, return false
    if (!leftBalanced || !rightBalanced || abs(leftHeight - rightHeight) > 1) {
        return false;  // The tree is unbalanced
    }

    // Otherwise, the tree is balanced
    return true;
}


//Klink - Performs a breadth-first traversal of the BST using a queue.
void BST::BFS() {
    queue<int> q;
    if (tree[0] == INT_MIN)
        return; // Empty tree, no traversal needed

    q.push(0); // Start with the root

    while (!q.empty()) {
        int index = q.front();
        q.pop();

        cout << tree[index] << " ";

        if (leftChild(index) < capacity && tree[leftChild(index)] != INT_MIN)
            q.push(leftChild(index));
        if (rightChild(index) < capacity && tree[rightChild(index)] != INT_MIN)
            q.push(rightChild(index));
    }
}
