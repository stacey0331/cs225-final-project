/*
    Author: Stacey Lee
*/
#include <vector>
#include <stack>

#include "Graph.h"

class Tarjan {
    public:
        Tarjan();
        void findScc(int u);
        vector<int> getSccList(int airportId);
        vector<vector<int>> getSccVec();

    private:
        vector<vector<pair<int, double>>> adjList;
        vector<int> disc;
        vector<int> low;
        vector<bool> stackMember;
        stack<int> st;

        /* 
            sccInd:
            -2: haven't assign
            -1: itself is a component
            others: index in sccVec
        */
        vector<int> sccInd; 
        vector<vector<int>> sccVec; // each element is a stongly connected component
        int compCount; // index of sccVec
};