#ifndef BSTP_H
#define BSTP_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue> // Klink - Include queue for BFS

using namespace std;

struct node
{
    int data;
    node* leftChild;
    node* rightChild;

    node(int value);
};

class BST
{
    public:
        node* root;

        BST();
        ~BST();
        void clearTree(node* node);

        void insertNode(node*& root, int data);
        node* searchNode(node*& root, int data);
        void deleteNode(node*& root, int data);

        void preorder(node* root);
        void inorder(node* root);
        void postorder(node* root);

        void printTree(node* root, int space);

        // Klink - New functions
        int height(node* root); 
        int countNodes(node* root); 
        string isBalanced(); 
        void BFS(); 
        
        // Klink - Helper function to check balance and calculate height
        bool checkBalance(node* root, int& height); 
};

#endif
