#include "Entry.h"

Entry::Entry(std::string symbol, int value) : symbol_(symbol), value_(value), next_(nullptr) {}

Entry::~Entry() {

}
