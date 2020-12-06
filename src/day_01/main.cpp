#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int p1_checks = 0;
int p2_checks = 0;

void read_input(std::vector<int> &lines) {
  std::string line;

  std::ifstream myfile("input.txt");
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      getline(myfile, line);
      lines.push_back(stoi(line));
    }
    myfile.close();
  }
}

int part_1(std::vector<int> data) {
  for (size_t i = 0; i < data.size(); i++) {
    for (size_t j = 0; j < data.size(); j++) {
      p1_checks++;
      if (data[i] + data[j] == 2020) {
        return data[i] * data[j];
      } else if (data[i] + data[j] > 2020) {
        break;
      }
    }
  }
  return 0;
}

int part_2(std::vector<int> data) {
  for (size_t i = 0; i < data.size(); i++) {
    for (size_t j = 0; j < data.size(); j++) {
      for (size_t k = 0; k < data.size(); k++) {
        p2_checks++;
        if (data[i] + data[j] + data[k] == 2020) {
          return data[i] * data[j] * data[k];
        } else if (data[i] + data[j] + data[k] > 2020) {
          break;
        }
      }
    }
  }
  return 0;
}

void main() {
  std::vector<int> data;
  read_input(data);

  // Sort the data so we can parse it a bit faster.
  std::sort(data.begin(), data.end());

  std::cout << "part_1 : " << part_1(data) << std::endl;
  std::cout << "part_2 : " << part_2(data) << std::endl;

  std::cout << "part_1 found in : " << p1_checks << std::endl;
  std::cout << "part_2 found in : " << p2_checks << std::endl;
}