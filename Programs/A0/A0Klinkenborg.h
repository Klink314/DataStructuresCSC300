// Name: Keenan Klinkenborg
// Program: Assignment 0 | Linker Loader
// Date: 1/26/25

#ifndef A0KLINKENBORG_H
#define A0KLINKENBORG_H

#include <iostream>
#include <cctype>
#include <string>

using namespace std;

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

// *head = nullptr;

//task 1
void insertNode(node *&head, int index, int data);
void deleteNode(node *&head, int index);
node* searchNode (node *head, int key);
void displayList(node *head);

//task 2
void reverseList(node *&head);

//error checking 
int getValidNumber();

#endif