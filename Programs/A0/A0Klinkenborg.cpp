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

node* searchNode(node *head, int key)
{
    node *walker = head;
    int index = 0;

    while (walker != nullptr)
    {
        if (walker->data == key) 
        {
            cout << "Key " << key << " found at index " << index << "." << endl;
            return walker;
        }
        walker = walker->next;
        index++;
    }

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

int getValidNumber() {
    string input;
    bool isNumber;

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