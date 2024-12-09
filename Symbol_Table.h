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

#include <cstddef>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Entry.h"

class Symbol_Table {
  public:
    // Constructor with input capacity
    Symbol_Table(size_t capacity);

    // Destructor
    ~Symbol_Table();

    // Build table with default values
    void buildTable();

    // Calculate position in table for an entry using its key
    size_t hashFunction(const std::string& key);

    // Insert symbol into table and generate value from symbolAddressCount_
    void insert(const std::string& key);

    // Insert entry into table with input value
    void insert(const std::string& key, int value);

    // Check if given key already exists in table
    bool duplicateCheck(const std::string& key, size_t bucketIndex);

    // Delete entry using key from table
    void deleteEntry(const std::string& key);

    // Return a value by searching with a key
    int search(const std::string& key);

    // Print out the table
    void printTable();

  private:
    std::vector<std::list<Entry>> table_; // Vector of Entry lists as a hash table

    size_t entryCount_; // Number of entries

    size_t symbolAddressCount_; // Number of unique symbols in the table
};

#endif
