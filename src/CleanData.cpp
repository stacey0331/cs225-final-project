#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>

#include <cstdio>
#include <stdio.h>

#include "CleanData.h"

using std::stod;

/*
1. 
If any of these column missing, delete that row
- IATA (4)
- Latitude (6)
- Longitude (7)

2.
If latitude is not within -90 to 90, or longitude is not between -180 to 180, delete row
*/
void CleanData::cleanAirports() {
    fstream fin, fout;
    fin.open("../dataset/airports.csv", ios::in);
    fout.open("../dataset/airports_out.csv", ios::out);

    vector<string> row;

    string word, line;
    while(getline(fin, line, '\n')) {
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')) {
            row.push_back(word);
        }

        // // for some reason stod doesn't work here 
        // bool validLat = stod(row[6]) >= -90 && stod(row[6]) <= 90;
        // bool validLong = stod(row[7]) >= -180 && stod(row[7]) <= 180;
        if (row[4] != "\\N" && row[6] != "" && row[7] != "") {
            for(int i = 0; i < (int)row.size() - 1; i++) {
                fout << row[i] << ",";
            }
            fout << row[(int)row.size() - 1] << "\n";
        } 
        // for testing
        else {
            std::cout << __LINE__ << std::endl;
        }
    }

    fin.close();
    fout.close();

    // rename & remove
    if (remove("../dataset/airports.csv") != 0) {
        perror("Error deleting airports.csv");
    } else {
        puts("original airports.csv successfully deleted.");
    }

    if (rename("../dataset/airports_out.csv", "../dataset/airports.csv") == 0) {
        puts("airports.csv successfully renamed");
    } else {
        perror("Error renaming airports_out.csv.");
    }
}

/*
If any of these column missing, delete that row:
- Airline ID (0)
- Name (1)
*/
void CleanData::cleanAirlines() {
    fstream fin, fout;
    fin.open("../dataset/airlines.csv", ios::in);
    fout.open("../dataset/airlines_out.csv", ios::out);

    vector<string> row;

    string word, line;
    while(getline(fin, line, '\n')) {
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')) {
            row.push_back(word);
        }

        if (row[0] != "" && row[0] != "\\N" && row[1] != "") {
            for(int i = 0; i < (int)row.size() - 1; i++) {
                fout << row[i] << ",";
            }
            fout << row[(int)row.size() - 1] << "\n";
        } 
        // // for testing
        // else {
        //     std::cout << __LINE__ << std::endl;
        // }
    }

    fin.close();
    fout.close();

    // rename & remove
    if (remove("../dataset/airlines.csv") != 0) {
        perror("Error deleting airlines.csv");
    } else {
        puts("original airlines.csv successfully deleted.");
    }

    if (rename("../dataset/airlines_out.csv", "../dataset/airlines.csv") == 0) {
        puts("airlines.csv successfully renamed");
    } else {
        perror("Error renaming airlines_out.csv.");
    }
}

/* 
1. 
If any of these column missing, delete that row
- Airline ID (1)
- Source airport(IATA or ICAO) (2)
- Destination airport(IATA or ICAO) (4)

2. 
If stops is not 0 (direct flight), delete that row

3. 
If either "Source airport" or "Destination airport" is not 3 characters, delete that row
*/
void CleanData::cleanRoutes() {
    fstream fin, fout;
    fin.open("../dataset/routes.csv", ios::in);
    fout.open("../dataset/routes_out.csv", ios::out);

    vector<string> row;

    string word, line;
    while(fin >> line) {
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')) {
            row.push_back(word);
        }

        bool isIata = row[2].length() == 3 && row[4].length() == 3;
        if (row[1] != "" && row[2] != "" && row[4] != "" && row[7] == "0" && isIata) {
            for(int i = 0; i < (int)row.size() - 1; i++) {
                fout << row[i] << ",";
            }
            fout << row[(int)row.size() - 1] << "\n";
        } 
        // // for testing
        // else {
        //     std::cout << __LINE__ << std::endl;
        // }

        /* only read until white space
           last column contains white space
           this is necessary to skip to next line*/
        getline(fin, word, '\n');
    }

    fin.close();
    fout.close();

    // rename & remove
    if (remove("../dataset/routes.csv") != 0) {
        perror("Error deleting routes.csv");
    } else {
        puts("original routes.csv successfully deleted.");
    }

    if (rename("../dataset/routes_out.csv", "../dataset/routes.csv") == 0) {
        puts("routes_out.csv successfully renamed");
    } else {
        perror("Error renaming routes_out.csv");
    }
}

void CleanData::cleanAll() {
    cleanRoutes();
    cleanAirports();
    cleanAirlines();
}