/*
    Author: Stacey Lee, Jianchen Hong
*/
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>

#include <cstdio>
#include <stdio.h>
#include <algorithm>

#include "CleanData.h"

using std::stod;

CleanData::CleanData() {
    for(int i = 0; i <= 14110; i++) {
        airportAvail.push_back(false);
    }
    
    // cleanAirports must go before cleanRoutes because of airportAvail
    cleanAirports();
    cleanRoutes();
    cleanAirlines();
}

/*
1. 
If any of these column missing, delete that row
- Airport ID (0)
- IATA (4)
- Latitude (6)
- Longitude (7)

2
If latitude is not within -90 to 90, or longitude is not between -180 to 180, delete row

3. Since after manual testing we notice airports after airport id 4390 basically have no routes, 
we will cut this dataset until that. 
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

        stringstream latStr(row[6]);
        stringstream longStr(row[7]);
        double latN = 0;
        double longN = 0;
        latStr >> latN;
        longStr >> longN;

        bool validLat = (latN >= -90) && (latN <= 90);
        bool validLong = (longN >= -180) && (longN <= 180);
        if (row[4] != "\\N" && row[6] != "" && row[7] != "" && validLat && validLong) {
            for(int i = 0; i < (int)row.size() - 1; i++) {
                fout << row[i] << ",";
            }
            fout << row[(int)row.size() - 1] << "\n";
        }
        
        stringstream idStr(row[0]);
        int id = 0;
        idStr >> id;

        // assign airportAvail
        airportAvail[id] = true;
        if (id == 4390) break;
    }

    fin.close();
    fout.close();

    // rename & remove
    if (remove("../dataset/airports.csv") != 0) {
        perror("Error deleting airports.csv");
    }

    if (rename("../dataset/airports_out.csv", "../dataset/airports.csv") != 0) {
        perror("Error renaming airports_out.csv.");
    }
}

/*
1. 
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
    }

    fin.close();
    fout.close();

    // rename & remove
    if (remove("../dataset/airlines.csv") != 0) {
        perror("Error deleting airlines.csv");
    }

    if (rename("../dataset/airlines_out.csv", "../dataset/airlines.csv") != 0) {
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

4.
If either the source or destination airport is not in airport.csv, delete that route
source airport id is column 3, destination id is 5

5.
Delete route if flight is codeshare, since it creates confusions

6. (disabled now, use if too slow)
Only top 20 airlines routes will be kept, in set "topAirlinesCode"
Airline IATA: column 0

*/
void CleanData::cleanRoutes() {
    fstream fin, fout;
    fin.open("../dataset/routes.csv", ios::in);
    fout.open("../dataset/routes_out.csv", ios::out);

    vector<string> row;
    bool airportExsits;

    string word, line;
    while(fin >> line) {
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')) {
            row.push_back(word);
        }

        // check 4. if airport exsits
        stringstream sourceStr(row[3]);
        int source = 0;
        sourceStr >> source;
        stringstream destStr(row[5]);
        int dest = 0;
        destStr >> dest;
        airportExsits = true;
        if (airportAvail[source] == false || airportAvail[dest] == false) {
            airportExsits = false;
        }

        bool isIata = row[2].length() == 3 && row[4].length() == 3;
        if (airportExsits && row[1] != "" && row[2] != "" && row[4] != "" && row[6] != "Y" && row[7] == "0" && isIata) {
            for(int i = 0; i < (int)row.size() - 1; i++) {
                fout << row[i] << ",";
            }
            fout << row[(int)row.size() - 1] << "\n";
        } 

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
    }

    if (rename("../dataset/routes_out.csv", "../dataset/routes.csv") != 0) {
        perror("Error renaming routes_out.csv");
    }
}
