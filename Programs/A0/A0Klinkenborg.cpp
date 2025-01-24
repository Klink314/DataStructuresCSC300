#include "A0Klinkenborg.h"

void insertNode(node *&head, int index, int data)
{
    node* newNode = new node;
    newNode->data = data;
    newNode->next = nullptr;

    // insert at the bag
    if (index == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        node* walker = head;
        int wIndex = 0;

        // walking to that index
        while (walker != NULL && wIndex < index - 1)
        {
            walker = walker->next;
            wIndex++;
        }

        if (walker == nullptr)
        {
            cout << "Index is too large" << endl;
            return;
        }
        else
        {
            newNode->next = walker->next;
            walker->next = newNode;
        }
    }
}

void displayList(node *head)
{
    node* walker = head;

    while (walker != nullptr)
    {
        cout << walker->data << " ";
        walker = walker->next;
    }
    cout << endl;
}