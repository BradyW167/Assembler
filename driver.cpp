#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Symbol_Table.h"

int main() {
  // Open the file
    std::ifstream file("assembly.txt");

  // Check if file opened
  if (!file.is_open()) {
    // Return error if fail
    std::cerr << "Unable to open file.\n";
    return 1;
  }

  std::string line = ""; // Stores each line from the input file
  int linecount = 0; // Stores the number of lines
  //
  // Loop through each line in file, storing it in line
  while (std::getline(file, line)) {
    // Remove all whitespace from line
    l
    ine.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

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
      continue; // Skip to next line (do not increase linecount)
    }

    linecount++; // Increment line counter
    std::cout << line << std::endl; // Print out the line
  }



  std::cout << "Linecount: " << linecount << std::endl;

  // Close file
  file.close();

  return 0;
}
