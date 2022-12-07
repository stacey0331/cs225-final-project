#include <iostream>
#include <string>
#include <algorithm>

#include "../src/CleanData.h"
#include "../src/Graph.h"
#include "../src/Dijkstra.h"
#include "../src/Tarjan.h"

using namespace std;

void shortestPath(Graph g);
void findCluster(Graph g);

void finishTool(Graph g) {
    cout << "" << endl;
    cout << "Do you wish to keep using this program?" << endl;
    cout << "1. Yes, continue with find shortest routes tool." << endl;
    cout << "2. Yes, continue with airport cluster tool." << endl;
    cout << "3. No" << endl;
    cout << "\tYour choice: ";
    int input;
    cin >> input;
    switch(input) {
        case 1:
            shortestPath(g);
            break;
        case 2:
            findCluster(g);
            break;
        case 3: 
            cout << "Thanks for using this program. Bye. " << endl;
            cout << "" << endl;
            cout << "" << endl;
            cout << "" << endl;
            return;
        default:
            cout << "Please enter a valid choice (a single number without anything else)." << endl;
            finishTool(g);
    }
}

void shortestPath(Graph g) {
    Dijkstra d;
    string source, dest;
    cout << "-----------------" << endl;
    cout << "Find the shortest routes between 2 airports." << endl;
    cout << "" << endl;
    
    cout << "Please enter a source airport's 3-letter IATA code (e.g. ORD)" << ": ";
    cin >> source;
    transform(source.begin(), source.end(), source.begin(), ::toupper);

    cout << "Please enter a destination airport's 3-letter IATA code (e.g. ORD)" << ": ";
    cin >> dest;
    transform(dest.begin(), dest.end(), dest.begin(), ::toupper);

    cout << "" << endl;
    if (g.getAirportIdByCode(source) == -1 || g.getAirportIdByCode(dest) == -1) {
        cout << "Please enter correct airport IATA codes. " << endl;
        shortestPath(g);
    } else {
        cout << "Distance: " + to_string(d.shortestpath(g.getAirportIdByCode(source), g.getAirportIdByCode(dest), g)) << endl;
    }
    finishTool(g);
}

void findCluster(Graph g) {
    Tarjan t;
    string airportIn;
    vector<int> clusterV;
    cout << "-----------------" << endl;
    cout << "Find an airport cluster/strongly connected components." << endl;
    cout << "Given an airport (by you), we will give you a list of airports that are ";
    cout << "\"strongly connected\", which means all these airports are reachable to and from each other." << endl;
    cout << "" << endl;

    cout << "Please enter an airport's 3-letter IATA code (e.g. ORD)" << ": ";
    cin >> airportIn;
    transform(airportIn.begin(), airportIn.end(), airportIn.begin(), ::toupper);
    
    cout << "" << endl;
    if (g.getAirportIdByCode(airportIn) == -1) {
        cout << "Please enter a correct airport IATA code. " << endl;
        findCluster(g);
    } else {
        clusterV = t.getSscList(g.getAirportIdByCode(airportIn));
        cout << "Airports that are strongly connected to " + airportIn + ": " << endl;
        for(int i = 0; i < (int)clusterV.size() - 1; i++) {
            cout << g.getAirportNameById(clusterV[i]) << ", ";
        }
        cout << g.getAirportNameById(clusterV[(int)clusterV.size() - 1]) + "." << endl;
    }
    finishTool(g);
}

void selectTool() {
    Graph g;
    cout << "-----------------" << endl;
    cout << "Please select tool (by typing its number): " << endl;
    cout << "1. Find the shortest routes between 2 airports. " << endl;
    cout << "2. Find an airport cluster/strongly connected components. " << endl;
    cout << "\tYour choice: ";
    int input;
    cin >> input;
    switch(input) {
        case 0:
            cout << "Thanks for using this program. Bye. " << endl;
            cout << "" << endl;
            cout << "" << endl;
            cout << "" << endl;
            return;
        case 1:
            shortestPath(g);
            break;
        case 2: 
            findCluster(g);
            break;
        default:
            cout << "Please enter a valid choice (a single number without anything else)." << endl;
            selectTool();
  }
}

int main() {
    // constructor will call data correction functions
    CleanData clean;

    // Dijkstra d;
    // // 2965: AER
    // // 2990: KZN
    // cout << d.shortestpath(2965,2990) << endl;

    // Tarjan t;
    // vector<int> sscList = t.getSscList(106);
    // for(int i: sscList)
    //     cout << i << ", ";
    // cout << "" << endl;

    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;

    cout << "Hi, welcome to this flights planning tool." << endl;
    cout << "(Note: the routes data we use are last updated 2014)" << endl;
    selectTool();
}