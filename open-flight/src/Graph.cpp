/*
    Author: Stacey Lee
*/
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

// default constructor
Graph::Graph() {
    numAirport = 4391;
    for(int i = 0; i < numAirport; i++) {
        vector<pair<int, double>> temp;
        adjList.push_back(temp);
    }
    mapLatLong();
    mapAirportCodeName();
    createGraph();
}

// add an edge from node a to node b with weight
void Graph::addEdge(int a, int b, double weight) {
  adjList[a].push_back(make_pair(b, weight));
}

// helper function to convert from degree to radians
double Graph::toRadians(double degree) {
    double convert = (M_PI) / 180.0;
    return (convert * degree);
} 

// helper function to get weight/distance between 2 airports
double Graph::getWeight(int sourceAirportId, int destAirportId) {
    double srcLat = toRadians(latMap[sourceAirportId]);
    double srcLong = toRadians(longMap[sourceAirportId]);
    double destLat = toRadians(latMap[destAirportId]);
    double destLong = toRadians(longMap[destAirportId]);

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
            addEdge(source, dest, currWeight);
        }
    }
    fin.close();
}


// Read airports.csv and map the airports IATA to its airport ID
void Graph::mapAirportCodeName() {
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
            row[1] is airport name
            row[4] is airport IATA
        */
        stringstream idStr(row[0]);
        int id = 0;
        idStr >> id;

        airportCode[id] = row[4];
        airportName[id] = row[1];
    }
    fin.close();
}

// Read airports.csv and map latitude and longtitude to its airport id
// in seperate maps
void Graph::mapLatLong() {
    fstream fin;
    fin.open("../dataset/airports.csv", ios::in);

    vector<string> row;
    string word, line;

    int id = 0;
    double latitude = 0;
    double longitude = 0;
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
        idStr >> id;
        // convert lat/long to double
        stringstream latStr(row[6]);
        latStr >> latitude;
        stringstream longStr(row[7]);
        longStr >> longitude;

        latMap[id] = latitude;
        longMap[id] = longitude;
    }
    fin.close();
}

// helper function to get private member adjList
vector<vector<pair<int, double>>> Graph::getAdjList() {
    return adjList;
}

/* 
    Helper function for private member map
    Get airport ID with its 3-letter IATA code
    return -1 if not found 
*/
int Graph::getAirportIdByCode(string iata) {
    iata = "\"" + iata + "\"";
    map<int, string>::iterator it;
    for (it = airportCode.begin(); it != airportCode.end(); it++) {
        if (it->second.compare(iata) == 0) {
            return it->first;
        }
    }
    return -1;
}

/*
    Helper function for private member map
    Get airport IATA code by its airport ID
*/
string Graph::getAirportCodeById(int id) {
    return airportCode[id].substr(1,3);
}

/*
    Helper function
    Get airport full name by its airport ID
*/
string Graph::getAirportNameById(int id) {
    return airportName[id].substr(1,airportName[id].length() - 2);
}

/*
    Helper function
    Get the maximum id of airport
    (note: doesn't equal the actual number of airports in the graph
    because some airport id does not match any airports)
*/
int Graph::getnumAirport() {
    return adjList.size();
}