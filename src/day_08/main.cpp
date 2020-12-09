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
int accumulator = 0;

bool run_instructions(std::vector<std::string> data) {
  std::vector<bool> called(data.size());

  bool repeated = false;
  bool completed = false;
  int i = 0;
  while ((!repeated == !completed) || i >= data.size()) {
    // std::cout << data[i] << std::endl;
    auto instruct = split(data[i], ' ');
    auto command = instruct[0];
    char symbol = instruct[1][0];
    int value = std::stoi(instruct[1].substr(1));

    if (called[i]) {
      repeated = true;
      return false;
    } else {
      called[i] = true;
      if (command == "acc") {
        if (symbol == '+') {
          accumulator += value;
        } else if (symbol == '-') {
          accumulator -= value;
        }
        i++;
      } else if (command == "jmp") {
        if (symbol == '+') {
          i += value;
        } else if (symbol == '-') {
          i -= value;
        }
      } else {
        i++;
      }
    }
    if (i == data.size() - 1) {
      completed == true;
      return true;
    } else if (i < 0 || i >= data.size()) {
      repeated = true;
      return false;
    }
  }
  return completed;
}

int test_1(std::vector<std::string> data) {
  run_instructions(data);
  int return_val = accumulator;
  accumulator = 0;
  return return_val;
}

int part_1(std::vector<std::string> data) { return test_1(data); }

int part_2(std::vector<std::string> data) {
  for (size_t i = 0; i < data.size(); i++) {
    std::vector<std::string> new_data = data;
    // deconstruct command
    auto instruct = split(data[i], ' ');
    auto command = instruct[0];
    char symbol = instruct[1][0];
    int value = std::stoi(instruct[1].substr(1));

    bool change = false;
    std::string cmd;
    if (command == "nop") {
      cmd = "jmp " + instruct[1];
      change = true;
    } else if (command == "jmp") {
      cmd = "nop " + instruct[1];
      change = true;
    }
    if (change) {
      // std::cout << cmd << std::endl;
      new_data[i] = cmd;

      if (run_instructions(new_data)) {
        return accumulator;
      } else {
        accumulator = 0;
      }
    }
  }
  return -1;
}

void main() {
  std::vector<std::string> test;
  std::vector<std::string> data;
  read_input("test.txt", test);
  read_input("input.txt", data);

  std::cout << "test : " << test_1(test) << std::endl;
  std::cout << "part_1 : " << part_1(data) << std::endl;
  std::cout << "part_2 : " << part_2(data) << std::endl;
}