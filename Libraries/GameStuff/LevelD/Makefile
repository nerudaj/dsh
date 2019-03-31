RM=del

# TODO: platform dep code
CXX=g++
CXXFLAGS= -std=gnu++14 -Wall -Wextra -pedantic

all: LevelDHandler.o ParserModuleMesh.o

LevelDHandler.o: LevelDHandler.cpp
	$(CXX) $(CXXFLAGS) $^ -c

ParserModuleMesh.o: ParserModules/ParserModuleMesh.cpp
	$(CXX) $(CXXFLAGS) $^ -c

clean:
	$(RM) *.o