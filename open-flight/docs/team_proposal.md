# Project proposal 

## Leading Question 
By using flight routes and airports data, we want to create tools for travel enthusiasts to find the best way to travel. There're 2 tools: 

Find the shortest routes by airport. 
   * By taking the source and destination airports from user input, this tool generates the shortest routes in terms of which airline to take and all the airports in between. We will achieve this by using Dijkstra's Shortest Path algorithm. 

Find a cluster of places that can be visited in order
   * By taking the user's nearest airport from user input, this tool will use Tarjan's strongly connected component algorithm to find a list of airports that are strongly connected to the current airport and list them out using BFS. We chose BFS over DFS because we want the user's travel to be as convenient as possible without needing to layover frequently. 


## Dataset Acquisition
[OpenFlights Airport, airline, and route data](https://openflights.org/data.html)


## Data Format
The data files we'll use are routes.txt, airlines.txt, and airports.txt. They will be put in the /dataset directory. The dataset is in the format of comma separated values. Routes.txt has 67663 entries, airlines.txt has 5888 entries, and airports.txt has 7698 entries. We will be using all the data for accuracy, even though that’s a lot of data. 
For our program, all thel input and output locations will be airports in the format of 3-letter IATA codes. There will not be any country or city names involved. 


## Data Correction
When we find an missing entry in any of the column we need, we will delete that entry completely. For latitude and longitude data, we will delete the data that are out of the correct range (-90 to 90 for latitude and -180 to 180 for longitude). 


## Data Storage
We will use adjacency list (with weights) to store routes. because Tarjan's strongly connected components algorithm requires a directed graph as input, we will use an adjacency list to represent all the routes available. Since the routes graph is probably sparse, we will use an adjacency list over an adjacency matrix for efficiency. And then, we will use map to store airlines' name, airports' latitudes, and longitude with keys in routes.txt.: we will use airlines' name for output readability, since routes.txt only has airline code and identifiers. We will use airports' latitude and longitude to complete the adjacency list edge weights. 

The storage cost for the adjacency list will be approximately O(V+E), where V is the number of airports in the data file and E is the number of routes. The space complexity for each map is O(n), where n is the number of airports. 


## Algorithm 
Dijkstra's Shortest Path Algorithm
   * Function Inputs: takes 2 airports from user input in the terminal. 
   * Function Outputs: prints the airlines and airports in between. 
   * Function Efficiency: for an adjacency list, Dijkstra's algorithm's time complexity is O(V+E)logV. Its space complexity will be O(V+E). 

Tarjan's Strongly Connected Component Algorithm
   * Function Inputs: takes 1 airport from user input in the terminal. 
   * Function Outputs: a list of airports that are strongly connected to the input airport.  
   * Function Efficiency: since Tarjan's Strongly Connected Component Algorithm is based off DFS, its time complexity will be O(V+E), and space complexity will be O(V). 

BFS
   * Function Inputs: a list of airports that are strongly connected.
   * Function Outputs: a list of airports to visit in BFS order.
   * Function Efficiency: time complexity is O(V+E) when adjacency list is used. Its space complexity will be O(V) since in the worst case we have to hold all vertices in the queue. 


## Timeline
### Week 1 (Nov7-Nov11):
Do these in order: 
* Complete data correction/cleaning. 
* Create airports' latitude and airports' longitude map. 
* Create routes adjacency list (use the maps to calculate weights). 


### Week 2 (Nov14-Nov18) [Mid-project checkin]
* Yanjie and Shuyuan: implement the Dijkstra's Shortest Path Algorithm. 
* Stacey and Jianchen: implement Tarjan's Strongly Connected Component Algorithm. 


### Week 3 (Nov 21-Nov 25)
* Yanjie and Shuyuan: create airlines' name map and convert output airline from airline ID to airline name for readability. 
* Stacey and Jianchen: implement BFS. 


### Week 4 (Nov 28-Dec 2)
* Finish any code left behind. 
* Clean up prompts/output formats in terminal. 
* Finish writing tests cases. 


### Week 5 (Dec 5-Dec8)
* Finish README
* Finish written report
* Final presentation video planning, slides, editing