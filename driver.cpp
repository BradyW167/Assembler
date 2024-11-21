#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "Symbol_Table.h"

readFileToTable(Symbol_Table table, std::string fileName) {
  // Open the file
  std::ifstream file(fileName);

  // Check if file opened
  if (!file.is_open()) {
    // Return error if fail
    std::cerr << "Unable to open file.\n";
    return 1;
  }

  size_t linecount = 0; // Stores the number of countable lines

  std::string line = ""; // Stores a line of text from the input file

  // Loop through each line in file and store it in line
  while (std::getline(file, line)) {
    // Remove all whitespace from line
    line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

    // If line begins with "//"..
    if(line.size() >= 2 && line[0] == '/' && line[1] == '/') {
      continue; // Skip to next line (do not increase linecount)
    }

    // Stores the position of the "//" substring
    size_t pos = line.find("//");

    // If "//" was found in the line...
    if(pos != std::string::npos) {
      line = line.substr(0,pos); // Get substring of everything before "//"
    }

    // If line begins and ends with parentheses...
    if (line.front() == '(' && line.back() == ')') {
      std::string label = line.substr(1, line.size() - 2); // Store the text inside the parentheses
      std::cout << "Line " << linecount + 1 << " has label: " << label << std::endl;
      table.insert(label, static_cast<int>(linecount + 1)); // Insert label into table with value as the line it refers to
      continue; // Skip to next line (do not increase linecount)
    }

    linecount++; // Increment line counter
    std::cout << line << std::endl; // Print out the line
  }

  std::cout << "Linecount: " << linecount << std::endl;

  file.close();
  
  return 0;
}

int main() {
  Symbol_Table assemblyTable(50); // Initialize hash table

  readFileToTable(assemblyTable, "assembly.txt"); // Input text file lines into hash table for symbols

  assemblyTable.search("LOOP");
  assemblyTable.search("END");

  assemblyTable.printTable(); // Print out table

  return 0;
}
