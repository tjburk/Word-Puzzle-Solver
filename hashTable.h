#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <forward_list>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class hashTable{
 public:
  hashTable();
  ~hashTable();

  void insert(const string& key);
  unsigned int hash(string key) const;
  void rehash();
  bool contains(forward_list<string> list, string key) const;
  bool find(string word) const;
    
 private:
  double LOAD_FACTOR = 0.75;
  int tableSize = 20011;
  int itemCount;
  vector<forward_list<string>> dictionary;
  unsigned int pow17Array[22]; //All the powers of 17
};

#endif