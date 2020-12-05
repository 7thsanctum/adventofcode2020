#include <algorithm>
#include <fstream>
#include <iostream>
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

void read_input(std::vector<std::string>& lines) {
  std::string line;
  std::ifstream myfile("input.txt");
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      getline(myfile, line);
      lines.push_back(line);
    }
    myfile.close();
  }
}

int check_slope(std::vector<std::string> data, int along, int down) {
  int tree_count = 0;
  // slope
  size_t offset = 0;
  for (auto i = down; i < data.size(); i += down) {
    auto& line = data[i];
    offset += along;
    if (offset >= line.size()) {
      offset -= line.size();
    }
    // check cell
    if (offset <= line.size()) {
      if (line[offset] == '#' || line[offset] == 'O') {
        line[offset] = 'O';
        tree_count++;
      } else {
        line[offset] = 'X';
      }
    }
  }

  // Debug view
  // for (auto d : data) {
  //   std::cout << d << std::endl;
  // }

  return tree_count;
}

int part_1(std::vector<std::string> data) {
  int p1_slope = check_slope(data, 3, 1);
  std::cout << "p1_slope : " << p1_slope << std::endl;
  return p1_slope;
}

unsigned int part_2(std::vector<std::string> data) {
  /*
Right 1, down 1.
Right 3, down 1. (This is the slope you already checked.)
Right 5, down 1.
Right 7, down 1.
Right 1, down 2.
  */
  int slope_1 = check_slope(data, 1, 1);
  int slope_2 = check_slope(data, 3, 1);
  int slope_3 = check_slope(data, 5, 1);
  int slope_4 = check_slope(data, 7, 1);
  int slope_5 = check_slope(data, 1, 2);
  std::cout << "slope_1 : " << slope_1 << std::endl;
  std::cout << "slope_2 : " << slope_2 << std::endl;
  std::cout << "slope_3 : " << slope_3 << std::endl;
  std::cout << "slope_4 : " << slope_4 << std::endl;
  std::cout << "slope_5 : " << slope_5 << std::endl;
  return slope_1 * slope_2 * slope_3 * slope_4 * slope_5;
}

void main() {
  std::vector<std::string> data;
  read_input(data);

  std::cout << "part_1 : " << part_1(data) << std::endl;
  std::cout << "part_2 : " << part_2(data) << std::endl;
}