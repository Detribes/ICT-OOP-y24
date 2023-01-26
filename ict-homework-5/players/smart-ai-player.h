#pragma once

#include <cassert>
#include <chrono>
#include <random>

#include "players/player-interface.h"

struct BotScanStatus
{
  int hit_x;
  int hit_y;
  int offset;
  int scanDir;
  bool exhausted;

  BotScanStatus();
  void nextDir();
  void resetScan();
};

class smart_ai_player_t : public player_interface_t {
public:
  smart_ai_player_t();

  bool cellExistsNotHit(int x, int y, const field_t &field);
  std::vector<std::pair<int, int>> getCandidates(const field_t &enemyField);

  std::pair<int, int> make_move(const field_t &my_field, const field_t &enemy_field) override;

  void on_incorrect_move(int, int) override;
  void on_duplicate_move(int, int) override;
  void on_miss(int, int) override;
  void on_hit(int, int) override;
  void on_kill(int, int) override;

  void on_win() override;
  void on_lose() override;

private:
  std::mt19937_64 gen_;
  BotScanStatus scanStatus_;
};
