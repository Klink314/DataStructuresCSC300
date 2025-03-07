// Name: Keenan Klinkenborg
// Program: Assignment 4 P1 | BST with Arrays and Lists
// Date: 3/06/25
#ifndef BSTA_H
#define BSTA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue> //Klink - Added for BFS

using namespace std;

class BST
{
    private:
        int* tree;
        int capacity;

        int leftChild(int index);
        int rightChild(int index);
        int parent(int index);

        // Klink - Add checkBalance declaration 
        bool checkBalance(int index, int &height);

    public:
        BST(int size);
        ~BST();

        void insertI(int data);
        void insertR(int data);
        void insertRhelper(int index, int data);

        bool searchI(int data);
        bool searchR(int data);
        bool searchRhelper(int index, int data);

        void preorder(int index = 0);
        void inorder(int index = 0);
        void postorder(int index = 0);

        void printTree(int index, int depth);

        //Klink - Added function declarations
        int height(int index);
        int countNodes(int index);
        string isBalanced();
        void BFS();
};

#endif
