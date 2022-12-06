#pragma once

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
        void addEdge(vector<pair<int, double>> adjList[], int a, int b, double weight);
        void createGraph();
        void mapAirportName();
        void mapLatLong();
        void printGraph(vector<pair<int, double>> adjList[]);
        double getWeight(int sourceAirportId, int destAirportId);
        double toRadians(double num);

        vector<pair<int, double>> getAdjList();


    private: 
        int numAirport;
/*
each element in adjList is a vertex(airport)
each vertex has an vector/list of its adjacent nodes/airport that it has a flight to
each adjacent nodes are expressed as a pair, with first being airport ID and second being weight
*/
        vector<pair<int, double>> adjList[4391];
        map<int, string> airportCode; // map airport ID to its IATA code
        
        // map airport id to its latitude/longitude
        map<int, double> latMap;
        map<int, double> longMap;


};

