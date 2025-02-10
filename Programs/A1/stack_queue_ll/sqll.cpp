// Name: Keenan Klinkenborg
// Program: Assignment 1 | Enqueue and Dequeue
// Date: 2/10/25

#include "sqll.h"

void push(node *&head, int value)
{
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;

    // INSERT AT INDEX 0
    newNode->next = head;
    head = newNode;
}

void pop(node *&head)
{
    if(head == nullptr){
        cout << "Stack is empty, nothing to pop" << endl;
        return;
    }

    // remove the head
    node *dltTemp = head;
    head = head->next;

    delete dltTemp;

}

void enqueue(node *&head, int value) 
{
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;

    // If queue is empty, head will become newNode.
    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    // Traverse to the last node
    node *walker = head;
    while (walker->next != nullptr)
    {
        walker = walker->next;
    }

    // Insert new node at the end
    walker->next = newNode;
}
void dequeue(node *&head) 
{
    if (head == nullptr)
    {
        cout << "Queue is empty, nothing to dequeue" << endl;
        return;
    }

    // will remove head at the front of the queue
    node *dltTemp = head;
    head = head->next;

    delete dltTemp;
}

void displayList(node *head)
{
    node *walker = head;

    while(walker != nullptr){
        cout << walker->data << " ";
        walker = walker->next;
    }
    cout << endl;
}