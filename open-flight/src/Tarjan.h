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
        vector<int> getSscList(int airportId);
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
            others: index in sscVec
        */
        vector<int> sccInd; 
        vector<vector<int>> sscVec; // each element is a stongly connected component
        int compCount;
};