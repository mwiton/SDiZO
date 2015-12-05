/* SDIZO IS1 210b LAB02
* Mateusz Witon
* mwiton@wi.zut.edu.pl
*/

#include <iostream>
#include <cstdlib>
#include <fstream>

struct Node {
	int key;
	double one;
	double two;
	double three;
	Node *next;
	Node *previous;
};

void randomValues(Node *node) {
	node->one = (double)rand() / RAND_MAX;
	node->two = (double)rand() / RAND_MAX;
	node->three = (double)rand() / RAND_MAX;
}

class List {
private:
	
	Node* head;
public:
	List() { head = NULL; };
	void insert(int newKey);
	Node* find(int key);
	void printFromStart();
	void printFromEnd();
	void removeAll();
    void insertRandomKeys(int amount);

    void remove(int key);
};

void List::insert(int newKey) {
	if (head == NULL) {
		head = new Node();
		head->key = newKey;
		head->previous = head;
		head->next = head;
		randomValues(head);
        return;
    }
    Node* currentNode = head;
    do{
        if( currentNode->key >= newKey ) break;
        currentNode = currentNode->next;
    } while (currentNode != head);
    if (currentNode->key == newKey) {
        return;
    }
    Node* newNode = new Node();
    newNode->key = newKey;
    randomValues(newNode);
    newNode->next = currentNode;
    newNode->previous = currentNode->previous;
    currentNode->previous->next = newNode;
    currentNode->previous = newNode;
	if(head->previous->key < head->key) head = head->previous;
}

void List::insertRandomKeys(int amount) {
	int newKey;
	for (int i = 0; i < amount; ++i) {
		newKey = (rand() * rand()) % (100001 - 10) + 10;
        insert(newKey);
	}
}

Node* List::find(int key) {
	Node* currentNode = head;
	if (currentNode == NULL) {
		std::cout << "Lista jest bez elementow\n";
		return NULL;
	}
	do{
        if (currentNode->key == key) return currentNode;
        else if( key < currentNode->key ) {
            std::cout << "Brak elementu z kluczem " << key << std::endl;
            return NULL;
        }
        currentNode = currentNode->next;
	} while (currentNode != head);
    std::cout << "Brak elementu z kluczem " << key << std::endl;
    return NULL;
}

void List::remove(int key) {
	Node* currentNode = head;
	if (currentNode == NULL) {
		std::cout << "Lista jest bez elementow\n";
		return;
	}
	do {
		currentNode = currentNode->next;
	}while (currentNode != head && key > currentNode->key);
	if (currentNode->key == key) {
		if (head->key == currentNode->key) head = currentNode->next;
		currentNode->previous->next = currentNode->next;
		currentNode->next->previous = currentNode->previous;
		delete currentNode;
	}
	else {
		std::cout << "Brak elementu z kluczem " << key << std::endl;
	}
}

void List::printFromStart() {
	if (head == NULL) {
		std::cout << "Lista jest bez elementow\n";
		return;
	}
	Node* currentNode = head;
	do{
		std::cout << currentNode->key << " " << currentNode->one << " "
			<< currentNode->two << " " << currentNode->three << std::endl;
		currentNode = currentNode->next;
	} while (currentNode->key != head->key);
}

void List::printFromEnd() {
	if (head == NULL) {
		std::cout << "Lista jest bez elementow\n";
		return;
	}
	Node* currentNode = head->previous;
	do{
		std::cout << currentNode->key << " " << currentNode->one << " "
			<< currentNode->two << " " << currentNode->three << std::endl;
		currentNode = currentNode->previous;
	} while (currentNode != head->previous);
}

void List::removeAll() {
	if (head == NULL) {
		return;
	}
	Node* currentNode = head->next;
    Node* nextNode;
	while (currentNode != head){
		nextNode = currentNode->next;
		delete currentNode;
        currentNode = nextNode;
	}
	delete head;
	head = NULL;
}

void test(){
    List testList = List();
    testList.insert(1);
    testList.insert(2);
    testList.insert(4);
    testList.insert(3);
    Node *find = testList.find(5);
    if(find != NULL) std::cout<<find->one<<std::endl;
    testList.insertRandomKeys(5);
    testList.printFromStart();
    testList.remove(4);
    testList.printFromStart();
    testList.printFromEnd();
    testList.removeAll();
}

int main() {
    clock_t begin, end;
    double time_spent;
    begin = clock();
    int X, k1, k2, k3, k4;
    std::ifstream file("inlab02.txt");
    file >> X >> k1 >> k2 >> k3 >> k4;
    List list;
	list.remove(k1);
    list.insertRandomKeys(X);
    list.insert(k2);
    list.remove(k2);
    list.find(k3);
    list.insert(k4);
    list.remove(k4);
    list.printFromStart();
    list.printFromEnd();
    list.removeAll();
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Czas wykonania: " << time_spent;
	return 0;
}
