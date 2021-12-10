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
    void eraseBlind(int player, BaseBoard *b);
    void drawBlind(int player);
    void printGameOver(int winner); // print winners

    void displayScore(int score, int player);
    void displayHighScore(int highScore);
    void displayLevel(int level, int player);
    void displayPreview(int player, vector<int> preview, int colour);
    void displayBoard(int player, bool draw);

};
#endif