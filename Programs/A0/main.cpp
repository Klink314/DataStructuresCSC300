#include "A0Klinkenborg.h"

int main()
{
    node *head = nullptr;
    node *myNode = nullptr;

    int choice, data, index;

    do
    {
        cout << "Menu:\n";
        cout << "1. Insert Node\n";
        cout << "2. Delete Node\n";
        cout << "3. Search Node\n";
        cout << "4. Display List\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidNumber();

        switch (choice)
        {
            case 1:
                cout << "Enter the index: ";
                index = getValidNumber();
                cout << "Enter the data: ";
                data = getValidNumber();
                insertNode(head, index, data);
                break;

            case 2:
                cout << "Enter the index to delete: ";
                index = getValidNumber();
                deleteNode(head, index);
                break;

            case 3:
                cout << "Enter the data to search: ";
                data = getValidNumber();
                searchNode(head, data);
                break;

            case 4:
                cout << "Displaying linked list: ";
                displayList(head);
                break;

            case 5:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);
    
    return 0;
}
