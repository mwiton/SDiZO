/* SDIZO IS1 210b LAB05
   Mateusz Witon
   mwiton@wi.zut.edu.pl
*/
#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

class Node{
public:
    Node(int);
    int key;
    Node *left;
    Node *right;
    int balanceFactor;
    char *tab;
};

class AVL {
public:
    AVL(): root(nullptr) {}
    void add(int);
    void addMany(int);
    Node** find(int);
    void remove(int);
    void replace(Node*, Node*);
    void makeNull(Node*, Node*);
    void printPreOrder();
    void printInOrder();
    void printPostOrder();
    void printPreOrder(Node*);
    void printInOrder(Node*);
    void printPostOrder(Node*);
    void print(Node*);
    void leftRotation(Node*, Node*, Node*);
    void rightRotation(Node*, Node*, Node*);
    int height();
    void balance(Node* child, Node* parent);

private:
    Node *root;

};

int heightSubTree(Node* node);

Node::Node(int keyNode) {
    key = keyNode;
    left = NULL;
    right = NULL;
    balanceFactor = 0;
    tab = new char[16];
    for(int i=0; i<16; ++i){
        tab[i] = (char)(rand()%(127 - 32)) + 32;
    }
}

void AVL::add(int key) {
    Node *newNode = new Node(key);
    Node *previous = NULL;
    std::vector<Node*> previousNodes;
    if(root == NULL){
        root = newNode;
        return;
    }
    //Adding to tree
    Node *pointer = root;
    while(pointer != NULL){
        previous = pointer;
        previousNodes.push_back(previous);
        if(newNode->key < pointer->key) pointer = pointer->left;
        else if(newNode->key > pointer->key) pointer = pointer->right;
        else{
            std::cout << "Juz znajduje sie lisc z kluczem " << key <<"\n";
            return;
        }
    }
    if(newNode->key < previous->key) previous->left = newNode;
    else if(newNode->key > previous->key) previous->right = newNode;
    //Calculating balanceFactor and balancing tree
    for (int i = previousNodes.size()-1; i >= 0; --i) {
        if(i != 0)
            balance(previousNodes[i], previousNodes[i-1]);
        else
            balance(previousNodes[i], NULL);
    }
}


void AVL::addMany(int X) {
    int key;
    for (int i = 0; i < X; ++i) {
        key = (rand()*rand()%1000003) + 10;
        add(key);
    }
}

Node **AVL::find(int key) {
    //stack[0] - child, stack[1] - parent, stack[2] - grandparent
    Node** stack =  new Node*[3];
    stack[0] = root;
    stack[1] = NULL;
    stack[2] = NULL;
    while(stack[0] != NULL){
        if(stack[0]->key == key) return stack;
        stack[2] = stack[1];
        stack[1] = stack[0];
        if(key < stack[0]->key) stack[0] = stack[0]->left;
        else stack[0] = stack[0]->right;
    }
    std::cout << "W drzewie nie ma liscia o kluczu " << key << "\n";
    return NULL;
}

void AVL::remove(int i) {
    Node** removeNode = find(i);
    if(removeNode == NULL){
        return;
    }
    if(removeNode[0]->left == NULL && removeNode[0]->right == NULL){
        if(removeNode[1]) makeNull(removeNode[1], removeNode[0]);
        else root = NULL;
        delete[] removeNode;
        return;
    }
    //Removing a node
    Node *pointer = removeNode[0];
    Node *parent = pointer;
    if(removeNode[0]->left==NULL){
        pointer = removeNode[0]->right;
        if (pointer->left != NULL) {
            while (pointer->left != NULL) {
                parent = pointer;
                pointer = pointer->left;
            }
            replace(removeNode[0], pointer);
            if (pointer->right) {
                parent->left = pointer->right;
            }
            else parent->left = NULL;
        }
        else {
            replace(removeNode[0], pointer);
            if (pointer->right) {
                removeNode[0]->right = pointer->right;
            }
            else parent->right = NULL;
        }
        return;
    }
    pointer = removeNode[0]->left;
    if (pointer->right != NULL) {
        while (pointer->right != NULL) {
            parent = pointer;
            pointer = pointer->right;
        }
        replace(removeNode[0], pointer);
        if (pointer->left) {
            parent->right = pointer->left;
        }
        else parent->right = NULL;
    }
    else{
        replace(removeNode[0], pointer);
        if (pointer->left) {
            removeNode[0]->left = pointer->left;
        }
        else parent->left = NULL;
    }
    //Calculating balanceFactor and balancing
    Node** currentNodes = find(parent->key);
    while(true){
        balance(currentNodes[0], currentNodes[1]);
        if(currentNodes[1] == NULL)
            break;
        currentNodes = find(currentNodes[1]->key);
    }
}



void AVL::replace(Node *node1, Node *node2) {
    node1->key = node2->key;
    node1->tab = node2->tab;
}

void AVL::makeNull(Node *node, Node *node1) {
    if(node->left) {
        if (node->left->key == node1->key) node->left = NULL;
    }
    else node->right = NULL;
}

void AVL::printPreOrder(Node *node) {
    if(node == NULL) return;
    print(node);
    printPreOrder(node->left);
    printPreOrder(node->right);
}

void AVL::printInOrder(Node *node) {
    if(node == NULL) return;
    printInOrder(node->left);
    print(node);
    printInOrder(node->right);
}


void AVL::printPostOrder(Node *node) {
    if(node == NULL) return;
    printPostOrder(node->left);
    printPostOrder(node->right);
    print(node);
}

void AVL::print(Node *node) {
    std::cout << node->key << " ";
}

void AVL::printPreOrder() {
    printPreOrder(root);
}

void AVL::printInOrder() {
    printInOrder(root);
}

void AVL::printPostOrder() {
    printPostOrder(root);
}

void AVL::leftRotation(Node* child, Node* parent, Node* grandparent) {
    if(grandparent != NULL) {
        if (grandparent->left == parent)
            grandparent->left = child;
        else
            grandparent->right = child;
    }
    else
        root = child;
    parent->right = child->left;
    child->left = parent;
}

void AVL::rightRotation(Node* child, Node* parent, Node* grandparent) {
    if(grandparent != NULL) {
        if (grandparent->left == parent)
            grandparent->left = child;
        else
            grandparent->right = child;
    }
    else
        root = child;
    parent->left = child->right;
    child->right = parent;
}

int heightSubTree(Node* node){
    if(node == NULL)
        return 0;
    int leftHeight = heightSubTree(node->left);
    int rightHeight = heightSubTree(node->right);
    if(leftHeight >= rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

int AVL::height() {
    if (root == NULL)
        return 0;
    int leftHeight = heightSubTree(root->left);
    int rightHeight = heightSubTree(root->right);
    if (leftHeight >= rightHeight)
        return leftHeight;
    else
        return rightHeight;
}

void AVL::balance(Node *child, Node *parent) {
    child->balanceFactor =
            heightSubTree(child->left) - heightSubTree(child->right);
    if(child->balanceFactor == 2){
        if(child->left->balanceFactor == -1) {
            leftRotation(child->left->right, child->left, child);
        }
        rightRotation(child->left, child, parent);
    }
    else if(child->balanceFactor == -2){
        if(child->right->balanceFactor == 1) {
            rightRotation(child->right->left, child->right, child);
        }
        leftRotation(child->right, child, parent);
    }
}

void test() {
    AVL tree;
    tree.add(8);
    tree.add(10);
    tree.add(14);
    tree.add(13);
    tree.add(3);
    tree.add(6);
    tree.add(4);
    tree.add(7);
    tree.add(1);
    tree.remove(7);
    tree.printPreOrder();
    std::cout << "\n";
    tree.printInOrder();
    std::cout << "\n";
    tree.printPostOrder();
}

int main(){
    clock_t begin, end;
    double time_spent;
    begin = clock();
    int X, k1, k2, k3, k4;
    std::ifstream file("inlab05.txt");
    if(!file)return 1;
    file >> X >> k1 >> k2 >> k3 >> k4;
    AVL tree;
    tree.addMany(X);
    std::cout << tree.height() << "\n";
    tree.add(k1);
    tree.add(k2);
    tree.add(k3);
    tree.add(k4);
    std::cout << tree.height() << "\n";
    tree.find(k2);
    tree.remove(k1);
    std::cout << tree.height() << "\n";
    tree.printInOrder();
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Czas wykonania: " << time_spent;
    return 0;
}



