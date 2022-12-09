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
typedef pair<double, int> dipair;
typedef pair<int, double> idpair;

class Dijkstra {
    public:
        double shortestpath(int start, int dest, Graph g);
        vector<int> getroute(int start, int dest);
    private:
        map<int, int> pre;
};
