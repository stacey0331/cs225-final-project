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
#include <map>
#include <queue>


#include "Dijkstra.h"
using namespace std;

// Input 2 airport id, return the shortest distance needed to travel using weight of the graph
double Dijkstra::shortestpath(int start, int dest, Graph g) {
    vector<vector<idpair>> adjlist = g.getAdjList();
    // create a priority queue to sort the distances in increasing order;
    priority_queue<dipair, vector<dipair>, greater<dipair>> pq;
    int volume = adjlist.size();
    // initialize the distance for all airports to INFITE;
    vector<double> dist(volume, INF);
    // cout << volume << endl;
    for(int i = 0; i < volume; i++) {
        dist.push_back(INF);
    }
    // initialize the start point with distance 0;
    pq.push(make_pair(0, start));
    dist.at(start) = 0;
    // cout << "here" << endl;
    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (size_t i = 0; i < adjlist[u].size(); i++) {
            // get the airport and the distance
            int v = adjlist.at(u).at(i).first;
            int weight = adjlist.at(u).at(i).second;
            // if there is a shorter path of v;
            if (dist.at(v) > dist.at(u) + weight) {
                //update the distance of v;
                dist.at(v) = dist.at(u) + weight;
                pq.push(make_pair(dist.at(v), v));
                // update the previous vertex of v;
                pre[v] = u;
            }
        }
    }
    return dist.at(dest);
}

// Input 2 airport id, return a vector with all the airports/node in the path. 
vector<int> Dijkstra::getroute(int start, int dest) {
    int s = dest;
    vector<int> route;
    vector<int> previous;
    // use the map from shortestpath to get the previous point;
    while (s != start) {
        previous.push_back(s);
        s = pre[s];  
    }
    previous.push_back(start);
    // reverse the vector to make a new vector which start with the start point
    // and end with the destination;
    for (size_t i = previous.size(); i > 0; i--) {
        route.push_back(previous.at(i - 1));
    }
    return route;
}
