// Name: Keenan Klinkenborg
// Program: Assignment 1 | Enqueue and Dequeue
// Date: 2/10/25

#include "sqdll.h"

void enqueueFront(node *&head, node *&tail, int value)
{
    // Create the node to be inserted at the front
    node *newNode = new node;
    newNode->data = value;
    newNode->next = head;     
    newNode->prev = nullptr;  

    // If the deque is emtpty, then newNode also becomes both the head and the tail
    if (head == nullptr)
    {
        head = tail = newNode;
    }
    else // If not empty, just make newNode the head
    { 
        head->prev = newNode;
        head = newNode;
    }

}

void enqueueBack(node *&head, node *&tail, int value)
{
    // create new node
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = tail;

    // if dequeue is empty, newNode will become the head and tail
    if (tail == nullptr)
    {
        head = tail = newNode;
    }
    else // links tail to new node and updates tail
    {
        tail->next = newNode;
        tail = newNode;
    }
}

void dequeueFront(node *&head, node *&tail)
{
    if (head == nullptr)
    {
        cout << "Dequeue is empty, nothing to dequeue from front" << endl;
        return;
    }

    node *dltTemp = head;
    head = head->next;

    // if dequeue is empty set tail to null as well
    if (head == nullptr)
    {
        tail = nullptr;
    }
    else
    {
        head->prev = nullptr;
    }

    delete dltTemp;
}

void dequeueBack(node *&head, node *&tail)
{
    if (tail == nullptr)
    {
        cout << "Dequeue is empty, nothing to dequeue from back" << endl;
        return;
    }

    node *dltTemp = tail;
    //moves tail backwards
    tail = tail->prev;

    //if dequeue is empty, head is now null
    if (tail == nullptr)
    {
        head = nullptr;
    }
    else
    {
        tail->next = nullptr;
    }

    delete dltTemp;
}

void displayList(node *head)
{
    node *walker = head;

    while(walker != nullptr){
        cout << walker->data << " ";
        walker = walker -> next;
    }
    cout << endl;
}
