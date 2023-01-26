#pragma once

#include <iostream>
#include <cassert>

#include "players/player-interface.h"
#include "players/util.h"

class human_player_t : public player_interface_t {
public:
  human_player_t(std::istream &input_stream, std::ostream &output_stream)
      : input_stream(input_stream), output_stream(output_stream) {}

    std::pair<int, int> make_move(const field_t &my_field, const field_t &enemy_field) override;

    void on_incorrect_move(int, int) override;
    void on_duplicate_move(int, int) override;
    void on_miss(int, int) override;
    void on_hit(int, int) override;
    void on_kill(int, int) override;

    void on_win() override;
    void on_lose() override;

private:
  std::istream &input_stream;
  std::ostream &output_stream;
};
