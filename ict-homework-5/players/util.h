#ifndef SEA_BATTLE_UTIL_H
#define SEA_BATTLE_UTIL_H
#pragma once

#include <regex>

static bool checkCoordinatesString(std::string s) {
  if (s.length() < 2) {return false;};
  const std::regex check_regex("^\\d[0]?[A-Z]");
  return std::regex_match(s, check_regex);
}

const int A_LETTER = 65;

static std::string convertCoordsToHuman(int x, int y) {
  std::string r = "";
  r += std::to_string(x+1);
  r += (char)(A_LETTER + (y));
  return r;
}

static std::pair<int, int> convertCoordsToIntpair(std::string s) {
  int a; int b;

  if (s.length() == 3) {
    a = std::stoi(s.substr(0, 2));
    b = int(s.at(2)) - A_LETTER;
  }
  else {
    a = s.at(0) - '0';
    b = int(s.at(1)) - A_LETTER;
  }

  return std::pair<int, int>(a - 1, b);
}
#endif // SEA_BATTLE_UTIL_H
