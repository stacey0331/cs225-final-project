/*
    Author: Stacey Lee
*/
#include <iostream>
#include <vector>
#include <stack>

#include "Tarjan.h"

using namespace std;

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
    for (int i = 0; i < (int)adjList.size(); i++) {
        if (disc[i] == -1) {
            findScc(i);
        }
    }

    // // for testing:
    // for(vector<int> i: sccVec) {
    //     cout << (int)i.size() << endl;
    // }
}

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
        // cout << w << "\n";
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

vector<vector<int>> Tarjan::getSccVec() {
    return sccVec;
}
