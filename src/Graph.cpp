#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <stdio.h>
#include <cmath>

#include "Graph.h"

using namespace std;
using std::string;

/* default constructor */
Graph::Graph() {
    numAirport = 4390;
    createGraph();
}

void Graph::addEdge(vector<pair<int, double>> adjList[], int a, int b, double weight) {
  adjList[a].push_back(make_pair(b, weight));
  adjList[b].push_back(make_pair(a, weight));
}

// helper function for testing correctness of graph
void Graph::printGraph(vector<pair<int, double>> adjList[]) {
  for (int d = 0; d <= numAirport; d++) {
    cout << "\n Vertex "
       << d << ": ";
    for (auto x : adjList[d])
      cout << to_string(x.first) + "(" << to_string(x.second) + ")" << ", ";
    cout << "" << endl;
  }
}

// helper function to convert from degree to radians
double Graph::toRadians(double degree) {
    double convert = (M_PI) / 180.0;
    return (convert * degree);
} 

// helper function to get weight/distance between 2 airports
double Graph::getWeight(int sourceAirportId, int destAirportId) {
    double srcLat = -1;
    double srcLong = -1;
    double destLat = -1;
    double destLong = -1;

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

        /*
            row[0] is airport ID
            row[6] is latitude
            row[7] is longitude
        */
        // convert airport ID to int
        stringstream idStr(row[0]);
        int id = 0;
        idStr >> id;

        if (sourceAirportId == id) {
            // convert from string to double
            stringstream latStr(row[6]);
            double latitude = 0;
            latStr >> latitude;
            stringstream longStr(row[7]);
            double longitude = 0;
            longStr >> longitude;

            srcLat = latitude;
            srcLong = longitude;
        } else if (destAirportId == id) {
            // convert from string to double
            stringstream latStr(row[6]);
            double latitude = 0;
            latStr >> latitude;
            stringstream longStr(row[7]);
            double longitude = 0;
            longStr >> longitude;

            destLat = latitude;
            destLong = longitude;
        }

        // no need to continue scan dataset if found all data needed
        if (srcLat != -1 && destLat != -1) break;
    }
    fin.close();

    // distance calculations
    srcLat = toRadians(srcLat);
    srcLong = toRadians(srcLong);
    destLat = toRadians(destLat);
    destLong = toRadians(destLong);


    double dlong = destLong - srcLong;
    double dlat = destLat - srcLat;
    double ans = pow(sin(dlat / 2), 2) +
                    cos(srcLat) * cos(destLat) *
                    pow(sin(dlong / 2), 2);
    ans = 2 * asin(sqrt(ans));
    ans = ans * 6371.0; //6371 in km, use 3956 for miles
    return ans;
}

void Graph::createGraph() {
    cout << "Creating graph and edge weights..." << endl;
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

        double currWeight = getWeight(source, dest);
        if (currWeight != -1) {
            addEdge(adjList, source, dest, currWeight);
        }
    }
    // for testing: 
    printGraph(adjList);
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