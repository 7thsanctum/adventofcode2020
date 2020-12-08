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

std::vector<std::string> prev_nodes;
bool explore_nodes(std::map<std::string, std::vector<std::string>> bag_map,
                   std::string bag_name) {
  bool can_contain_gold = false;

  if (bag_name == "shiny gold") {
    return true;
  }

  prev_nodes.push_back(bag_name);

  for (auto b : bag_map[bag_name]) {
    if (std::find(prev_nodes.begin(), prev_nodes.end(), b) !=
        prev_nodes.end()) {
      // skip this node since we are already exploring it
    } else if (explore_nodes(bag_map, b)) {
      return true;
    }
  }

  return can_contain_gold;
}

int explore_node_caps(
    std::map<std::string, std::vector<std::string>> bag_map,
    std::map<std::string, std::vector<std::pair<std::string, int>>> bag_cap_map,
    std::string bag_name) {
  int cap = 1;

  prev_nodes.push_back(bag_name);

  for (auto b : bag_map[bag_name]) {
    if (std::find(prev_nodes.begin(), prev_nodes.end(), b) !=
        prev_nodes.end()) {
      // skip this node since we are already exploring it
    } else {
      int multiplier = 1;
      for (auto caps : bag_cap_map[bag_name]) {
        if (caps.first == b) {
          multiplier = caps.second;
        }
      }
      cap += explore_node_caps(bag_map, bag_cap_map, b) * multiplier;
    }
  }

  return cap;
}

int test_1(std::vector<std::string> data) {
  std::map<std::string, std::vector<std::string>> bag_map;
  std::map<std::string, std::vector<std::pair<std::string, int>>> bag_cap_map;

  for (auto l : data) {
    auto words = split(l, ' ');
    std::string parent_bag;
    std::string bag_name;
    bool parent = true;
    int cap = 0;
    for (auto w : words) {
      if (w == "contain") {
        parent = false;
      } else if (std::regex_match(w, std::regex("[0-9]"))) {
        cap += std::stoi(w);
      } else if (std::regex_match(w, std::regex("bag[s,.]{0,2}"))) {
        // std::cout << bag_name;
        bag_name.erase(0, 1);
        bag_map[bag_name];
        if (parent) {
          parent_bag = bag_name;
        } else {
          bag_map[parent_bag].push_back(bag_name);
          bag_cap_map[parent_bag].push_back(std::make_pair(bag_name, cap));
          cap = 0;
        }
        bag_name.clear();
      } else {
        bag_name += " " + w;
      }
    }
  }
  int gold_count = 0;
  int gold_bag_cap = 0;
  for (auto p : bag_map) {
    // std::cout << p.first << " " << bag_cap_map[p.first] << std::endl;
    prev_nodes.push_back(p.first);
    if (p.first == "shiny gold") {
      gold_bag_cap = explore_node_caps(bag_map, bag_cap_map, p.first);
    } else if (explore_nodes(bag_map, p.first)) {
      gold_count++;
    }
    prev_nodes.clear();
  }

  std::cout << "Gold Cap : " << gold_bag_cap << std::endl;
  return gold_count;
}

int part_1(std::vector<std::string> data) { return test_1(data); }

int part_2(std::vector<std::string> data) { return test_1(data); }

void main() {
  std::vector<std::string> test;
  std::vector<std::string> data;
  read_input("test.txt", test);
  read_input("input.txt", data);

  std::cout << "test : " << test_1(test) << std::endl;
  std::cout << "part_1 : " << part_1(data) << std::endl;
  // std::cout << "part_2 : " << part_2(data) << std::endl;
}