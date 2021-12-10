#include "board.h"
#include <iostream>
#include <vector>
using std::vector;

Board::Board()
    : height{18}, width{11}, isAlive{false}, score{0}, highScore{0},
      currentBlock{nullptr}, nextBlock{nullptr}, level{0}, isBlind{false},
      isHeavy{false}, isForce{false} {
  for (int i = 0; i < height; ++i) {
    vector<Cell> row;
    for (int j = 0; j < width; ++j) {
      row.emplace_back(Cell(i, j));
    }
    board.emplace_back(row);
  }
}

Board::~Board() {
  delete currentBlock;
  delete nextBlock;
  delete currentLevel;

  for (int i = 0; i < height; ++i) {
    board[i].clear();
  }
  board.clear();
}

int Board::getHeight() {
  return height;
}

void Board::restBlock(const int level) {
  // need implementation of specific blocks to drop
}