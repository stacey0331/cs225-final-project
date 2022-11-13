EXENAME = main
OBJS = main.o dijkstra.o CleanData.o Graph.o

CXX = clang++
CXXFLAGS = -std=c++0x -c -g -O0 -Wall -Wextra
LD = clang++
LDFLAGS = -std=c++0x

all: $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

main.o: main.cpp
	$(CXX) $< $(CXXFLAGS)

dijkstra.o: dijkstra.cpp
	$(CXX) $< $(CXXFLAGS)
CleanData.o:CleanData.cpp
	$(CXX) $< $(CXXFLAGS)
Graph.o:Graph.cpp
	$(CXX) $< $(CXXFLAGS)

clean:
	-rm -f *.o $(EXENAME)