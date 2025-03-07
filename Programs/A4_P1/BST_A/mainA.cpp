#include "bstA.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cerr << "Usage: ./a <filename>" << endl;
        return 1;
    }

    int size = 50;
    string filename = argv[1];

    BST bst(size);

    ifstream infile(filename);

    if (!infile) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        int command, data;
        iss >> command;

        switch (command) {
            case 0:
                //cout << "Exiting...!" << endl;
                //return 0;
                continue;
            case 1:
                iss >> data;
                bst.insertI(data);
                cout << "Insert I: " << data << endl;
                break;
            case 2:
                iss >> data;
                bst.insertR(data);
                cout << "Insert R: " << data << endl;
                break;
            case 3:
                iss >> data;
                if (bst.searchI(data))
                    cout << data << " found I" << endl;
                else
                    cout << data << " not found I" << endl;
                break;
            case 4:
                iss >> data;
                if (bst.searchR(data))
                    cout << data << " found R" << endl;
                else
                    cout << data << " not found R" << endl;
                break;
            case 5:
                cout << "Preorder traversal: ";
                bst.preorder(0); // Start from root index 0
                cout << endl;
                break;
            case 6:
                cout << "Inorder traversal: ";
                bst.inorder(0); // Start from root index 0
                cout << endl;
                break;
            case 7:
                cout << "Postorder traversal: ";
                bst.postorder(0); // Start from root index 0
                cout << endl;
                break;
            case 8:
                cout << "Binary Search Tree" << endl;
                bst.printTree(0, 0); // Start from root index 0
                cout << endl;
                break;
            default:
                cout << "Invalid command" << endl;
        }
    }

    // After processing all commands, will display the task results
    cout << "\nAfter all operations on the BST:" << endl;

    // Task 1: Height of the tree
    cout << "Height of the tree: " << bst.height(0) << endl;

    // Task 2: Count the nodes in the tree
    cout << "Number of nodes: " << bst.countNodes(0) << endl;

    // Task 3: Check if the tree is balanced
    cout << "Is the tree balanced? " << bst.isBalanced() << endl;

    // Task 4: Perform BFS
    cout << "Breadth-First Search (BFS) traversal: ";
    bst.BFS();
    cout << endl;

    cout << "Exiting...!" << endl;

    return 0;
}
