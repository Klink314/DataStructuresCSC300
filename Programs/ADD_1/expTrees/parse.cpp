#include "parse.h"

// ======================= PUBLIC FUNCTIONS ================================================

// Node constructor
Node::Node(string val)
{
    value = val;
    left = nullptr;
    right = nullptr; 
}

// Constructor - initializing root
Parser::Parser()
{
    root = nullptr; 
}

// Destructor - free tree memory
Parser::~Parser() 
{
    if (root) {
        if (root->left) {
            delete root->left;
        }
        if (root->right) {
            delete root->right;
        }
        delete root;
        root = nullptr; // avoids dangling pointer
    }
}

void Parser::preOrder() 
{
    preOrderTraversal(root);
    cout << endl;
}

void Parser::inOrder() 
{
    inOrderTraversal(root);
    cout << endl;
}

void Parser::postOrder() 
{
    postOrderTraversal(root);
    cout << endl;
}


double Parser::evaluate() 
{
    return evaluateTree(root);
}

Node* Parser::simplify() 
{
    root = simplifyTree(root);
    return root;
}

// ================== Task 1 Start ====================

// Build the expression tree from a postfix expression
Node* Parser::buildExpressionTree(const string& postfix) 
{
    struct StackNode {
        Node* treeNode;
        StackNode* next;
    };

    StackNode* top = nullptr;

    auto push = [&](Node* node) {
        StackNode* newNode = new StackNode{ node, top };
        top = newNode;
    };

    auto pop = [&]() -> Node* {
        if (!top) return nullptr;
        Node* node = top->treeNode;
        StackNode* temp = top;
        top = top->next;
        delete temp;
        return node;
    };

    istringstream ss(postfix);
    string token;

    while (ss >> token) {
        Node* newNode = new Node(token);

        if (isNumber(token) || isalpha(token[0])) { // If it's a number or a variable, push it
            push(newNode);
        } else { // Otherwise, it's an operator
            newNode->right = pop(); // Right child first (LIFO)
            newNode->left = pop();  // Left child second (LIFO)
            push(newNode);
        }
    }

    root = pop();
    return root;
}

// ================== Task 1 End ====================



// ======================= PRIVATE FUNCTIONS ================================================


// Check if the string is a number
bool Parser::isNumber(const string& s) {
    for (char c : s) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }
    return true;
}


// Recursive Pre-order traversal (C-L-R)
void Parser::preOrderTraversal(Node* node) {
    if (!node) return;
    cout << node->value << " ";
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
}


// Recursive In-order traversal (L-C-R)
void Parser::inOrderTraversal(Node* node) {
    if (!node) return;
    if (node->left) cout << "( ";
    inOrderTraversal(node->left);
    cout << node->value << " ";
    inOrderTraversal(node->right);
    if (node->right) cout << ") ";
}


// Recursive Post-order traversal (L-R-C)
void Parser::postOrderTraversal(Node* node) {
    if (!node) return;
    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    cout << node->value << " ";
}


// ================== Task 2 Start ====================

double Parser::evaluateTree(Node* node) {
    if (!node) return 0;
    if (isNumber(node->value)) {
        return stod(node->value);
    }

    double leftVal = evaluateTree(node->left);
    double rightVal = evaluateTree(node->right);

    if (node->value == "+") return leftVal + rightVal;
    if (node->value == "-") return leftVal - rightVal;
    if (node->value == "*") return leftVal * rightVal;
    if (node->value == "/") return leftVal / rightVal;

    return 0; // Should never reach here
}

// ================== Task 2 End ====================


// ================== Task 3 Start ====================

Node* Parser::simplifyTree(Node* node) {
    if (!node || isNumber(node->value)) return node;

    // Recursively simplify left and right subtrees
    node->left = simplifyTree(node->left);
    node->right = simplifyTree(node->right);

    // Constant Folding: If both children are numbers, evaluate immediately
    if (node->left && node->right && isNumber(node->left->value) && isNumber(node->right->value)) {
        double leftVal = stod(node->left->value);
        double rightVal = stod(node->right->value);
        double result;

        if (node->value == "+") result = leftVal + rightVal;
        else if (node->value == "-") result = leftVal - rightVal;
        else if (node->value == "*") result = leftVal * rightVal;
        else if (node->value == "/") result = leftVal / rightVal;

        return new Node(to_string(result));
    }

    // Algebraic Simplification
    if (node->value == "*") {
        if (node->left->value == "1") return simplifyTree(node->right); // x * 1 = x
        if (node->right->value == "1") return simplifyTree(node->left); // 1 * x = x
        if (node->left->value == "0" || node->right->value == "0") return new Node("0"); // x * 0 = 0, 0 * x = 0
    }

    if (node->value == "/") {
        if (node->right->value == "1") return simplifyTree(node->left); // x / 1 = x
    }

    if (node->value == "+") {
        if (node->left->value == "0") return simplifyTree(node->right); // 0 + x = x
        if (node->right->value == "0") return simplifyTree(node->left); // x + 0 = x
    }

    if (node->value == "-") {
        if (node->right->value == "0") return simplifyTree(node->left); // x - 0 = x
    }

    return node;
}

// ================== Task 3 End ====================
