#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
/*
Build a symbol table for symbols and their values
using an array of objects

Read in symbols from a text file

Count lines

Ignore comments and loop labels

Assign memory locations starting at 16

*/

#include <string>

#include "Entry.h"

class Symbol_Table {
  public:
    // Constructor with input capacity
    Symbol_Table(int capacity);

    // Destructor
    ~Symbol_Table();

    // Calculate position in table for an entry using its key
    int hashFunction(Symbol_Table* e, std::string key);

    // Insert entry into table
    void insert(Symbol_Table* e, std::string key, int value);

    // Delete entry using key from table
    void delete(Symbol_Table* e, std::string key);

    // Return a value by searching with a key
    int search(Symbol_Table* e, std::string key);

  private:
    int entryCount_; // Number of entries

    int capacity_; // Maximum capacity of table

    Entry** map_; // Pointer to a pointer to the base entry in the hash map
};

#endif
