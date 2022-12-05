EXENAME = cs225-final-project-master
TEST = test

OBJS = main.o dijkstra.o CleanData.o Graph.o


CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpthread -lm

all: $(EXENAME)

# $(EXENAME): $(OBJS)
# 	$(LD) $^ $(LDFLAGS) -o $@
$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o: main.cpp
	$(CXX) $< $(CXXFLAGS)

tests.o: /workspaces/cs225/cs225-final-project-master/tests/tests.cpp
	$(CXX) $< $(CXXFLAGS)

dijkstra.o: dijkstra.cpp
	$(CXX) $< $(CXXFLAGS)
CleanData.o:CleanData.cpp
	$(CXX) $< $(CXXFLAGS)
Graph.o:Graph.cpp
	$(CXX) $< $(CXXFLAGS)

test: tests.o dijkstra.o CleanData.o Graph.o
	$(LD) tests.o dijkstra.o CleanData.o Graph.o $(LDFLAGS) -o test
clean:
	-rm -f *.o $(EXENAME)