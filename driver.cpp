#include <algorithm>
#include <bitset>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#include "Symbol_Table.h"

// Uses string s to set computation bits in bitset b
std::bitset<16> setComputationBits(std::bitset<16> b, std::string s) {
  // If computation is 0...
  if (s == "0") {b.set(7).set(9).set(11);}
  // If computation is 1...
  else if (s == "1") {b.set(6).set(7).set(8).set(9).set(10).set(11);}
  // If computation is -1...
  else if (s == "-1") {b.set(7).set(9).set(10).set(11);}
  // If computation is D...
  else if (s == "D") {b.set(8).set(9);}
  // If computation is A or M...
  else if (s == "A" || s == "M") {b.set(10).set(11);}
  // If computation is !D...
  else if (s == "!D") {b.set(6).set(8).set(9);}
  // If computation is !A or !M...
  else if (s == "!A" || s == "!M") {b.set(6).set(10).set(11);}
  // If computation is -D...
  else if (s == "D") {b.set(6).set(7).set(8).set(9);}
  // If computation is -A or -M...
  else if (s == "-A" || s == "-M") {b.set(6).set(7).set(10).set(11);}
  // If computation is D+1...
  else if (s == "D+1") {b.set(6).set(7).set(8).set(9).set(10);}
  // If computation is A+1 or M+1...
  else if (s == "A+1" || s == "M+1") {b.set(6).set(7).set(8).set(10).set(11);}
  // If computation is D-1...
  else if (s == "D-1") {b.set(7).set(8).set(9);}
  // If computation is A-1 or M-1...
  else if (s == "A-1" || s == "M-1") {b.set(7).set(10).set(11);}
  // If computation is D+A or D+M...
  else if (s == "D+A" || s == "D+M") {b.set(7);}
  // If computation is D-A or D-M...
  else if (s == "D-A" || s == "D-M") {b.set(6).set(7).set(10);}
  // If computation is A-D or M-D...
  else if (s == "A-D" || s == "M-D") {b.set(6).set(7).set(8);}
  // If computation is D&A or D&M...
  else if (s == "D&A" || s == "D&M") {;}
  // If computation is D|A or D|M...
  else if (s == "D|A" || s == "D|M") {b.set(6).set(8).set(10);}
  // Else invalid computation
  else {
    std::cerr << "Compute value \"" + s + "\" invalid, exiting program" << std::endl;
    exit(1);
  }

  // If string contains M, set bit 12 (a) = 1
  if (s.find('M') != std::string::npos) {b.set(12);}

  return b; // Return bitset b
}

// Uses string s to set jump bits in bitset b
std::bitset<16> setJumpBits(std::bitset<16> b, std::string s) {
  // If jump is null
  if (s == "null") {}
  // If jump is JGT
  else if (s == "JGT") {b.set(0);}
  // If jump is JEQ
  else if (s == "JEQ") {b.set(1);}
  // If jump is JGE
  else if (s == "JGE") {b.set(0).set(1);}
  // If jump is JLT
  else if (s == "JLT") {b.set(2);}
  // If jump is JNE
  else if (s == "JNE") {b.set(0).set(2);}
  // If jump is JLE
  else if (s == "JLE") {b.set(1).set(2);}
  // If jump is JMP
  else if (s == "JMP") {b.set(0).set(1).set(2);}
  // Else invalid jump
  else {
    std::cerr << "Jump value \"" + s + "\" invalid, exiting program" << std::endl;
    exit(1);
  }

  return b; // Return bitset b
}

// Uses string s to set destination bits in bitset b
std::bitset<16> setDestinationBits(std::bitset<16> b, std::string s) {
  // If destination is null
  if (s == "null") {}
  // If destination is M
  else if (s == "M") {b.set(3);}
  // If destination is D
  else if (s == "D") {b.set(4);}
  // If destination is MD
  else if (s == "MD") {b.set(3).set(4);}
  // If destination is A
  else if (s == "A") {b.set(5);}
  // If destination is AM
  else if (s == "AM") {b.set(3).set(5);}
  // If destination is AD
  else if (s == "AD") {b.set(4).set(5);}
  // If destination is AMD
  else if (s == "AMD") {b.set(3).set(4).set(5);}
  // Else invalid destination
  else {
    std::cerr << "Destination value \"" + s + "\" invalid, exiting program" << std::endl;
    exit(1);
  }

  return b; // Return bitset b
}

// Reads symbols from input file into symbol table
void readFileToTable(Symbol_Table& table, std::string fileName) {
  // Open the input and output file
  std::ifstream file(fileName);

  // Check if input file is open
  if(!file.is_open()) {
    // Return error if fail
    std::cerr << "Unable to open file" << std::endl;
    exit(1);
  }

  size_t linecount = 0; // Stores the number of countable lines

  std::string line = ""; // Stores a line of text from the input file

  // Loop through each line in file and store it in line
  while (std::getline(file, line)) {
    // Remove all whitespace from line
    line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

    // If line is empty...
    if (line.empty()) {
      continue; // Skip to next line (do not increase linecount)
    }

    // If line begins with "//"...
    if (line.size() >= 2 && line[0] == '/' && line[1] == '/') {
      continue; // Skip to next line (do not increase linecount)
    }

    // Stores the position of the "//" substring
    size_t pos = line.find("//");

    // If "//" was found in the line...
    if (pos != std::string::npos) {
      line = line.substr(0,pos); // Get substring of everything before "//"
    }

    // If line begins and ends with parentheses...
    if (line.front() == '(' && line.back() == ')') {
      std::string label = line.substr(1, line.size() - 2); // Store the text inside the parentheses
      table.insert(label, static_cast<int>(linecount)); // Insert label into table with value as the line it refers to
      continue; // Skip to next line (do not increase linecount)
    }

   // If line begins with an @ symbol...
  if (line.front() == '@' ) {
      std::string symbol = line.substr(1); // Store the string following the @ symbol

      // If symbol is a number (begins with a digit)...
      if (std::isdigit(symbol[0])) {}
      // If symbol is a symbol (begins with a lowercase letter)
      else if(std::islower(symbol[0])) {
        table.insert(symbol);
      }
      // Else symbol is a label
      else {}
    }

    linecount++; // Increment line counter
  }

  // Close file
  file.close();
}

// Converts input file into binary hack code
void readFileToBinary(Symbol_Table& table, std::string fileName) {
  // Open the input and output file
  std::ifstream file(fileName);
  std::ofstream outFile("out.txt");

  // Check if input and output file are open
  if(!(file.is_open() && outFile.is_open())) {
    // Return error if fail
    std::cerr << "Unable to open file" << std::endl;
    exit(1);
  }

  size_t linecount = 0; // Stores the number of countable lines

  std::string line = ""; // Stores a line of text from the input file

  // Loop through each line in file and store it in line
  while (std::getline(file, line)) {
    // Remove all whitespace from line
    line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

    // If line is empty...
    if (line.empty()) {
      continue; // Skip to next line (do not increase linecount)
    }

    // If line begins with "//"...
    if (line.size() >= 2 && line[0] == '/' && line[1] == '/') {
      continue; // Skip to next line (do not increase linecount)
    }

    // Stores the position of the "//" substring
    size_t pos = line.find("//");

    // If "//" was found in the line...
    if (pos != std::string::npos) {
      line = line.substr(0,pos); // Get substring of everything before "//"
    }

    // If line begins and ends with parentheses...
    if (line.front() == '(' && line.back() == ')') {
      continue; // Skip to next line (do not increase linecount)
    }

    std::bitset<16> binary; // Declare bitset for binary representation

    // If line begins with an @ symbol...
    if (line.front() == '@' ) {
      std::string symbol = line.substr(1); // Store the string following the @ symbol

      // If address is a number (begins with a digit)...
      if (std::isdigit(symbol[0])) {
        binary = std::bitset<16> (std::stoi(symbol)); // Convert decimal number to binary

        outFile << binary; // Write binary to output file
      }
      // Else address is a symbol
      else {
        int address = table.search(symbol); // Search for symbol's address from hash table and store it

        // If symbol is not found (search returned -1)...
        if (address == -1) {
          // Return error
          std::cerr << "Symbol \"" << symbol << "\" cannot be found in the table" << std::endl;
          exit(1);
        }

        binary = std::bitset<16>(address); // Convert decimal address to binary

        outFile << binary; // Write binary to output file
      }
    }
    // Else line is a c-instruction...
    else {
      binary.set(13).set(14).set(15); // Set bits 13-15 for c-instruction

      size_t scPos = line.find(';'); // Store position of semicolon if found

      size_t eqPos = line.find('='); // Store position of equals sign if found

      // If line contains ';'...
      if (scPos != std::string::npos) {
        std::string before = line.substr(0, scPos); // Substring before ";"

        std::string after = line.substr(scPos + 1); // Substring after ";"

        binary = setComputationBits(binary, before); // Set computation bits in bitset using the string before ";"

        binary = setJumpBits(binary, after); // Set jump bits in bitset using the string after ";"

        outFile << binary; // Write binary to output file
      }

      // If line contains '='...
      else if (eqPos != std::string::npos) {
        std::string before = line.substr(0, eqPos); // Substring before "="

        std::string after = line.substr(eqPos + 1); // Substring after "="

        binary = setDestinationBits(binary, before); // Set destination bits in bitset using the string before "="

        binary = setComputationBits(binary, after); // Set computation bits in bitset using the string after "="

        outFile << binary; // Write binary to output file
      }
    }

    // If input file has a next line, then go to next line in output file
    if (file.peek() != EOF) {outFile << std::endl;}

    linecount++; // Increment line counter
  }

  // Close files
  file.close();
  outFile.close();
}

int main () {
  std::string inputFile = "assembly.txt";

  Symbol_Table assemblyTable(50); // Initialize hash table

  readFileToTable(assemblyTable, inputFile); // Input text file lines into hash table for symbols

  readFileToBinary(assemblyTable, inputFile); // Generate binary output file

  assemblyTable.printTable();

  return 0;
}
