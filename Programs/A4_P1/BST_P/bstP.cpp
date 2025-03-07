// Name: Keenan Klinkenborg
// Program: Assignment 4 P1 | BST with Arrays and Lists
// Date: 3/06/25

#include "bstP.h"

node::node(int value)
{
    data = value;
    leftChild = nullptr;
    rightChild = nullptr;
}

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(node* node)
{
    if(node == nullptr)
        return;
    
    clearTree(node->leftChild);
    clearTree(node->rightChild);
    delete node;
}

void BST::insertNode(node*& root, int data)
{
    if(root == nullptr)
    {
        root = new node(data);
        return;
    }

    if(data < root->data)
        insertNode(root->leftChild, data);
    else if(data > root->data)
        insertNode(root->rightChild, data); //Klink - Avoid duplicate insertions
}

node* BST::searchNode(node*& root, int data)
{
    if (root == nullptr || root->data == data)
        return root;
    if (data < root->data)
        return searchNode(root->leftChild, data);
    return searchNode(root->rightChild, data);
}

void BST::deleteNode(node*& root, int data)
{
    if (root == nullptr)
        return;

    if (data < root->data)
        deleteNode(root->leftChild, data);
    else if (data > root->data)
        deleteNode(root->rightChild, data);
    else {
        if (root->leftChild == nullptr) {
            node* temp = root->rightChild;
            delete root;
            root = temp;
        }
        else if (root->rightChild == nullptr) {
            node* temp = root->leftChild;
            delete root;
            root = temp;
        }
        else {
            node* temp = root->rightChild;
            while (temp->leftChild != nullptr)
                temp = temp->leftChild;
            root->data = temp->data;
            deleteNode(root->rightChild, temp->data);
        }
    }
}

void BST::preorder(node* root)
{
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorder(root->leftChild);
    preorder(root->rightChild);
}

void BST::inorder(node* root)
{
    if (root == nullptr)
        return;
    inorder(root->leftChild);
    cout << root->data << " ";
    inorder(root->rightChild);
}

void BST::postorder(node* root)
{
    if (root == nullptr)
        return;
    postorder(root->leftChild);
    postorder(root->rightChild);
    cout << root->data << " ";
}

void BST::printTree(node* root, int space)
{
    const int COUNT = 10;
    if (root == nullptr)
        return;
    space += COUNT;
    printTree(root->rightChild, space);
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->data << endl;
    printTree(root->leftChild, space);
}

//Klink - Computes the height of the BST recursively
int BST::height(node* root)
{
    if (root == nullptr)
        return -1; // Base case: empty node contributes -1 to height

    // Recursive case: max depth of left or right subtree
    return 1 + max(height(root->leftChild), height(root->rightChild));
}

//Klink - Counts the number of nodes in the BST recursively
int BST::countNodes(node* root)
{
    if (root == nullptr)
        return 0; // Base case: no node here

    // Recursive case: count current node + left subtree + right subtree
    return 1 + countNodes(root->leftChild) + countNodes(root->rightChild);
}

// Klink - Checks if the BST is balanced based on height differences between the left and right subtrees.
string BST::isBalanced()
{
    int leftHeight = height(root->leftChild);    
    int rightHeight = height(root->rightChild);

    if (abs(leftHeight - rightHeight) <= 1)
        return "Yes";
    return (leftHeight > rightHeight) ? "Left-heavy" : "Right-heavy";
}


// Klink - Helper function to recursively check balance and calculate height
bool BST::checkBalance(node* root, int& height)
{
    if (root == nullptr) {
        height = -1; // Base case: empty node contributes -1 to height
        return true; // Empty node is considered balanced
    }

    // Recursively check the left subtree
    int leftHeight = 0;
    bool leftBalanced = checkBalance(root->leftChild, leftHeight);

    // Recursively check the right subtree
    int rightHeight = 0;
    bool rightBalanced = checkBalance(root->rightChild, rightHeight);

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
void BST::BFS()
{
    queue<node*> q;
    if (root == nullptr)
        return; // Empty tree

    q.push(root); // Start with the root

    while (!q.empty()) {
        node* currentNode = q.front();
        q.pop();

        cout << currentNode->data << " ";

        if (currentNode->leftChild != nullptr)
            q.push(currentNode->leftChild);
        if (currentNode->rightChild != nullptr)
            q.push(currentNode->rightChild);
    }
}
