#include <iostream>
#include <vector>
#include <set>

using namespace std;

class CleanData {
    public:
        CleanData();
        void cleanAirports();
        void cleanAirlines();
        void cleanRoutes();
    private: 
        vector<bool> airportAvail;

        // // 2022 top 6 airlines 2 letter IATA code, according to Skytrax
        // set<string> topAirlinesCode;
};