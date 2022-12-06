#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <sstream>
#include "../src/CleanData.h"

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