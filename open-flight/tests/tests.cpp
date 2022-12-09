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


TEST_CASE("Tarjan::includes all nodes in graph", "[Tarjan]") {
    vector<int> exist;
    Graph g;
    Tarjan t;
    vector<vector<int>> sccVec = t.getSccVec();
    for(int i=0; i<g.getnumAirport(); i++) {
        exist.push_back(-1);
    }
    for(int i=0; i < (int)sccVec.size(); i++) {
        for(int j=0; j < (int)sccVec[i].size(); j++) {
            exist[sccVec[i][j]] = 1;
        }
    }
    for(int i = 0; i < g.getnumAirport(); i++) {
        REQUIRE(exist[i] == 1);
    }
}


TEST_CASE("Tarjan::can reach other vertex in component", "[Tarjan]") {
    Tarjan t;
    Dijkstra d;
    Graph g;
    #define INF 0x3f3f3f3f
    vector<vector<int>> sccVec = t.getSccVec();
    for(int i=0; i<(int)sccVec.size(); i++) {
        for(int j=0;j<(int)sccVec[i].size(); j++) {
            bool validRand = false;
            int randNum = -1;
            while(validRand == false) {
                randNum = 0 + (rand() % sccVec[i].size() - 1);
                validRand = (0 + (rand() % sccVec[i].size() - 1) != j);
            }
            REQUIRE(d.shortestpath(sccVec[i][j], sccVec[i][randNum], g) != INF);
            REQUIRE(d.shortestpath(sccVec[i][randNum], sccVec[i][j], g) != INF);
        }
    }
}