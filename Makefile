# Tyler Burkhardt

CXX=clang++ $(CXXFLAGS)
CXXFLAGS=-O2 -Wall
DEBUG=-g
OBJECTS=wordPuzzle.o hashTable.o timer.o

wordPuzzle: $(OBJECTS)
	$(CXX) $(DEBUG) $(OBJECTS)

wordPuzzle.o: wordPuzzle.cpp hashTable.h timer.h
hashTable.o: hashTable.cpp hashTable.h

.PHONY: clean
clean:
	-rm -f *.o *~ a.out
