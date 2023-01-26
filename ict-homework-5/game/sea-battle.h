#pragma once

#include <memory>

#include "game/field.h"
#include "players/player-interface.h"

class sea_battle_t {
public:
  enum turn_t { FIRST_PLAYER = 0, SECOND_PLAYER = 1 };

  sea_battle_t(std::shared_ptr<player_interface_t> player1, field_t field1, std::shared_ptr<player_interface_t> player2,
               field_t field2);

  ~sea_battle_t() = default;

  void play();

  static turn_t change_turn(turn_t current_turn);
  static std::string get_player_name(turn_t turn);

  static bool isAllShipsDestroyedOnField(field_t &field);
  static bool hasOtherShipCells(field_t &field, std::pair<int, int> coords);
  static field_t makeEmptyField();

private:
  std::shared_ptr<player_interface_t> firstPlayer_;
  field_t firstField_;
  std::shared_ptr<player_interface_t> secondPlayer_;
  field_t secondField_;
};