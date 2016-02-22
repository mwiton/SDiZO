// Implementation of Dijkstra algorithm and A* algorithm

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include "inlab07.h"

const int TOWNS = 39;

struct Node{
    int key;
    std::string name;
    std::vector<std::pair<int, int>> neighbours; //first - id of town, second - distance to town

};

Node** towns;

void createTableTowns(){
    towns = new Node*[TOWNS];
    for(int i=0; i<TOWNS; i++){
        towns[i] = new Node;
        towns[i]->key = i;
        towns[i]->name = miastoLabel[i];
        for(int j=0; j<TOWNS; j++){
            if(distances[i][j]>0)
                towns[i]->neighbours.push_back({j, distances[i][j]});
        }
    }
}

bool findNodeInVector(std::vector<Node*> vector, Node* node){
    for (int i = 0; i < vector.size(); ++i) {
        if(vector[i] == node)
            return true;
    }
    return false;
}

int findTown(std::string town){
    for (int i = 0; i < TOWNS; ++i) {
        if(towns[i]->name == town)
            return i;
    }
    return -1;
}

int* distancesDijkstraAlgorithm(int start, int end){
    std::vector<Node*> Q, S;
    std::pair<int, int> nodeW;
    //int p[TOWNS];
    int* d = new int[TOWNS];
    Node* u;
    for(int i=0; i<TOWNS; ++i) {
        Q.push_back(towns[i]);
        d[i] = INT32_MAX;
        //p[i]=-1;
    }
    d[start]=0;
    while(Q.size() > 0){
        int minIndex = 0;
        for(int i=1; i<Q.size(); ++i){
            if(d[Q[i]->key] < d[Q[minIndex]->key])
                minIndex = i;
        }
        u = Q[minIndex];
        if(u->key == end) return d;
        Q.erase(Q.begin()+minIndex);
        S.push_back(u);
        for(int i=0; i<u->neighbours.size(); ++i){
            nodeW = u->neighbours[i];
            if(findNodeInVector(Q, towns[nodeW.first])){
                if(d[nodeW.first] > d[u->key] + nodeW.second){
                    d[nodeW.first] = d[u->key] + nodeW.second;
                    //p[nodeW.first] = u->key;
                }
            }
        }
    }
    return d;
}

int dijkstraAlgorithm(std::string townA, std::string townB){
    int idTownA = findTown(townA);
    int idTownB = findTown(townB);
    int *distances = distancesDijkstraAlgorithm(idTownA, idTownB);
    return distances[idTownB];
}

double getRealDistance(int idA, int idB){
    return std::sqrt(std::pow(miasta[idB][0]-miasta[idA][0],2)+std::pow(miasta[idB][1]-miasta[idA][1],2));
}

int AAlgorithm(std::string townA, std::string townB){
    int idTownA = findTown(townA);
    int idTownB = findTown(townB);
    int minIndex, G[TOWNS];
    double F[TOWNS];
    std::pair<int, int> neighbour;
    std::vector<Node*> openNodes, closedNodes;
    Node* current;
    for (int k = 0; k < TOWNS; ++k) {
        F[k] = INT32_MAX;
        G[k] = INT32_MAX;
    }
    G[idTownA] = 0;
    F[idTownA] = getRealDistance(idTownA, idTownB);
    openNodes.push_back(towns[idTownA]);
    while (openNodes.size() > 0){
        minIndex = 0;
        for (int i = 1; i < openNodes.size(); ++i) {
            if(F[openNodes[i]->key] < F[minIndex])
                minIndex = i;
        }
        current = openNodes[minIndex];
        if(current->key == idTownB)
            return G[current->key];
        openNodes.erase(openNodes.begin()+minIndex);
        closedNodes.push_back(current);
        for (int j = 0; j < current->neighbours.size(); ++j) {
            neighbour = current->neighbours[j];
            Node* neighbourNode = towns[neighbour.first];
            if(findNodeInVector(closedNodes, neighbourNode))
                continue;
            int newG = G[current->key] + neighbour.second;
            if(!(findNodeInVector(openNodes, neighbourNode))){
                openNodes.push_back(neighbourNode);
            }
            else if(newG >= G[neighbourNode->key]){
                continue;
            }
            G[neighbourNode->key] = newG;
            F[neighbourNode->key] = G[neighbourNode->key] + getRealDistance(neighbourNode->key, idTownB);
        }
    }
    return -1;
}

int main(){
    clock_t begin, end;
    double time_spent;
    createTableTowns();
    begin = clock();
    std::cout<<dijkstraAlgorithm("Szczecin", "Krakow")<<std::endl;
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Czas wykonania: " << time_spent << std::endl;
    begin = clock();
    for(int i=0; i<1000; i++){
        dijkstraAlgorithm("Szczecin", "Przemysl");
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Czas wykonania: " << time_spent<< std::endl;;
    begin = clock();
    std::cout<<AAlgorithm("Szczecin", "Krakow")<<std::endl;
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Czas wykonania: " << time_spent<< std::endl;;
    begin = clock();
    for(int i=0; i<1000; i++){
        AAlgorithm("Szczecin", "Przemysl");
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Czas wykonania: " << time_spent<< std::endl;;
    return 0;
}
