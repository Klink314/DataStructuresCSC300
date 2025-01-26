// Name: Keenan Klinkenborg
// Program: Assignment 0 | Linker Loader
// Date: 1/26/25

#include "A0Klinkenborg.h"

int main()
{
    node *head = nullptr;
    node *myNode = nullptr;

    int choice, data, index;

    // Main loop to display the menu and execute corresponding actions
    do
    {
        //displays menu
        cout << "Menu:\n";
        cout << "1. Insert Node\n";
        cout << "2. Delete Node\n";
        cout << "3. Search Node\n";
        cout << "4. Display List\n";
        cout << "5. Reverse List\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidNumber();

        //switch statement to handle the menu options
        switch (choice)
        {
            //insert node
            case 1:
                cout << "Enter the index: ";
                index = getValidNumber();
                cout << "Enter the data: ";
                data = getValidNumber();
                insertNode(head, index, data);
                break;

            //delete node
            case 2:
                cout << "Enter the index to delete: ";
                index = getValidNumber();
                deleteNode(head, index);
                break;

            //search node
            case 3:
                cout << "Enter the data to search: ";
                data = getValidNumber();
                searchNode(head, data);
                break;
            
            //display list
            case 4:
                cout << "Displaying linked list: ";
                displayList(head);
                break;

            //reverse list
            case 5:
                cout << "Reversing list";
                reverseList(head);
                break;

            //Exit program
            case 6: 
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 6);
    
    return 0;
}
