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

double Dijkstra::shortestpath(int start, int dest) {
    Graph g;
    vector<idpair> adjlist = g.getAdjList();
    // create a priority queue to sort the distances in increasing order;
    priority_queue<dipair, vector<dipair>, greater<dipair>> pq;
    int volume = adjlist.size();
    // initialize the distance for all airports to INFITE;
    vector<double> dist;
    for(int i = 0; i < volume; i++) {
        dist.push_back(INF);
    }
    // initialize the start point with distance 0;
    pq.push(make_pair(0, start));
    dist[start] = 0;

    while(!pq.empty()) {
        for (int i = 0; i < volume; i++) {
            // get the airport and the distance
            int v = adjlist[i].first;
            int weight = adjlist[i].second;
            // if there is a shorter path of v;
            if (dist[v] > dist[i] + weight) {
                //update the distance of v;
                dist[v] = dist[i] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist[dest];
}
