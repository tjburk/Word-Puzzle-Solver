#include "hashTable.h"
#include <iostream>
#include <forward_list>
#include <string>
#include <vector>
using namespace std;

bool checkPrime(unsigned int p);
int getNextPrime(unsigned int n);

hashTable::hashTable(){
  dictionary.resize(tableSize);
  //Initialize pow17array
  for(int i = 0; i < 22; i++){
    pow17Array[i] = pow(17.0, i);
  }
}

hashTable::~hashTable(){
  dictionary.erase(dictionary.begin(), dictionary.end());
}

bool hashTable::contains(forward_list<string> list, string key) const{
  //For each loop to check if the key exists in the list
  for(string s: list){
    if(s == key)
      return true;
  }
  return false;
}

void hashTable::insert(const string& key){
  //cout << "Word to be hashed: " << key << endl;
  int index = hash(key);
  //cout << "Hash value of word: " << index << endl;
  
  dictionary[index].push_front(key);
  itemCount++;

  //Calculate load factor
  double loadFactor = (itemCount * 1.0)/tableSize; //calculate current load factor
  //cout << "Load Factor: " << loadFactor << endl;

  //Rehash if load factor is too high
  if(loadFactor > LOAD_FACTOR){ //If current table has load factor above 0.75
    itemCount = 0;
    rehash();
  }
}

bool hashTable::find(string word) const{
  unsigned int hashVal = hash(word);
  return contains(dictionary[hashVal], word);
}

unsigned int hashTable::hash(string key) const{
  unsigned int hashVal = 0;
  for(int i = 0; i < key.length(); i++){
    hashVal += key[i] * pow17Array[i]; //HASH FUNCTION with POW
  }
  hashVal %= tableSize;
  //cout << "HashVal: " << hashVal << endl;
  return hashVal;
}

void hashTable::rehash(){
  //cout << "Rehashing" << endl;
  
  //Get new table size of next prime
  tableSize = getNextPrime(tableSize*2);

  //Make a temp dict to be the same as dict
  vector<forward_list<string>> tempDict = dictionary;
  
  //Remake dict with new array size and rehash
  dictionary.clear();
  dictionary.resize(tableSize);
  //cout << "New table size: " << dictionary.size() << endl;

  for(int i = 0; i < tempDict.size(); i++){
    while(!tempDict[i].empty()){
      string s = tempDict[i].front();
      tempDict[i].pop_front();
      insert(s);
    }
  }
}

/**********************************************
 * Title: primenumber
 * Author: Aaron Bloomfield
 * Date: 10/16/22 Date Written: 2014
 * Availability: https://github.com/aaronbloomfield/pdr repository
 **********************************************/

bool checkprime(unsigned int p) {
    if ( p <= 1 ) // 0 and 1 are not primes; the are both special cases
        return false;
    if ( p == 2 ) // 2 is prime
        return true;
    if ( p % 2 == 0 ) // even numbers other than 2 are not prime
        return false;
    for ( int i = 3; i*i <= p; i += 2 ) // only go up to the sqrt of p
        if ( p % i == 0 )
            return false;
    return true;
}

int getNextPrime (unsigned int n) {
    while ( !checkprime(++n) );
    return n; // all your primes are belong to us
}