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

double Dijkstra::shortestpath(int start, int dest) {
    Graph g;
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
            if (dist.at(v)> dist.at(u) + weight) {
                //update the distance of v;
                dist.at(v) = dist.at(u) + weight;
                pq.push(make_pair(dist.at(v), v));
            }
        }
        // for (int i = 0; i < volume; i++) {
        //     for(int j = 0; j < (int)adjlist[i].size(); j++) {
        //         // get the airport and the distance
        //         int v = adjlist[i][j].first;
        //         int weight = adjlist[i][j].second;
        //         // if there is a shorter path of v;
        //         if (dist[v] > dist[i] + weight) {
        //             //update the distance of v;
        //             dist[v] = dist[i] + weight;
        //             pq.push(make_pair(dist[v], v));
        //         }
        //     }
        // }
    }
    // cout << start << endl;
    // cout << dest << endl;
    // for (int i = 2900; i < 3000; i++) {
    //     cout << dist.at(i) << endl;
    // }
    return dist.at(dest);
}
