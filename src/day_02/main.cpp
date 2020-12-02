#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Password {
  int min;
  int max;
  char letter;
  std::string password;
};

std::vector<std::string> split(const std::string& s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

void read_input(std::vector<Password>& lines) {
  std::string line;
  std::ifstream myfile("./input.txt");
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      getline(myfile, line);
      std::vector<std::string> results = split(line, ' ');

      Password new_password;
      // store min and max
      std::vector<std::string> rules = split(results[0], '-');
      new_password.min = stoi(rules[0]);
      new_password.max = stoi(rules[1]);

      // get char
      new_password.letter = split(results[1], ':')[0][0];

      // get password
      new_password.password = results[2];
      lines.push_back(new_password);
    }
    myfile.close();
  }
}

int part_1(std::vector<Password> data) {
  int valid_passwords = 0;
  // for each password
  for (auto i = 0; i < data.size(); i++) {
    // for each letter in the password
    int occurence = 0;
    for (auto j = 0; j < data[i].password.size(); j++) {
      if (data[i].password[j] == data[i].letter) {
        occurence++;
      }
    }
    if (occurence >= data[i].min && occurence <= data[i].max) {
      valid_passwords++;
    }
  }
  return valid_passwords;
}

int part_2(std::vector<Password> data) {
  int valid_passwords = 0;
  // for each password
  for (auto i = 0; i < data.size(); i++) {
    int index_1 = data[i].min - 1;
    int index_2 = data[i].max - 1;
    if ((data[i].password[index_1] == data[i].letter) !=
        (data[i].password[index_2] == data[i].letter)) {
      valid_passwords++;
    }
  }
  return valid_passwords;
}

void main() {
  std::vector<Password> data;
  read_input(data);

  std::cout << "part_1 : " << part_1(data) << std::endl;
  std::cout << "part_2 : " << part_2(data) << std::endl;
}