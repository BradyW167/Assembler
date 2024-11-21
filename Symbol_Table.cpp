#include "Symbol_Table.h"

Symbol_Table::Symbol_Table(size_t capacity) : table_(capacity), entryCount_(0){}

Symbol_Table::~Symbol_Table() {}

// Hash function from https://www.geeksforgeeks.org/implementation-of-hash-table-in-c-using-separate-chaining/
size_t Symbol_Table::hashFunction(const std::string& key) {
  size_t bucketIndex = 0; // Stores position in table for this key to be placed

  size_t sum = 0; // Stores the sum of each character run through the prime multiplication

  size_t factor = 31; // Stores the value of our prime number raised to x

  for (size_t i = 0; i < key.size(); i++) {
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

void Symbol_Table::insert(const std::string& key, int value) {
  size_t bucketIndex = hashFunction(key); // Get bucket index for given key

  std::cout << "Inserting key-value pair: '" << key << "' : " << value << " at index " << bucketIndex << std::endl;

  Entry newEntry(key, value); // Create new entry with given key and value

  table_[bucketIndex].push_back(newEntry); // Insert entry into list at index

  std::cout << "Inserted key-value pair: '" << table_[bucketIndex].front().getSymbol() << "' : " << table_[bucketIndex].front().getValue() << " at index " << bucketIndex << std::endl;
}

void Symbol_Table::deleteEntry(const std::string& key) {
  int bucketIndex = hashFunction(key); // Get bucket index for given key

  auto& list = table_[bucketIndex];  // Reference to the list at given index

  // Iterate through each entry in the list
  for (auto it = list.begin(); it != list.end(); ++it) {
      // If the iterator's current key matches the given key...
      if (it->getSymbol() == key) {
          list.erase(it);  // Remove the entry from the list
          std::cout << "Deleted: (" << key << ", " << it->getValue() << ")\n";
          return;  // Exit once the entry is deleted
      }
  }

  std::cout << "Key not found: " << key << "\n";  // If key was not found
}

int Symbol_Table::search(const std::string& key) {
  int bucketIndex = hashFunction(key); // Get bucket index for given key

  std::cout << "Search for key '" << key << "' at index " << bucketIndex << std::endl;
  auto& list = table_[bucketIndex];  // Reference to the list at given index

  std::cout << "Entries at bucket index " << bucketIndex << ": ";
  for (const auto& entry : list) {
    std::cout << entry.getSymbol() << " -> ";
  }

std::cout << std::endl;

  // Iterate through each entry in the list
  for (auto it = list.begin(); it != list.end(); ++it) {
      std::cout << "Key: " << it->getSymbol() << " -> ";
      // If the iterator's current key matches the given key...
      if (it->getSymbol() == key) {
          return it->getValue();  // Return value matching given key
      }
  }

  std::cout << "Key not found" << std::endl;
  return -1;
}

void Symbol_Table::printTable() {
  // Loop through each index in the table
  for (size_t i = 0; i < table_.size(); ++i) {
    // Print the index value
    std::cout << "Index " << i << ": ";

    // Check if the list is empty
    if (table_[i].empty()) {
      std::cout << "Empty list" << std::endl;
      continue; // Skip to next list
    } else {
        // Loop through each entry in the list at index i in table_
        for (auto it = table_[i].begin(); it != table_[i].end(); ++it) {
            // Print the key and its value
            std::cout << "(" << it->getSymbol() << ", " << std::to_string(it->getValue()) << ")";
            // Print "->" if it's not the last element
            if (std::next(it) != table_[i].end()) {
                std::cout << " -> ";
            }
        }
    }

    // Print nullptr at the end of each list (just for formatting)
    std::cout << " -> nullptr" << std::endl;
  }
}
