#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <stdio.h>

#include "Graph.h"

using namespace std;
using std::string;

/* default constructor */
Graph::Graph() {
    createGraph();
}

void Graph::addEdge(vector<int> adjList[], int a, int b) {
  adjList[a].push_back(b);
  adjList[b].push_back(a);
}

// helper function for testing correctness of graph
void Graph::printGraph(vector<int> adjList[], int V) {
  for (int d = 0; d < V; ++d) {
    cout << "\n Vertex "
       << d << ": ";
    for (auto x : adjList[d])
      cout << x << ", ";
    cout << "" << endl;
  }
}

void Graph::createGraph() {
    fstream fin;
    fin.open("../dataset/routes.csv", ios::in);

    vector<string> row;

    string word, line;
    while(getline(fin, line, '\n')) {
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')) {
            row.push_back(word);
        }

        // row[3] is source airport ID
        // row[5] is destination airport ID
        // convert string to int
        stringstream sourceStr(row[3]);
        int source = 0;
        sourceStr >> source;
        stringstream destStr(row[5]);
        int dest = 0;
        destStr >> dest;
        addEdge(adjList, source, dest);
    }
    // for testing: 
    printGraph(adjList, 6075);
    fin.close();
}

/*
Take airports.csv and map the airports IATA to its airport ID
*/
void Graph::createAirportMap() {
    fstream fin;
    fin.open("../dataset/airports.csv", ios::in);

    vector<string> row;

    string word, line;
    while(getline(fin, line, '\n')) {
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')) {
            row.push_back(word);
        }

        // row[0] is airport ID
        // row[4] is airport IATA
        stringstream idStr(row[0]);
        int id = 0;
        idStr >> id;

        // // for testing: 
        // std::cout << row[0] + " is the same as " + std::to_string(id) << std::endl;

        airportCode[id] = row[4];
    }
    // // // for testing: 
    // std::cout << airportCode[3316] << std::endl;
    fin.close();
}