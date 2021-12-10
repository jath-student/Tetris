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
  TextDisplay(int wid, int hgh, BaseBoard *brd1, BaseBoard *brd2); // constructor 
  void initDisplay(); // initializes the display 
  void notify(Cell &whoNotified) override; // notifies cell based on specific changes
  void notify(BaseBoard &whoNotified) override; // notifies board based on specific changes
  void nextPreview(int player, Block* nextBlock); // stores the next preview
  void displayPreview(ostream &out) const; // displays the preview
  void blindBoard(int player, ostream out) const; // function for when board is blind 
  friend ostream &operator<<(ostream &out, const TextDisplay &td);
  ~TextDisplay(); // destructor 
};

#endif