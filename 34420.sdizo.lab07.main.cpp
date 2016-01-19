//
// Created by mwiton on 19.01.16.
//
#include <iostream>
#include <vector>
#include "inlab07.h"

const int TOWNS = 39;

struct Node{
    int key;
    std::string name;
    std::vector<std::pair<int, int>> neighbours;

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

int* distancesDijkstraAlgorithm(int start){
    //std::vector<Node*> Q, S;
    bool Q[TOWNS];
    int d[TOWNS], p[TOWNS];
    Node* u;
    for(int i=0; i<TOWNS; ++i) {
        Q[i] = true;
        d[i] = 100000;
        //p[i]=-1;
    }
    d[start]=0;
    while(Q.size() > 0){
        int min = 0;
        for(int i=1; i<Q.size(); ++i){
            if(d[Q[i]->key] < d[Q[min]->key])
                min = i;
        }
        u = Q[min];
        Q.erase(Q.begin()+min);
        S.push_back(u);

    }
}

int dijkstraAlgorithm(std::string townA, std::string townB){

}

int main(){
    std::cout<<dijkstraAlgorithm("Szczecin", "Krakow");
}