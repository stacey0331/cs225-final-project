# Development Log (Date: 11/12/22 -- 11/18/22)

## Weekly Goals
* Finish the Makefile
* Finish implementing the maps of airports, latitude and longitude.
* Do research to have a deep understanding of our algorithms(Dijkstra's algorithm and Tarjan's algorithm).
## Specific Tasks Completed (and by who)
This week Jianchen Hong implemented the makefile for the test. Stacey Lee and Jianchen Hong did research of the algorithm that we will use next week. Yanjie Han used the struct to do the data processing, so that we are able to get data from the file.
## Problems Encountered 
Since we have some delay last week, we still focousing on the data processing this week. We have no experience of writing the makefile, Jianchen Hong worked it out. When writing the data map program, we are not able to compile. The error is we use getstring with 3 parameters instead of 2. We are still trying to figure it out.
## Plans for next week
Yanjie: implement the Dijkstra's Shortest Path Algorithm.

Stacey and Jianchen: implement Tarjan's Strongly Connected Component Algorithm.
If possible we will try to catch up with our original plan with implementing BFS. 
## Optional: Questions for mentor
* We have some issue when using getstring with 3 parameters [data cleaning code](https://github.com/stacey0331/cs225-final-project/blob/master/src/CleanData.cpp) we need some help.
* Stod issue from last week: it has runtime error that says "libc++abi.dylib: terminating with uncaught exception of type std::invalid_argument: stod: no conversion. " (Code is [here](https://github.com/stacey0331/cs225-final-project/blob/master/src/CleanData.cpp#L39-L41))