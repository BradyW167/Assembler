Symbol_Table::Symbol_Table(capacity) : entryCount_(0), capacity_(capacity), map_((Entry**)malloc(sizeof(Entry*) * capacity) {}

Symbol_Table::~Symbol_Table() {}

// Hash function from https://www.geeksforgeeks.org/implementation-of-hash-table-in-c-using-separate-chaining/
int hashFunction(Symbol_Table* table, std::string key) {
  int bucketIndex = 0; // Stores position in table for this key to be placed

  int sum = 0; // Stores the sum of each character run through the prime multiplication

  int factor = 31; // Stores the value of our prime number raised to x

  for (int i = 0; i < key.length(); i++) {
    // Get bit value for character at index of key string
      int charBitValue = static_cast<int>(key[i]);
      // sum = sum + (ascii value of char * (primeNumber ^ x))...
      // where x = 1, 2, 3....n
      sum = ((sum % table->capacity) + (charBitValue * factor) % table->capacity) % table->capacity;

      // factor = factor * prime number....(prime number) ^ x
      // prime numbers apparently spread keys out more evenly
      factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
  }

  bucketIndex = sum; // Store the calculated sum as the index value for this keys

  return bucketIndex;
}

void insert(Symbol_Table* table, std::string key, int value) {
  int bucketIndex = hashFunction(table, key); // Get bucket index for given key

  Entry* newEntry = new Entry(key, value); // Create new entry and a pointer to it with given key and value

  // If no key already exists at generated index...
  if(table->map_[bucketIndex] == nullptr) {
      // Store the new entry at that index in the table
      map->map_[bucketIndex] = newEntry;
  }
  // Else a collision occurred...
  else {
    // Insert the new entry at the head of the linked list
    // by setting the entry it collided with to its next entry
    newEntry->next = table->map_[bucketIndex];
    table->map_[bucketIndex] = newEntry;
  }
}

void delete(Symbol_Table* table, std::string key) {
  int bucketIndex = hashFunction(table, key); // Get bucket index for given key

  Entry* prevEntry = nullptr; // Stores pointer to previous entry

  Entry* currEntry = table->map_[bucketIndex]; // Stores pointer to head of linked list at bucketIndex

  // Loop through linked list from head entry
  while(currEntry != nullptr) {
    // Match found if current entry key is same as given key
    if(key == currEntry->getSymbol()) {
      // If current entry is head node...
      if (currEntry == table->map_[bucketIndex]) {
        // Set the head node to the next node in the linked list
        table->map_[bucketIndex] = currEntry->next;
      }
      // Else current entry is not the head
      else {
        // Store pointer to current entries next node
        prevEntry->next = currEntry->next;
      }
      delete currEntry; // Delete current entry
      break; // Exit while loop
    }
    prevEntry = currEntry; // 
    currEntry = currEntry->next; // 
  }
}

int search(Symbol_Table* table, std::string key);
