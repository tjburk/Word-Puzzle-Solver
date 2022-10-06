#include <iostream>
#include <fstream>
#include "hashTable.h"
#include <string>
#include "timer.h"
using namespace std;

// Create a 2-D array of some big size
// Can only handle puzzles up to 500x500
#define MAXROWS 500
#define MAXCOLS 500
char grid[MAXROWS][MAXCOLS];

// Forward declarations
bool readInGrid(string filename, int& rows, int& cols);
string getWordInGrid(int startRow, int startCol, int dir, int len,
                     int numRows, int numCols);
string getDirection(int direction);

int main(int argc, char** argv){

  timer time;
  time.start();
  
  if(argc < 3) //Not enough command line parameters
    return 0;
  
  //Get grid set up
  int rows, columns;
  string gridName = argv[2];
  bool result = readInGrid(gridName, rows, columns);
  if(!result){
    cout << "Error reading in file!" << endl;
    return 1;
  }

  
  //Dictionary File
  ifstream dictFile (argv[1]);

  //One word in dictionary 
  string word;

  //Hash table
  hashTable dictionary;

  //Get every possible word in the dictionary
  if(dictFile.is_open()){
    while(getline(dictFile, word)){
      dictionary.insert(word);
    }
    dictFile.close();
  }

  else
    cout << "Unable to open file" << endl;


  //Get every possible word in the grid
  string prevWord;
  int count = 0;
  for(int r = 0; r < rows; r++){ //rows
    for(int c = 0; c < columns; c++){ //columns
      for(int d = 0; d < 8; d++){ //direction (all 8)
	for(int l = 1; l <= 22; l++){ //length (1 to 22)
	  
          word = getWordInGrid(r, c, d, l, rows, columns); //gets word

	  if(word != prevWord && !isdigit(word[0])){ //If word is unique and first digit is not a number
	    if(word.length() >= 3 && dictionary.find(word)){ //If word is in the dict with a length greater than 3
	      
              cout << getDirection(d) << "(" << r << ", " << c << "):       " << word << endl;
	      count++; //increment count
	      
	    }
	  }
	  prevWord = word; //increment previous word
	}
      }
    }
  }
  cout << count << " words found" << endl;
  time.stop();
  //cout << "Found all words in " << time.getTime() << " seconds" << endl;
  
  return 0;
}

//Helper function to print direction of word based on number
string getDirection(int direction){
  switch(direction){
  case 0:
    return "N ";
    break;
  case 1:
    return "NE";
    break;
  case 2:
    return "E ";
    break;
  case 3:
    return "SE";
    break;
  case 4:
    return "S ";
    break;
  case 5:
    return "SW";
    break;
  case 6:
    return "W ";
    break;
  case 7:
    return "NW";
    break;
  }
  return "";
}


/**********************************************
 * Title: getWordinGrid
 * Author: Aaron Bloomfield
 * Date: 10/16/22 Date Written: 2014
 * Availability: https://github.com/aaronbloomfield/pdr repository
 **********************************************/

/** This function will read in a grid file, as per the format in the
 * CS 2150 lab 6 document, into a global grid[][] array.  It uses C++
 * file streams, and thus requires the the <fstream> #include header.
 *
 * @return true or false, depending on whether the file was
 *         successfully opened.
 * @param filename The file name to read in -- it's assumed to be in
 *                 the file format described in the lab document.
 * @param rows The number of rows as specified in the input file;
 *             as this is a reference, it is set by the function.
 * @param cols The number of columns as specified in the input file;
 *             as this is a reference, it is set by the function.
 */
bool readInGrid(string filename, int& rows, int& cols) {
    // try to open the file
    ifstream file(filename);
    // upon an error, return false
    if (!file.is_open()) {
        return false;
    }

    // first comes the number of rows
    file >> rows;

    // then the columns
    file >> cols;

    // and finally the grid itself
    string data;
    file >> data;

    // close the file
    file.close();

    // convert the string read in to the 2-D grid format into the
    // grid[][] array.
    // In the process, we'll print the grid to the screen as well.
    int pos = 0; // the current position in the input data
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c] = data[pos++];
        }
    }
    return true;
}

/** This function will retrieve a word in a grid of letters in a given
 * direction.  If the end of the grid is encountered before the length
 * of the desired string is reached, then a shorter string will be
 * returned.  The data is retrieved from a global char grid[][]
 * array, which is assumed to be defined (and in scope).  NOTE: The
 * return value is a static string variable (for efficiency
 * reasons), so a successive return value will overwrite a previous
 * return value.
 *
 * @return A STATIC string containing the letters in the provided direction.
 * @param startRow The starting (row,col) position to find the word.
 * @param startCol The starting (row,col) position to find the word.
 * @param dir The direction to move: 0 is north (upwards), 1 is
 *            northeast, and it rotates around clockwise until it
 *            reaches 7 for northwest.
 * @param len The desired length of the string to return (assuming
 *            the edge of the grid is not reached--if the edge of the
 *            grid is reached, it will return as many characters as
 *            possible up to the edge of the grid, so the returned
 *            string may not have the same length as this parameter
 *            indicates).
 * @param numRows The number of rows in the global char grid[][]
 *                array.
 * @param numCols The number of columns in the global char grid[][]
 *                array.
 */
string getWordInGrid (int startRow, int startCol, int dir, int len,
                      int numRows, int numCols) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocation.  It also prevents it
    // from being deallocated between invocations.  It's probably not
    // good programming practice, but it's an efficient means to return
    // a value.
    static string output;
    output.clear(); // Since it's static we need to clear it
    output.reserve(256); // Can't set capacity in the constructor so do it the first time here

    // the position in the output array, the current row, and the
    // current column
    int r = startRow, c = startCol;
    // iterate once for each character in the output
    for (int i = 0; i < len; i++) {
        // if the current row or column is out of bounds, then break
        if (c >= numCols || r >= numRows || r < 0 || c < 0) {
            break;
        }

        // set the next character in the output array to the next letter
        // in the grid
        output += grid[r][c];

        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }

    return output;
};