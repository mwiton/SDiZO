/* Implementation of min-max heap
*/
#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>

class Node{
public:
    Node(int);
    int key;
};

class HeapMinMax {
public:
    HeapMinMax(): table(nullptr), size(0) {}
    void add(int);
    void addMany(int);
    void removeMin();
    void removeMax();
    void removeAll();
    void printMin();
    void printMax();
    void print4levels();
    void increaseSize();
    void changePositions(int index1, int index2);
    void deleteLast();

private:
    Node **table;
    int size;

};

Node::Node(int keyNode) {
    key = keyNode;
}

void HeapMinMax::add(int key) {
    Node* newNode = new Node(key);
    increaseSize();
    int index = size;
    table[index-1] = newNode;
    int parent = index/2;
    int grandparent = parent/2;
    if (grandparent == 0){
        if(parent != 0){
            if(table[index-1]->key < table[parent - 1]->key)
                changePositions(index-1, parent-1);
        }
        return;
    }
    int minLevel, maxLevel;
    if(table[grandparent-1]->key < table[parent-1]->key){
        minLevel = grandparent;
        maxLevel = parent;
    }
    else{
        maxLevel = grandparent;
        minLevel = parent;
    }
    if(table[index-1]->key < table[minLevel - 1]->key){
        changePositions(index-1, minLevel-1);
        index = minLevel;
        minLevel /= 4;
        while (minLevel != 0){
            if(table[index-1]->key < table[minLevel-1]->key) {
                changePositions(index - 1, minLevel - 1);
                index = minLevel;
                minLevel /= 4;
            }
            else break;
        }
    }
    else if(table[index-1]->key > table[maxLevel - 1]->key){
        changePositions(index-1, maxLevel-1);
        index = maxLevel;
        maxLevel /= 4;
        while (maxLevel != 0){
            if(table[index-1]->key > table[maxLevel-1]->key) {
                changePositions(index - 1, maxLevel - 1);
                index = maxLevel;
                maxLevel /= 4;
            }
            else break;
        }
    }
}


void HeapMinMax::addMany(int X) {
    int key;
    for (int i = 0; i < X; ++i) {
        key = (rand()*rand()%(1000000-10)) + 10;
        add(key);
    }
}

void HeapMinMax::removeMin() {
    changePositions(0, size - 1);
    deleteLast();
    int min, current = 0, nextLevel = 2;
    while(std::pow(2, nextLevel) <= size){
        min = std::pow(2, nextLevel)-1;
        for (int i = std::pow(2, nextLevel) + 1; i <std::pow(2, nextLevel+1); ++i) {
            if(i > size)
                break;
            if(table[i-1]->key < table[min]->key)
                min = i-1;
        }
        if(table[current]->key < table[min]->key)
            return;
        changePositions(current, min);
        current = min;
        nextLevel += 2;
    }
    if(table[current]->key > table[(current+1)/2 - 1]->key)
        changePositions(current, (current+1)/2 - 1);
    else {
        int lower, leftChild = (current + 1) * 2, rightChild = leftChild + 1;
        if (rightChild <= size) {
            if (table[leftChild - 1]->key < table[rightChild -1]->key)
                lower = leftChild-1;
            else
                lower = rightChild-1;
            if(table[current]->key > table[lower]->key)
                changePositions(current, lower);
        }
        else if(leftChild == size){
            if(table[current]->key > table[leftChild-1]->key)
                changePositions(current, leftChild-1);
        }
    }
}

void HeapMinMax::removeMax() {
    int max, current, nextLevel = 3;
    if(size < 3){
        deleteLast();
        return;
    }
    if(table[2]->key > table[1]->key)
        current = 2;
    else
        current = 1;
    changePositions(current, size - 1);
    deleteLast();
    while(std::pow(2, nextLevel) <= size){
        max = std::pow(2, nextLevel)-1;
        for (int i = std::pow(2, nextLevel) + 1; i <std::pow(2, nextLevel+1); ++i) {
            if(i > size)
                break;
            if(table[i-1]->key > table[max]->key)
                max = i-1;
        }
        if(table[current]->key > table[max]->key)
            return;
        changePositions(current, max);
        current = max;
        nextLevel += 2;
    }
    if(table[current]->key < table[(current+1)/2 - 1]->key)
        changePositions(current, (current+1)/2 - 1);
    else {
        int higher, leftChild = (current + 1) * 2, rightChild = leftChild + 1;
        if (rightChild <= size) {
            if (table[leftChild - 1]->key < table[rightChild -1]->key)
                higher = leftChild-1;
            else
                higher = rightChild-1;
            if(table[current]->key < table[higher]->key)
                changePositions(current, higher);
        }
        else if(leftChild == size){
            if(table[current]->key < table[leftChild-1]->key)
                changePositions(current, leftChild-1);
        }
    }
}

void HeapMinMax::removeAll() {
    for (int i = 0; i < size; ++i) {
        delete table[i];
    }
    delete[] table;
    table = nullptr;
    size = 0;
}

void HeapMinMax::printMin() {
    if(size == 0)
        std::cout << "Brak elementow w kopcu";
    else
        std::cout << table[0]->key;
}

void HeapMinMax::printMax() {
    if(size == 0)
        std::cout << "Brak elementow w kopcu";
    else if(size == 1)
        std::cout << table[0]->key;
    else if(size == 2)
        std::cout << table[1]->key;
    else{
        if(table[2]->key > table[1]->key)
            std::cout << table[2]->key;
        else
            std::cout << table[1]->key;
    }
}

void HeapMinMax::print4levels() {
    for (int i = 0; i < 4; ++i) {
        for(int j = std::pow(2, i); j < std::pow(2, i+1); ++j){
            if(j > size)
                return;
            std::cout << table[j-1]->key << " ";
        }
        std::cout << "\n";
    }
}

void HeapMinMax::increaseSize() {
    Node** oldTable = new Node*[size+1];
    for(int i=0; i<size; ++i){
        oldTable[i] = table[i];
    }
    if(table != nullptr)
        delete[] table;
    table = oldTable;
    ++size;
}

void HeapMinMax::changePositions(int index1, int index2) {
    Node* t = table[index1];
    table[index1] = table[index2];
    table[index2] = t;
}

void HeapMinMax::deleteLast() {
    delete table[size-1];
    --size;
    if(size==0){
        table = nullptr;
        return;
    }
    Node** newTab = new Node*[size];
    for (int i = 0; i < size; ++i) {
        newTab[i] = table[i];
    }
    delete[] table;
    table = newTab;
}

/*void test() {
    HeapMinMax tree;
    tree.add(8);
    tree.add(10);
    tree.add(14);
    tree.add(13);
    tree.add(3);
    tree.add(6);
    tree.add(4);
    tree.add(7);
    tree.add(1);
    tree.add(2);
    tree.add(20);
    tree.removeMin();
    tree.print4levels();
    std::cout << "\n";
    tree.printMin();
    std::cout << "\n";
    tree.printMax();
    std::cout << "\n";
}*/

int main(){
    clock_t begin, end;
    double time_spent;
    begin = clock();
    int x1, x2, k1, k2;
    std::ifstream file("inlab06.txt");
    if(!file)return 1;
    file >> x1 >> x2 >> k1 >> k2;
    HeapMinMax heap;
    heap.addMany(x1);
    heap.add(k1);
    heap.add(k2);
    heap.removeMin();
    heap.removeMax();
    heap.print4levels();
    std::cout << "\n";
    heap.removeAll();
    heap.addMany(x2);
    heap.removeMin();
    heap.removeMax();
    heap.add(k1);
    heap.add(k2);
    heap.printMax();
    std::cout << "\n";
    heap.printMin();
    std::cout << "\n";
    heap.removeAll();
    heap.printMax();
    std::cout << "\n";
    heap.printMin();
    std::cout << "\n";
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Czas wykonania: " << time_spent;
    return 0;
}


