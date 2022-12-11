/*
    Author: Yanjie Han
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
#define INF 0x3f3f3f3f
// types use to pair the airports with the weight.
typedef pair<double, int> dipair;
typedef pair<int, double> idpair;

class Dijkstra {
    public:
        // get the shortest distance between two airports 
        // and also store the routes in the map;
        double shortestpath(int start, int dest, Graph g);
        // return a vector of airports ID that the shortest path
        // need to reach;
        vector<int> getroute(int start, int dest);
    private:
        // this map store the previous vertex of a specific vertex;
        map<int, int> pre;
};
