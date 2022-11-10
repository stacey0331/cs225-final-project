#include <fstream>
#include <sstream>
#include <vector>

#include <cstdio>
#include <stdio.h>

#include "CleanData.h"

void CleanData::cleanAirports() {

}

void CleanData::cleanAirlines() {

}

/* 
1. 
If any of these column missing, delete that row
- Airline(IATA or ICAO)
- Source airport(IATA or ICAO)
- Destination airport(IATA or ICAO)

2. 
If stops is not 0 (direct flight), delete that row
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

        if (row[0] != "" && row[2] != "" && row[4] != "" && row[7] == "0") {
            for(int i = 0; i < (int)row.size() - 1; i++) {
                fout << row[i] << ",";
            }
            fout << row[(int)row.size() - 1] << "\n";
        } 
        // // for testing
        // else {
        //     std::cout << "Hello" << std::endl;
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
        puts("routes.csv successfully deleted.");
    }

    if (rename("../dataset/routes_out.csv", "../dataset/routes.csv") == 0) {
        puts("File successfully renamed");
    } else {
        perror("Error renaming");
    }
}