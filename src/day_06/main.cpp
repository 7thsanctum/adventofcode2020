#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

void read_input(std::string filename, std::vector<std::string>& lines) {
  std::string line;
  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      getline(myfile, line);
      lines.push_back(line);
    }
    myfile.close();
  }
}

int part_1(std::vector<std::string> data) {
  int total_sums = 0;
  int unique_yes = 0;
  std::map<char, int> values;
  for (auto line : data) {
    if (line.size() == 0) {
      total_sums += unique_yes;
      unique_yes = 0;
      values.clear();
    }
    for (auto c : line) {
      if (values[c] == 0) {
        unique_yes++;
      }
      values[c]++;
    }
  }
  return total_sums;
}

int part_2(std::vector<std::string> data) {
  int person_count = 0;
  int all_yes_count = 0;
  std::map<char, int> values;
  for (auto line : data) {
    if (line.size() == 0) {
      for (auto v : values) {
        if (v.second == person_count) {
          all_yes_count++;
        }
      }
      values.clear();
      person_count = 0;
    } else {
      person_count++;
    }
    for (auto c : line) {
      values[c]++;
    }
  }
  return all_yes_count;
}

void main() {
  std::vector<std::string> data;
  read_input("input.txt", data);

  // std::cout << "test : " << test_1(test, false) << std::endl;
  std::cout << "part_1 : " << part_1(data) << std::endl;
  std::cout << "part_2 : " << part_2(data) << std::endl;
}