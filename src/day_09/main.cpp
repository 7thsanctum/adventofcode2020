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
int test_1(std::vector<std::string> data, int preamble) {
  int answer = -1;
  for (size_t i = preamble; i < data.size() - 1; i++) {
    bool valid = false;
    for (size_t x = i - preamble; x < i; x++) {
      for (size_t y = i - preamble; y < i; y++) {
        auto combined =
            std::to_string(std::stoll(data[x]) + std::stoll(data[y]));
        if (combined == data[i]) {
          valid = true;
        }
      }
    }
    if (!valid) {
      answer = std::stoi(data[i]);
    }
  }

  return answer;
}

int part_2(std::vector<std::string> data,
                                     int target) {
  std::pair<size_t, size_t> range = std::make_pair(0, 0);

  // the target value is `target`
  std::cout << "looking for : " << target << std::endl;

  // consider each value as a starting point
  for (size_t i = 0; i < data.size() - 1; i++) {
    long long total = std::stoll(data[i]);
    // for each of the next values, sum and see if it meets the criteria
    for (size_t j = i + 1; j < data.size() - 1; j++) {
      total += std::stoll(data[j]);
      // if the value is too big, discard and move on to the next item.
      if (total > target) {
        break;
      } else if (total == target) {
        // if we found a match, note the range
        std::cout << "range " << i << ", " << j << std::endl;
        range.first = i;
        range.second = j;
        break;
      }
    }
  }

  auto small_1 = std::stoll(data[range.first]);
  auto large_1 = std::stoll(data[range.second]);

  // now we look for the biggest and smallest number in the previously
  // identified range
  for (size_t i = range.first; i <= range.second; i++) {
    auto val = std::stoll(data[i]);
    if (val > large_1) {
      large_1 = val;
    }
    if (val < small_1) {
      small_1 = val;
    }
  }

  // return_vals.first = small_1;
  // return_vals.second = large_1;

  return small_1 + large_1;
}

int part_1(std::vector<std::string> data) { return test_1(data, 25); }

void main() {
  std::vector<std::string> test;
  std::vector<std::string> data;
  read_input("test.txt", test);
  read_input("input.txt", data);

  int tp1 = test_1(test, 5);
  // std::cout << "test : " << tp1 << std::endl;
  auto tp2 = part_2(test, tp1);
  std::cout << "test_1 : " << tp1 << std::endl;
  std::cout << "test_2 : " << tp2 << std::endl;

  int part1 = part_1(data);
  auto part2 = part_2(data, part1);
  // long long part2 = p2_range.first + p2_range.second;
  std::cout << "part_1 : " << part1 << std::endl;
  std::cout << "part_2 : " << part2 << std::endl;
}