# Word-Puzzle-Solver #
Project in C++ that takes 2 text files:

1. A dictionary of words to look for
2. A group of characters arranged in a grid pattern

The program will find words facing forwards, backwards, up, down, and any direction diagonally.
The program uses a custom hash table to optimize the amount of time it takes to find the words. No hash tables from the standard library are used.

# How to Run #
### Windows ###
__1.__ Make sure you have a C++ compiler installed (I use MinGW)
__2.__ Clone the repository
__3.__ Open the project in your IDE (I use VSCode)
__4.__ CD into the directory of the project. For example:
```
cd Downloads
```
__5.__ Compile the cpp files (Makefile is for Linux use only)
```
g++ -O2 wordPuzzle.cpp hashTable.cpp timer.cpp
```
__6.__ Execute the file with your dictionary and grid of choice
```
./a.exe testfiles/words.txt testfiles/3x3.grid.txt
```
__7.__ Feel free to use any dictionary/grid you would like!

### Linux ###
__1.__ Clone the repository
__2.__ Open the project in your IDE
__3.__ CD into the directory of the project. For example:
```
cd Downloads
```
__4.__ Make the object files
```
make
```
__5.__ Execute the file with your dictionary and grid of choice
```
./a.out testfiles/words.txt testfiles/3x3.grid.txt
```
__6.__ Feel free to use any dictionary/grid you would like!

# About #
This project was made for CS2150: Program and Data Representation at the University of Virginia

