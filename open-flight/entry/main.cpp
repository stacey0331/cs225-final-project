#include <iostream>
#include "../src/CleanData.h"
#include "../src/Graph.h"
#include "../src/Dijkstra.h"

using namespace std;

int main() {
    CleanData clean;
    clean.cleanAll();

    Graph g;

    Dijkstra d;
    cout << d.shortestpath(2965,2990) << endl;
}