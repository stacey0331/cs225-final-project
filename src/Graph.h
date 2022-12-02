#include <list>
#include <vector>
#include <map>

using namespace std;
using std::string;

/*
- Create map to map airport IATA code to airport ID
- Create graph using the aiport map above
- Considering only using part of data as the datafile is huge

*/
class Graph {
    public: 
        // node and edge info both in routes.csv
        Graph();
        void addEdge(vector<int> adjList[], int a, int b);
        void createGraph();
        void createAirportMap();
        void printGraph(vector<int> adjList[], int V);

    private: 
        // adjacency list with weights. each node is an airport, each edge is a route
        vector<int> adjList[6075];
        map<int, string> airportCode; // map airport ID to its IATA code


};

// vector<pair(int vertex, vector<pair(int vertext, int weight)>)> adjList;