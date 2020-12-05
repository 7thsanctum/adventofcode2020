#include <array>
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

/*
all valid fields

byr (Birth Year)
iyr (Issue Year)
eyr (Expiration Year)
hgt (Height)
hcl (Hair Color)
ecl (Eye Color)
pid (Passport ID)
cid (Country ID) (optional)
*/

int test_1(std::vector<std::string> data) {
  int valid_passports = 0;
  std::vector<std::string> passport_list;

  // process the data
  std::string passport;
  for (auto line : data) {
    std::cout << line.size() << std::endl;
    if (line.size() > 0) {
      passport += " " + line;
    } else if (line.size() == 0) {
      std::cout << passport << std::endl;
      passport.erase(0, 1);
      // passport.erase(passport.size() - 1);
      passport_list.push_back(passport);
      passport.clear();
    }
  }

  // for each passport
  for (int i = 0; i < passport_list.size(); i++) {
    std::array<std::pair<std::string, int>, 8> fields = {{{"byr", 0},
                                                          {"iyr", 0},
                                                          {"eyr", 0},
                                                          {"hgt", 0},
                                                          {"hcl", 0},
                                                          {"ecl", 0},
                                                          {"pid", 0},
                                                          {"cid", 0}}};
    auto components = split(passport_list[i], ' ');
    std::cout << "passport " << i << std::endl;
    for (auto c : components) {
      std::cout << c << std::endl;
      std::cout << split(c, ':')[0] << std::endl;
      // for (auto j = 0; j < fields.size(); j++) {
      for (auto& f : fields)
        if (f.first == split(c, ':')[0]) {
          f.second++;
        }
    }

    int valid_fields = 0;
    for (auto& f : fields) {
      if (f.second == 1) {
        valid_fields++;
      }
    }
    if (valid_fields == 8) {
      valid_passports++;
    } else if (fields[7].second == 0 && valid_fields == 7) {
      valid_passports++;
    }
  }

  return valid_passports;
}

int part_1(std::vector<std::string> data) { return test_1(data); }

unsigned int part_2(std::vector<std::string> data) { return 0; }

void main() {
  std::vector<std::string> test;
  std::vector<std::string> data;
  read_input("test.txt", test);
  read_input("input.txt", data);

  std::cout << "test : " << test_1(test) << std::endl;
  std::cout << "part_1 : " << part_1(data) << std::endl;
  // std::cout << "part_2 : " << part_2(data) << std::endl;
}