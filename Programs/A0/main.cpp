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
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter index and data to insert: ";
                cin >> index >> data;
                insertNode(head, index, data);
                break;

            case 2:
                cout << "Enter index to delete: ";
                cin >> index;
                deleteNode(head, index);
                break;

            case 3:
                cout << "Enter key to search: ";
                cin >> data;
                searchNode(head, data);
                break;

            case 4:
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