/*
    Author: Stacey Lee
    This file implements Tarjan's algorithm to find Strongly
    connected components. 
*/
#include <iostream>
#include <vector>
#include <stack>

#include "Tarjan.h"

using namespace std;

/*
    Default constructor
    Calls function to find strongly connected components
*/
Tarjan::Tarjan() {
    compCount = 0;
    Graph g;
    adjList = g.getAdjList();
    // Initialize vectors
    for (int i = 0; i < (int)adjList.size(); i++) {
        disc.push_back(-1);
        low.push_back(-1);
        stackMember.push_back(false);
        sccInd.push_back(-2);
    }
 
    // Call the recursive function to find strongly
    // connected components in DFS with vertex i
    // This uses DFS traversals
    for (int i = 0; i < (int)adjList.size(); i++) {
        if (disc[i] == -1) {
            findScc(i);
        }
    }
}

/*
    Recursive function finding strongly connected components
    using DFS traversals
    sccVec: 2D vector storing each strongly connected components
            in each row.
    sccInd: indicate which row/component in sccVec this airports belongs to
*/
void Tarjan::findScc(int u) {
    static int time = 0;
 
    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;
    st.push(u);
    stackMember[u] = true;
 
    // Go through all adjacent vertices
    for (int i = 0; i < (int)adjList[u].size(); i++) {
        int v = adjList[u][i].first; // v is current adjacent of u
 
        // if v is not visited yet
        if (disc[v] == -1) {
            findScc(v);
            low[u] = min(low[u], low[v]);
        } else if (stackMember[v] == true)
            low[u] = min(low[u], disc[v]);
    }
 
    // if head node is found, pop the stack
    int w = 0;
    if (low[u] == disc[u]) {
        vector<int> temp;
        bool moreThanItself = false;
        while (st.top() != u) {
            moreThanItself = true;
            w = (int)st.top();
            // cout << w << " ";
            temp.push_back(w);
            sccInd[w] = compCount;
            stackMember[w] = false;
            st.pop();
        }
        // process the node st.top() == u
        w = (int)st.top();
        temp.push_back(w);
        if (moreThanItself) {
            sccInd[w] = compCount;
            sccVec.push_back(temp);
            compCount++;
        } else {
            sccInd[w] = -1;
        }
        stackMember[w] = false;
        st.pop();
    }
}

// helper function to get a list of node that are strongly connected to
// an airport, by its airport id
vector<int> Tarjan::getSccList(int airportId) {
    vector<int> outV;
    if (sccInd[airportId] >= 0) {
        return sccVec[sccInd[airportId]];
    } else if (sccInd[airportId] == -1) {
        outV.push_back(airportId);
    } else {
        outV.push_back(-1);
        cout << "Tarjan code error" << endl;
    }
    return outV;
}

// helper function to get private member sccVec
vector<vector<int>> Tarjan::getSccVec() {
    return sccVec;
}
