#include <array>
#include <algorithm>
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

/*
all valid fields

byr (Birth Year) - four digits; at least 1920 and at most 2002.
iyr (Issue Year) - four digits; at least 2010 and at most 2020.
eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
hgt (Height) - a number followed by either cm or in:
If cm, the number must be at least 150 and at most 193.
If in, the number must be at least 59 and at most 76.
hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
pid (Passport ID) - a nine-digit number, including leading zeroes.
cid (Country ID) - ignored, missing or not.

*/

bool validate_field(std::string field, std::string value) {
  try {
    if(field == "byr") {
      // four digits; at least 1920 and at most 2002.
      int val = stoi(value);
      if(val < 1920 || val > 2002) {
        return false;
      }
      return true;
    }
    else if(field == "iyr") {
      // four digits; at least 2010 and at most 2020
      int val = stoi(value);
      if(val < 2010 || val > 2020) {
        return false;
      }
      return true;
    }
    else if(field == "eyr") {
      // four digits; at least 2020 and at most 2030.
      int val = stoi(value);
      if(val < 2020 || val > 2030) {
        return false;
      }
      return true;
    }
    else if(field == "hgt") {
      // a number followed by either cm or in:
      // If cm, the number must be at least 150 and at most 193.
      // If in, the number must be at least 59 and at most 76.
      if (std::regex_match (value, std::regex("[0-9]{3}cm"))) {
        std::string sub = value.substr (0,3);
        int val = stoi(sub);
        if(val < 150 || val > 193) {
          return false;
        }

        return true;
      }
      else if (std::regex_match (value, std::regex("[0-9]{2}in"))) {
        std::string sub = value.substr (0,2);
        int val = stoi(sub);
        if(val < 59 || val > 76) {
          return false;
        }
        return true;
      }
    }
    else if(field == "hcl") {
      // a # followed by exactly six characters 0-9 or a-f.
      if (std::regex_match (value, std::regex("#[0-9a-f]{6}") )) {
        return true;
      }
    }
    else if(field == "ecl") {
      // exactly one of: amb blu brn gry grn hzl oth.
      if (std::regex_match (value, std::regex("amb|blu|brn|gry|grn|hzl|oth"))) {
        return true;
      }
    }
    else if(field == "pid") {
      // a nine-digit number, including leading zeroes.
      if (std::regex_match (value, std::regex("[0-9]{9}") )) {
        return true;
      }
    }
    else if(field == "cid") {
      // ignored, missing or not.
      return true;
    }
  }
  catch(std::exception& e){
    return false;
  }
  return false;
}

int test_1(std::vector<std::string> data, bool validate_input) {
  int valid_passports = 0;
  std::vector<std::string> passport_list;

  // process the data
  std::string passport;
  for (auto line : data) {
    if (line.size() > 0) {
      passport += " " + line;
    } else if (line.size() == 0) {
      passport.erase(0, 1);
      passport_list.push_back(passport);
      passport.clear();
    }
  }

  // for each passport
  for (size_t i = 0; i < passport_list.size(); i++) {
    // track the number of times each field appears
    std::array<std::pair<std::string, int>, 8> fields = {{{"byr", 0},
                                                          {"iyr", 0},
                                                          {"eyr", 0},
                                                          {"hgt", 0},
                                                          {"hcl", 0},
                                                          {"ecl", 0},
                                                          {"pid", 0},
                                                          {"cid", 0}}};
    auto components = split(passport_list[i], ' ');
    for (auto c : components) {
      for (auto& f : fields) {
        if (f.first == split(c, ':')[0]) {
          if(validate_input) {
            if(validate_field(split(c, ':')[0], split(c, ':')[1])) {
              f.second++;
            }
          }
          else {
            f.second++;
          }          
        }
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

int part_1(std::vector<std::string> data) { return test_1(data, false); }

int part_2(std::vector<std::string> data) {return test_1(data, true); }

void main() {
  std::vector<std::string> test;
  std::vector<std::string> data;
  read_input("test.txt", test);
  read_input("input.txt", data);

  std::cout << "test : " << test_1(test, false) << std::endl;
  std::cout << "part_1 : " << part_1(data) << std::endl;
  std::cout << "part_2 : " << part_2(data) << std::endl;
}