#include "Symbol_Table.h"

Symbol_Table::Symbol_Table(size_t capacity) : table_(capacity), entryCount_(0), symbolAddressCount_(0) {
  buildTable();
}

Symbol_Table::~Symbol_Table() {}

void Symbol_Table::buildTable() {
  insert("R0", 0);
  insert("R1", 1);
  insert("R2", 2);
  insert("R3", 3);
  insert("R4", 4);
  insert("R5", 5);
  insert("R6", 6);
  insert("R7", 7);
  insert("R8", 8);
  insert("R9", 9);
  insert("R10", 10);
  insert("R11", 11);
  insert("R12", 12);
  insert("R13", 13);
  insert("R14", 14);
  insert("R15", 15);
  insert("SP", 0);
  insert("LCL", 1);
  insert("ARG", 2);
  insert("THIS", 3);
  insert("THAT", 4);
  insert("SCREEN", 16384);
  insert("KBD", 24576);
}

// Hash function from https://www.geeksforgeeks.org/implementation-of-hash-table-in-c-using-separate-chaining/
size_t Symbol_Table::hashFunction(const std::string& key) {
  size_t bucketIndex = 0; // Stores position in table for this key to be placed

  size_t sum = 0; // Stores the sum of each character run through the prime multiplication

  size_t factor = 31; // Stores the value of our prime number raised to x

  for(size_t i = 0; i < key.size(); i++) {
      // Get bit value for character at index of key string
      size_t charBitValue = static_cast<size_t>(key[i]);
      // sum = sum + (ascii value of char * (primeNumber ^ x))...
      // where x = 1, 2, 3....n
      sum = ((sum % table_.size()) + (charBitValue * factor) % table_.size()) % table_.size();

      // factor = factor * prime number....(prime number) ^ x
      // prime numbers apparently spread keys out more evenly
      factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
  }

  bucketIndex = sum; // Store the calculated sum as the index value for this keys

  return bucketIndex; // Return the index value
}

void Symbol_Table::insert(const std::string& key) {
  size_t bucketIndex = hashFunction(key); // Get bucket index for given key

  if(duplicateCheck(key, bucketIndex)) {return;} // Check if given key is a duplicate and return if so

  int value = symbolAddressCount_ + 15; // Set symbol addresses to some value over 15

  symbolAddressCount_++; // Increment symbol address count

  std::cout << "\nInserting key-value pair ('" << key << "' : " << value << ") at index " << bucketIndex << std::endl;

  Entry newEntry(key, value); // Create new entry with given key and value

  table_[bucketIndex].push_back(newEntry); // Insert entry into list at index
}

void Symbol_Table::insert(const std::string& key, int value) {
  size_t bucketIndex = hashFunction(key); // Get bucket index for given key

  if(duplicateCheck(key, bucketIndex)) {return;} // Check if given key is a duplicate and return if so

  std::cout << "\nInserting key-value pair ('" << key << "' : " << value << ") at index " << bucketIndex << std::endl;

  Entry newEntry(key, value); // Create new entry with given key and value

  table_[bucketIndex].push_back(newEntry); // Insert entry into list at index
}

bool Symbol_Table::duplicateCheck(const std::string& key, size_t bucketIndex) {
  // Loop through table entries
  for (const Entry& existingEntry : table_[bucketIndex]) {
    // If entry matches given key...
    if (existingEntry.getSymbol() == key) {
        return true;
    }
  }
  return false; // Return false if matching key not found
}

void Symbol_Table::deleteEntry(const std::string& key) {
  int bucketIndex = hashFunction(key); // Get bucket index for given key

  auto& list = table_[bucketIndex]; // Get reference to the list at bucketIndex

  // If list is empty...
  if(list.empty()) {
    std::cout << "List empty at index " << bucketIndex << ", Entry with key " << key << " could not be deleted" << std::endl;
    return; // Skip to next list
  }

  // Iterate through each entry in the list
  for (auto it = list.begin(); it != list.end(); ++it) {
      // If the iterator's current key matches the given key...
      if (it->getSymbol() == key) {
          std::cout << "Deleted: ('" << key << "', " << it->getValue() << ")" << std::endl;

          list.erase(it); // Remove the entry from the list
          return; // Return after the entry is deleted
      }
  }

  std::cout << "Key '" << key << "' not found";  // If key was not found
}

int Symbol_Table::search(const std::string& key) {
  size_t bucketIndex = hashFunction(key); // Get bucket index for given key

  std::cout << "\nSearching for key '" << key << "' at index " << bucketIndex << std::endl;
  auto& list = table_[bucketIndex]; // Get reference to the list at the bucket index

  // Return -1 if list is empty, key not found
  if(list.empty()) {
    std::cout << "List empty" << std::endl;
    return -1;
  }

  // Loop through each entry in the list
  for(const auto& entry : list) {
      // If the iterator's current key matches the given key...
      if (entry.getSymbol() == key) {
          return entry.getValue();  // Return value matching given key
      }
  }

  std::cout << "Key not found" << std::endl;
  return -1;
}

void Symbol_Table::printTable() {
  std::cout << "\nPrinting hash table..." << std::endl;
  // Loop through each index in the table
  for(size_t i = 0; i < table_.size(); ++i) {
    std::cout << "Index " << i << ": "; // Print the index value

    auto& list = table_[i]; // Get reference to the list at index i

    // If list is empty...
    if(list.empty()) {
      std::cout << "List empty" << std::endl;
      continue; // Skip to next list
    }

    // Loop through each entry in the list
    for(const auto& entry : list) {
      // Print key value pair of entry
      std::cout << "(" << entry.getSymbol() << ", " << std::to_string(entry.getValue()) << ") ";
    }
    std::cout << std::endl;
  }
}
