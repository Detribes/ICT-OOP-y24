#include "players/smart-ai-player.h"
#include "players/util.h"

BotScanStatus::BotScanStatus() {
  hit_x = 0;
  hit_y = 0;
  offset = 0;
  scanDir = 0;
  exhausted = true;
}

void BotScanStatus::nextDir() {
  scanDir++;
  offset = 0;
}

void BotScanStatus::resetScan() {
  offset = 0;
  scanDir = 0;
}

smart_ai_player_t::smart_ai_player_t() {
  std::seed_seq seq = {std::chrono::high_resolution_clock::now().time_since_epoch().count()};
  gen_ = std::mt19937_64(seq);
  scanStatus_ = BotScanStatus();
}

std::pair<int, int> smart_ai_player_t::make_move(const field_t &my_field, const field_t &enemy_field) {
  int ax = 0;
  int ay = 0;

  // If we not have yet found a ship cell, pick a random one
  if (scanStatus_.exhausted) {
    auto candidates = getCandidates(enemy_field);

    if (candidates.size() <= 0) {
      std::cout << "candidates = 0, enemy field:\n" << enemy_field << std::endl;
      assert(false);
    }

    return candidates[std::uniform_int_distribution<int>(0, candidates.size() - 1)(gen_)];
  }

  // If found, perform a sequential scan in 4 directions
  while (true) {
    // all possible directions exhausted
    if (scanStatus_.scanDir > field_t::DIRECTIONS.size()) {
      scanStatus_.exhausted = true;
      return make_move(my_field, enemy_field);
    }

    ax = scanStatus_.hit_x + (scanStatus_.offset + 1) * field_t::DIRECTIONS[scanStatus_.scanDir].first;
    ay = scanStatus_.hit_y + (scanStatus_.offset + 1) * field_t::DIRECTIONS[scanStatus_.scanDir].second;
    scanStatus_.offset++;

    // invalid cell or out of largest ship boundaries
    if (!field_t::is_cell_valid(ax, ay) || scanStatus_.offset > 3) {
      scanStatus_.nextDir();
      continue;
    }
    // already attacked this cell
    if (enemy_field[ax][ay] != field_t::EMPTY_CELL) {
      scanStatus_.nextDir();
      continue;
    }
    break;
  }

  return std::pair<int, int>(ax, ay);
}

bool smart_ai_player_t::cellExistsNotHit(int x, int y, const field_t &field) {
  if (field_t::is_cell_valid(x, y)) {
    if (field[x][y] != field_t::HIT_CELL)
      return true;
    else
      return false;
  }

  return true;
}

std::vector<std::pair<int, int>> smart_ai_player_t::getCandidates(const field_t &enemyField) {
  std::vector<std::pair<int, int>> emptyCells;
  int optimizeLimit = 0;
  for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
    for (int j = 0; j < field_t::FIELD_SIZE; ++j) {
      if (enemyField[i][j] == field_t::EMPTY_CELL) {
        // check if neighbor cells were not hit/scanned
        if (cellExistsNotHit(i - 1, j, enemyField) && cellExistsNotHit(i, j + 1, enemyField) &&
            cellExistsNotHit(i + 1, j, enemyField) && cellExistsNotHit(i, j - 1, enemyField)) {

          emptyCells.emplace_back(i, j);
          optimizeLimit++;

          // we don't need too many candidates (c) hr
          if (optimizeLimit > 5)
            return emptyCells;
        }
      }
    }
  }
  return emptyCells;
}

void smart_ai_player_t::on_incorrect_move(int, int) {
  assert(false);
}

void smart_ai_player_t::on_duplicate_move(int x, int y) {
  assert(false);
}

void smart_ai_player_t::on_miss(int x, int y) {
  // switch scan direction
  if (!scanStatus_.exhausted)
    scanStatus_.nextDir();
}

void smart_ai_player_t::on_hit(int x, int y) {
  // if we are not scanning now, remember the hit location and start the scan
  if (scanStatus_.exhausted) {
    scanStatus_.resetScan();
    scanStatus_.hit_x = x;
    scanStatus_.hit_y = y;
    scanStatus_.exhausted = false;
  }
}

void smart_ai_player_t::on_kill(int x, int y) {
  // reset scan process
  scanStatus_.exhausted = true;
}

void smart_ai_player_t::on_win() {
//do nothing
}

void smart_ai_player_t::on_lose() {
  //do nothing
}