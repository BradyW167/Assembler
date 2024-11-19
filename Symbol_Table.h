#ifndef SYMBOL_H
#define SYMBOL_H
/*
Build a symbol table for symbols and their values
using an array of objects

Read in symbols from a text file

Count lines

Ignore comments and loop labels

Assign memory locations starting at 16

*/
class Symbol_Table {
  public:
    Symbol_Table();

    Symbol_Table(const Symbol_Table &);

    ~Symbol_Table();

  private:
};

#endif
