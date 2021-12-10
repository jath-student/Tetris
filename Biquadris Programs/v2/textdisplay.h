#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "observer.h"
#include <iostream>
#include <ostream>
#include <vector>

class Cell;
class Block;

using namespace std;

class TextDisplay : public Observer {
  int width, height;
  vector<vector<char>> display1, display2;
  vector<char> preview1, preview2;
  BaseBoard *board1;
  BaseBoard *board2;
  char spaceChar;

public:
  TextDisplay(int wid, int hgh, BaseBoard *brd1, BaseBoard *brd2);
  void initDisplay();
  void notifyCell(Cell &cellNotified) override;
  void notifyBoard(BaseBoard &boardNotified) override;
  void nextPreview(int player, Block* nextBlock);
  void displayPreview(ostream &out) const;
  void blindBoard(int player, ostream out) const;
  friend ostream &operator<<(ostream &out, const TextDisplay &td);
  ~TextDisplay();
};

#endif