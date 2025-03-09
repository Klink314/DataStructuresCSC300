#include "reserve.h"

reservation::reservation(int t) {
    time = t;
    left = nullptr;
    right = nullptr; 
}


BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(reservation* node)
{
    if (root == nullptr)
        return;

    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// reserve new landing time
bool BST::reserve(int time) 
{
    if (checkConflict(root, time)) {
        return false; // conflict - reservation fails
    }
 
    insert(root, time); 
    return true; // no conflict - reservation successful
}

// check for landing time conflicts within 3 minutes (Use recursion)
bool BST::checkConflict(reservation* node, int time) 
{
    //Klink
    if (node == nullptr)
        return false;  // No node here, no conflict

    if (abs(node->time - time) < 3)
        return true;   // Conflict found within 3 minutes

    if (time < node->time)
        return checkConflict(node->left, time);  // Go left
    else
        return checkConflict(node->right, time); // Go right
}

// insert new reservation and update subtree size (make sure to avoid inserting duplicates)
void BST::insert(reservation*& node, int time) 
{
    // Empty spot found, insert here
    if (node == nullptr) {
        node = new reservation(time);
        node->subtreeSize = 1;
        return;
    }

    // Duplicate time safeguard
    if (time == node->time)
        return;

    // Recurse to left or right
    if (time < node->time)
        insert(node->left, time);
    else
        insert(node->right, time);

    // Update node's subtreeSize after insertion
    int leftSize = (node->left != nullptr) ? node->left->subtreeSize : 0;
    int rightSize = (node->right != nullptr) ? node->right->subtreeSize : 0;

    node->subtreeSize = 1 + leftSize + rightSize;
}

// Count nodes with times <= t
int BST::countPlanes(reservation* node, int t) 
{
    if (node == nullptr)
        return 0;  

    if (node->time <= t) {
        int leftSize = (node->left != nullptr) ? node->left->subtreeSize : 0;
        return 1 + leftSize + countPlanes(node->right, t);
    } else {
        return countPlanes(node->left, t);
    }
}

void BST::inorder(reservation* root)
{
    if (root == nullptr)
        return;
    
    inorder(root->left);
    cout << root->time << " ";
    inorder(root->right);
}