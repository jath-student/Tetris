#ifndef __GRAPHICDISPLAY_H__
#define __GRAPHICDISPLAY_H__

#include "observer.h"
#include "subject.h"
#include "window.h"
#include <string>

class Cell;

class GraphicsDisplay: public Observer {
  BaseBoard *gameBoard1; // pointer to board 1
  BaseBoard *gameBoard2; // pointer to board 2
  Xwindow xw;
  public:
    GraphicsDisplay(BaseBoard *brd1, BaseBoard *brd2); // constructor
    ~GraphicsDisplay(); // destructor
    void createGraphicsDisplay(); // initialize graphics display
    void notify(BaseBoard &whoNotified) override;
    void notify(Cell &whoNotified) override;
    void eraseBlind(int player, BaseBoard *board);
    void drawBlind(int player);
    void printGameOver(int winner); // print winners
};
#endif