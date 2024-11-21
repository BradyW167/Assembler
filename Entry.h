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
    Entry(std::string symbol, int value);

    ~Entry();

    inline void setSymbol(std::string symbol) {symbol_ = symbol;}

    inline void setValue(int value) {value_ = value;}

    inline void setNext(Entry* next) {next_ = next;}

    inline std::string getSymbol() {return symbol_;}

    inline int getSymbol() {return value_;}

    inline int getNext() {return next_;}

  private:
    std::string symbol_; // Stores the symbol

    int value_; // Stores the symbol value

    Entry* next_; // Stores pointer to next entry
};

#endif
