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

void deleteNode(node *&head, int index)
{
    // If the list is empty
    if (head == nullptr)
    {
        cout << "List is empty, nothing to delete." << endl;
        return;
    }

    // Deleting the first node (index 0)
    if (index == 0)
    {
        node *temp = head;
        head = head->next; // Move the head to the next node
        delete temp; // Free the memory of the deleted node
        cout << "Node at index 0 deleted." << endl;
        return;
    }

    // Traverse to the node before the one to delete
    node *walker = head;
    int wIndex = 0;

    while (walker != nullptr && wIndex < index - 1)
    {
        walker = walker->next;
        wIndex++;
    }

    // If the index is out of range
    if (walker == nullptr || walker->next == nullptr)
    {
        cout << "Index out of range. Deletion failed." << endl;
        return;
    }

    // Delete the node at the specified index
    node *temp = walker->next;
    walker->next = temp->next; // Link the previous node to the next node
    delete temp; // Free the memory of the deleted node
    cout << "Node at index " << index << " deleted." << endl;
}

node* searchNode(node *head, int key)
{
    node *walker = head;
    int index = 0;

    // Traverse the list to find the key
    while (walker != nullptr)
    {
        if (walker->data == key) // Key found
        {
            cout << "Key " << key << " found at index " << index << "." << endl;
            return walker;
        }
        walker = walker->next;
        index++;
    }

    // Key not found
    cout << "Key " << key << " not found in the list." << endl;
    return nullptr;
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