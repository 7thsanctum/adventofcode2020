#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
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

int get_seat_id(std::string seat_code) {
  int row = 1;
  int col = 0;
  int row_l = 0;
  int row_u = 127;
  int col_l = 0;
  int col_u = 7;

  for (size_t i = 0; i < seat_code.size(); i++) {
    // row number
    if (seat_code[i] == 'F') {
      row_u = ((row_l + row_u + 1) / 2) - 1;
    } else if (seat_code[i] == 'B') {
      row_l = ((row_l + row_u + 1) / 2);
    }
    // column number
    if (seat_code[i] == 'R') {
      col_l = ((col_u + col_l + 1) / 2);
    } else if (seat_code[i] == 'L') {
      col_u = ((col_u + col_l + 1) / 2) - 1;
    }
  }
  col = col_l;
  row = row_l;
  return (row * 8) + col;
}

int part_1(std::vector<std::string> data) {
  int highest_id = 0;
  for (auto sc : data) {
    int curr_id = get_seat_id(sc);
    if (curr_id > highest_id) {
      highest_id = curr_id;
    }
  }
  return highest_id;
}

int part_2(std::vector<std::string> data) {
  std::vector<int> ids;
  for (auto sc : data) {
    ids.push_back(get_seat_id(sc));
  }

  for (int i = 1; i < 127; i++) {
    for (int j = 0; j < 8; j++) {
      int seat_id = i * 8 + j;
      if (std::find(ids.begin(), ids.end(), seat_id) == ids.end() &&
          std::find(ids.begin(), ids.end(), seat_id + 1) != ids.end() &&
          std::find(ids.begin(), ids.end(), seat_id - 1) != ids.end()) {
        return seat_id;
      }
    }
  }
  return 0;
}

void main() {
  std::vector<std::string> data;
  read_input("input.txt", data);

  // std::cout << "test : " << test_1(test, false) << std::endl;
  std::cout << "part_1 : " << part_1(data) << std::endl;
  std::cout << "part_2 : " << part_2(data) << std::endl;
}