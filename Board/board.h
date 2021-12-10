#ifndef __BOARD_H__
#define __BOARD_H__

#include "cell.h"
#include <iostream>
#include <vector>
using std::vector;

//delete class declarations after linking
class Block {};
class AbstractLevel {};

class Board {
  vector<vector<Cell>> board;
  bool isAlive;
  Block *currentBlock;
  Block *nextBlock;
  bool isBlind;
  bool isHeavy;
  bool isForce;
  int height;
  int width;
  int score;
  int highScore;
  int player;
  int level;
  AbstractLevel *currentLevel;

public:
  Board();
  ~Board();
  void updateBoard(Board &board);
  void changeBlock(const int x, const int y, const char block);
  void translateBlock(const int x, const int y, const int rotation);
  void restBlock(const int level);
  int getHeight();
};
#endif