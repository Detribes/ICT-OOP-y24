#include "game/sea-battle.h"
#include "game/field.h"

sea_battle_t::turn_t sea_battle_t::change_turn(turn_t current_turn) {
  return current_turn == FIRST_PLAYER ? SECOND_PLAYER : FIRST_PLAYER;
}

std::string sea_battle_t::get_player_name(turn_t turn) {
  return turn == FIRST_PLAYER ? "First" : "Second";
}

sea_battle_t::sea_battle_t(std::shared_ptr<player_interface_t> player1, field_t field1, std::shared_ptr<player_interface_t> player2, field_t field2):
      firstPlayer_(player1), firstField_(field1), secondPlayer_(player2), secondField_(field2) {}

field_t sea_battle_t::makeEmptyField(){
  std::vector<std::string> list;
  for (int i = 0; i < field_t::FIELD_SIZE; i++)
  {
    list.push_back(std::string(field_t::FIELD_SIZE, field_t::EMPTY_CELL));
  }

  field_t result = field_t(list);
  return result;
}

bool sea_battle_t::isAllShipsDestroyedOnField(field_t &field) {
  for (int x = 0; x < field_t::FIELD_SIZE; x++) {
    for (int y = 0; y < field_t::FIELD_SIZE; y++) {
      if (field[x][y] == field_t::SHIP_CELL) {
        return false;
      }
    }
  }
  return true;
}

bool sea_battle_t::hasOtherShipCells(field_t &field, std::pair<int, int> coords) {
  const int MAX_SHIP_LEN = 3;
  int delta = 0;
  // scan directions, up to total of 4 (0,1,2,3)
  int scan_dir = 0;
  while (true) {
    if (delta > MAX_SHIP_LEN) {
      delta = 0;
      scan_dir++;
      if (scan_dir >= field_t::DIRECTIONS.size()) {
        // directions exhausted, no ship cells around
        return false;
      }
      // start with new direction
    }

    // multiply by vector of direction
    int x = coords.first + (delta + 1) * field_t::DIRECTIONS[scan_dir].first;
    int y = coords.second + (delta + 1) * field_t::DIRECTIONS[scan_dir].second;
    delta++;
    if (!field_t::is_cell_valid(x, y)) {
      continue;
    }

    auto cell = field[x][y];
    if (cell == field_t::EMPTY_CELL || cell == field_t::MISS_CELL) {
      // force skip to next direction
      delta = 10;
      continue;
    }

    // another ship cell is around, break the loop
    if (cell == field_t::SHIP_CELL) {
      return true;
    }
  }
}
void sea_battle_t::play() {
  turn_t current_turn = turn_t::FIRST_PLAYER;
  std::array<field_t, 2> attacks_field {};
  std::array<field_t, 2> player_field {};
  std::array<player_interface_t*, 2> players;

  // construct empty fields for attack/miss markers
  attacks_field[0] = makeEmptyField();
  attacks_field[1] = makeEmptyField();
  // construct populated fields for game logic
  player_field[0] = firstField_;
  player_field[1] = secondField_;
  // construct players array
  players[0] = firstPlayer_.get();
  players[1] = secondPlayer_.get();

  // run game cycle
  bool game_runs = true;
  while (game_runs) {
    auto player = players[current_turn];
    auto enemy = players[1-current_turn];

    // ask player to make a move
    auto coords = player->make_move(player_field[current_turn], attacks_field[current_turn]);

    // check if given cell is within the game field
    if (!field_t::is_cell_valid(coords.first, coords.second)) {
      // invalid cell coordinates
      player->on_incorrect_move(coords.first, coords.second);
      continue; // continue, same player
    }

    // tile from the enemy field
    char tile = player_field[1-current_turn][coords.first][coords.second];

    if (tile == field_t::HIT_CELL || tile == field_t::MISS_CELL) {
      // in case we hit an already burning cell
      player->on_duplicate_move(coords.first, coords.second);
      continue; // continue, same player
    }
    if (tile == field_t::SHIP_CELL) {
      // in case player hits an enemy cell
      if (hasOtherShipCells(player_field[1-current_turn], coords)) {
        player->on_hit(coords.first, coords.second);
      } else {
        player->on_kill(coords.first, coords.second);
      }
      player_field[1-current_turn][coords.first][coords.second] = field_t::HIT_CELL;
      attacks_field[current_turn][coords.first][coords.second] = field_t::HIT_CELL;

      // check win/lose condition
      if (isAllShipsDestroyedOnField(player_field[1-current_turn])) {
        player->on_win();
        enemy->on_lose();

        game_runs = false;
      }

      continue; // continue, same player
    }
    else if (tile == field_t::EMPTY_CELL) {
      // in case current player missed
      player->on_miss(coords.first, coords.second);
      player_field[1-current_turn][coords.first][coords.second] = field_t::MISS_CELL;
      attacks_field[current_turn][coords.first][coords.second] = field_t::MISS_CELL;
      // pass
    }

    // switch player
    current_turn = change_turn(current_turn);
  }
}