#include "players/human-player.h"

#include <regex>
#include <string>
#include "players/util.h"

std::pair<int, int> human_player_t::make_move(const field_t &my_field, const field_t &enemy_field) {
  output_stream << "Your field:" << std::endl;
  output_stream << my_field << std::endl;
  output_stream << "Enemy's field" << std::endl;
  output_stream << enemy_field << std::endl;
  output_stream << "Input you turn! [Example 1A or 10B or 6J]" << std::endl;

  std::pair<int, int> coords {0, 0};
  std::string s;
  while (true) {
    std::getline(input_stream, s);
    if (!checkCoordinatesString(s)) {
      output_stream << "Incorrect move! [Correct example 1A or 10B or 6J]" << std::endl;
      continue;
    }

    coords = convertCoordsToIntpair(s);
    if (!field_t::is_cell_valid(coords.first, coords.second)) {
      output_stream << "Incorrect move! [Correct example 1A or 10B or 6J]" << std::endl;
      continue;
    }
    break;
  }

  return coords;
  }

void human_player_t::on_incorrect_move(int, int) {
  assert(false);
}

void human_player_t::on_duplicate_move(int x, int y) {
  output_stream << convertCoordsToHuman(x, y) << " DUPLICATE! Repeat move!" << std::endl;
}

void human_player_t::on_miss(int x, int y) {
  output_stream << convertCoordsToHuman(x, y) << " MISS! Enemy's turn!" << std::endl;
}

void human_player_t::on_hit(int x, int y) {
  output_stream << convertCoordsToHuman(x, y) << " HIT! Your next move!" << std::endl;
}

void human_player_t::on_kill(int x, int y) {
  output_stream << convertCoordsToHuman(x, y) << " KILL! Your next move!" << std::endl;
}

void human_player_t::on_win() {
  output_stream << "You WIN!" << std::endl;
}

void human_player_t::on_lose() {
  output_stream << "You LOSE!" << std::endl;
}