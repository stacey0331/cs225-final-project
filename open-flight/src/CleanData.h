/*
    Author: Stacey Lee, Jianchen Hong
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
    private: 
        vector<bool> airportAvail;
};