#include <iostream>
#include "../src/CleanData.h"
#include "../src/Graph.h"
#include "../src/Dijkstra.h"
#include "../src/Tarjan.h"

using namespace std;

int main() {
    CleanData clean;

    Dijkstra d;
    cout << d.shortestpath(2965,2990) << endl;

    Tarjan t;
    // vector<int> sscList = t.getSscList(106);
    // for(int i: sscList)
    //     cout << i << ", ";
    // cout << "" << endl;
    
}