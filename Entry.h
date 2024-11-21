#ifndef ENTRY_H
#define ENTRY_H
/*
Build a symbol table for symbols and their values
using an array of objects

Read in symbols from a text file

Count lines

Ignore comments and loop labels

Assign memory locations starting at 16

*/

#include <string>

class Entry {
  public:
    // Constructor with input symbol as key to the input value
    Entry(const std::string& symbol, int value);

    // Destructor
    ~Entry();

    inline void setValue(int value) {value_ = value;}

    inline const std::string getSymbol() const {return symbol_;}

    inline int getValue() const {return value_;}

  private:
    std::string symbol_; // Stores the symbol

    int value_; // Stores the symbol value
};

#endif
