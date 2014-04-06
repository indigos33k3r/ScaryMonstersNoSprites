CXX=g++
CXXFLAGS=-c -Wall
LDFLAGS=
BUILDOBJS=main.o game.o dungeonworld.o gameentity.o textmap.o

all: scarygame clean

scarygame: main.o game.o dungeonworld.o gameentity.o textmap.o
	$(CXX) $(BUILDOBJS) -o scarygame $(LDFLAGS) 

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp 

game.o: game.cpp
	$(CXX) $(CXXFLAGS) game.cpp  

dungeonworld.o: dungeonworld.cpp
	$(CXX) $(CXXFLAGS) dungeonworld.cpp 

gameentity.o: gameentity.cpp
	$(CXX) $(CXXFLAGS) gameentity.cpp 

textmap.o: textmap.cpp
	$(CXX) $(CXXFLAGS) textmap.cpp

clean:
	rm *.o