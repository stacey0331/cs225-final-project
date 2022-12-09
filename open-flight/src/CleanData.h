/*
    Author: Stacey Lee
*/
#include <iostream>
#include <vector>

using namespace std;

class CleanData {
    public:
        CleanData();
        void cleanAirports();
        void cleanAirlines();
        void cleanRoutes();
        // bool inTop20(string airline);
    private: 
        vector<bool> airportAvail;

        // // 2022 top 20 airlines 2 letter IATA code, according to Skytrax
        // vector<string> topAirlinesCode; 
};