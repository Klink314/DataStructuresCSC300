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
};

// *head = nullptr;

void insertNode(node *&head, int index, int data);
void deleteNode(node *&head, int index);
node* searchNode (node *head, int key);
void displayList(node *head);

int getValidNumber();

#endif