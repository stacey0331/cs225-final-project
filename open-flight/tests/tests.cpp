#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <sstream>
#include "../src/CleanData.h"
#include "../src/Dijkstra.h"
#include "../src/Tarjan.h"
#include "../src/Graph.h"

TEST_CASE("CleanData::cleanRoutes", "[cleandata]") {
    fstream fin;
    fin.open("../dataset/routes.csv", ios::in);
    vector<string> row;

    string word, line;
    while(fin >> line) {
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')) {
            row.push_back(word);
        }

        REQUIRE(row[1] != "");
        REQUIRE(row[2] != "");
        REQUIRE(row[2].length() == 3);
        REQUIRE(row[4] != "");
        REQUIRE(row[4].length() == 3);
        REQUIRE(row[7] == "0");

        /* only read until white space
           last column contains white space
           this is necessary to skip to next line*/
        getline(fin, word, '\n');
    }
    fin.close();
}

TEST_CASE("CleanData::cleanAirports", "[cleandata]") {
    fstream fin;
    fin.open("../dataset/airports.csv", ios::in);

    vector<string> row;

    string word, line;
    while(getline(fin, line, '\n')) {
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')) {
            row.push_back(word);
        }

        REQUIRE(row[4] != "\\N");
        REQUIRE(row[6] != "");
        REQUIRE(row[7] != "");

        stringstream latStr(row[6]);
        stringstream longStr(row[7]);
        double latN = 0;
        double longN = 0;
        latStr >> latN;
        longStr >> longN;

        REQUIRE(((latN >= -90) && (latN <= 90)) == true);
        REQUIRE(((longN >= -180) && (longN <= 180)) == true);
    }
    fin.close();
}

TEST_CASE("CleanData::cleanAirlines", "[cleandata]") {
    fstream fin;
    fin.open("../dataset/airlines.csv", ios::in);

    vector<string> row;

    string word, line;
    while(getline(fin, line, '\n')) {
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')) {
            row.push_back(word);
        }
        REQUIRE(row[0] != "");
        REQUIRE(row[0] != "\\N");
        REQUIRE(row[1] != "");
    }
    fin.close();
}

TEST_CASE("Graph:: correct adjacency list edge") {
    Graph g;
    vector<vector<pair<int, double>>> adjList = g.getAdjList();

    fstream fin;
    fin.open("../dataset/routes.csv", ios::in);

    int to10 = 0;
    vector<string> row;
    string word, line;
    while(getline(fin, line, '\n') && (to10 < 10)) {
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')) {
            row.push_back(word);
        }

        // row[3] is source airport ID
        // row[5] is destination airport ID
        // convert string to int
        stringstream sourceStr(row[3]);
        int source = 0;
        sourceStr >> source;
        stringstream destStr(row[5]);
        int dest = 0;
        destStr >> dest;

        bool containsEdge = false;
        vector<pair<int, double>> currAdj = adjList[source];
        for(pair<int, double> i: currAdj) {
            if (i.first == dest) containsEdge = true;
        }
        REQUIRE(containsEdge == true);
        to10++;
    }
    fin.close();
}

TEST_CASE("Tarjan::can reach other vertex in same component", "[Tarjan]") {
    Tarjan t;
    Dijkstra d;
    Graph g;
    #define INF 0x3f3f3f3f
    vector<vector<int>> sccVec = t.getSccVec();

    for(int k = 0; k < 10; k++) {
        int randI = 0 + (rand() % ((int)sccVec.size() - 1));
        int randJ = 0 + (rand() % ((int)sccVec[randI].size() - 1));
        int randNum = -1;
        bool validRand = false;

        while(validRand == false) {
            randNum = 0 + (rand() % ((int)sccVec[randI].size() - 1));
            validRand = (randNum != randJ);
        }
        REQUIRE(d.shortestpath(sccVec[randI][randJ], sccVec[randI][randNum], g) != INF);
        REQUIRE(d.shortestpath(sccVec[randI][randNum], sccVec[randI][randJ], g) != INF);
    }
}

TEST_CASE("Dijkstra::Direct flight", "[Dijkstra]") {
    CleanData clean;
    Graph g;
    Dijkstra d;
    int dist = d.shortestpath(2965, 2990, g);
    vector<int> r = d.getroute(2965, 2990);
    int truedist = 0;
    vector<vector<pair<int, double>>> graph = g.getAdjList();
    for (unsigned i = 0; i < graph.at(2965).size(); i++) {
        if (graph.at(2965).at(i).first == 2990) {
            truedist = graph.at(2965).at(i).second;
            break;
        }
    }
    REQUIRE(dist == truedist);
    REQUIRE(r.at(0) == 2965);
    REQUIRE(r.at(1) == 2990);
}

TEST_CASE("Dijkstra::Flight with transfer", "[Dijkstra]") {
    Dijkstra d;
    Graph g;
    int dist = d.shortestpath(2965, 2966, g);
    vector<int> r = d.getroute(2965, 2966);
    REQUIRE(dist == 1433);
    REQUIRE(r.at(0) == 2965);
    REQUIRE(r.at(1) == 3964);
    REQUIRE(r.at(2) == 2962);
    REQUIRE(r.at(3) == 2966);
}
