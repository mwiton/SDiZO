/* Implementation of binary search tree
*/

#include <iostream>
#include <ctime>
#include <fstream>

class Node{
public:
    Node(int);
    int key;
    Node *left;
    Node *right ;
    char *tab;
};

class BST{
public:
    BST(): root(nullptr) {}
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

private:
    Node *root;

};

Node::Node(int keyNode) {
    key = keyNode;
    left = NULL;
    right = NULL;
    tab = new char[256];
    for(int i=0; i<256; ++i){
        tab[i] = (char)(rand()%(127 - 32)) + 32;
    }
}

void BST::add(int key) {
    Node *newNode = new Node(key);
    Node *previous = NULL;
    if(root == NULL){
        root = newNode;
        return;
    }
    Node *pointer = root;
    while(pointer != NULL){
        previous = pointer;
        if(newNode->key < pointer->key) pointer = pointer->left;
        else if(newNode->key > pointer->key) pointer = pointer->right;
        else{
            std::cout << "Juz znajduje sie lisc z kluczem " << key <<"\n";
            return;
        }
    }
    if(newNode->key < previous->key) previous->left = newNode;
    else if(newNode->key > previous->key) previous->right = newNode;
}


void BST::addMany(int X) {
    int key;
    for (int i = 0; i < X; ++i) {
        key = (rand()*rand()%1000003) + 10;
        add(key);
    }
}

Node **BST::find(int key) {
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

void BST::remove(int i) {
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
}



void BST::replace(Node *node1, Node *node2) {
    node1->key = node2->key;
    node1->tab = node2->tab;
}

void BST::makeNull(Node *node, Node *node1) {
    if(node->left) {
        if (node->left->key == node1->key) node->left = NULL;
    }
    else node->right = NULL;
}

void BST::printPreOrder(Node *node) {
    if(node == NULL) return;
    print(node);
    printPreOrder(node->left);
    printPreOrder(node->right);
}

void BST::printInOrder(Node *node) {
    if(node == NULL) return;
    printInOrder(node->left);
    print(node);
    printInOrder(node->right);
}


void BST::printPostOrder(Node *node) {
    if(node == NULL) return;
    printPostOrder(node->left);
    printPostOrder(node->right);
    print(node);
}

void BST::print(Node *node) {
    std::cout << node->key << " ";
}

void BST::printPreOrder() {
    printPreOrder(root);
}

void BST::printInOrder() {
    printInOrder(root);
}

void BST::printPostOrder() {
    printPostOrder(root);
}

/*void test() {
    BST tree;
    tree.add(8);
    tree.add(10);
    tree.add(14);
    tree.add(13);
    tree.add(3);
    tree.add(6);
    tree.add(4);
    tree.add(7);
    tree.add(1);
    tree.remove(13);
    Node** stack = tree.find(6);
    std::cout << stack[0]->key  << " " << stack[1]->key << " " << stack[2]->key << "\n";
    for(int i=0; i<50; ++i){
        std::cout << stack[0]->tab[i] << " ";
    }
    tree.printPreOrder();
    std::cout << "\n\n";
    tree.printInOrder();
    std::cout << "\n\n";
    tree.printPostOrder();
    std::cout << "\n\n";
}*/

int main(){
    clock_t begin, end;
    double time_spent;
    begin = clock();
    int X, k1, k2, k3, k4;
    std::ifstream file("inlab03.txt");
    if(!file)return 1;
    file >> X >> k1 >> k2 >> k3 >> k4;
    BST tree;
    tree.remove(k1);
    tree.addMany(X);
    tree.add(k1);
    tree.add(k2);
    tree.add(k3);
    tree.add(k4);
    tree.remove(k1);
    tree.find(k1);
    tree.remove(k2);
    tree.remove(k3);
    tree.remove(k4);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Czas wykonania: " << time_spent;
    return 0;
}
