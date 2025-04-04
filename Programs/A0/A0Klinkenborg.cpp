// Name: Keenan Klinkenborg
// Program: Assignment 0 | Linker Loader
// Date: 1/26/25

#include "A0Klinkenborg.h"

// Task 1: Insert a node to a specific index
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

// Delete a node at a specific index
void deleteNode(node *&head, int index)
{
    if (head == nullptr)
    {
        cout << "List is empty, nothing to delete." << endl;
        return;
    }

    if (index == 0)
    {
        node *temp = head;
        head = head->next; 
        delete temp; 
        cout << "Node at index 0 deleted." << endl;
        return;
    }

    node *walker = head;
    int wIndex = 0;

    // walk to node just before index
    while (walker != nullptr && wIndex < index - 1)
    {
        walker = walker->next;
        wIndex++;
    }

    if (walker == nullptr || walker->next == nullptr)
    {
        cout << "Index out of range. Deletion failed." << endl;
        return;
    }

    node *temp = walker->next;
    walker->next = temp->next; 
    delete temp; 
    cout << "Node at index " << index << " deleted." << endl;
}

// Search for a node with a specific key
node* searchNode(node *head, int key)
{
    node *walker = head;
    int index = 0;

    while (walker != nullptr)
    {
        if (walker->data == key) 
        {
            cout << "Key " << key << " found at index " << index << "." << endl;
            return walker; // Return if the node is found
        }
        walker = walker->next;
        index++;
    }

    cout << "Key " << key << " not found in the list." << endl;
    return nullptr; // return null if not found
}

// Display all nodes in the list
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

// Task 2: Reverses the current list
void reverseList(node *&head)
{
    node *prev = nullptr;
    node *current = head;
    node *next = nullptr;

    // Traverse list and reverse direction of pointers
    while (current != nullptr)
    {
        next = current -> next;
        current -> next = prev;

        prev = current;
        current = next;
    }

    head = prev;

    cout << "List reversed." << endl;
}


// error checking: Get a valid number from user input
int getValidNumber() {
    string input;
    bool isNumber;

    // makes sure the input is only a digit to prevent code spaz
    do {
        isNumber = true; 
        cin >> input;

        for (char c : input) {
            if (!isdigit(c)) {
                isNumber = false; 
                cout << "Invalid input. Please enter a valid number." << endl;
                break;
            }
        }
    } while (!isNumber); 

    return stoi(input); 
}