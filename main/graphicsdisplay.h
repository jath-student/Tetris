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
    void notify(BaseBoard &whoNotified) override; // notifies observers about the board
    void notify(Cell &whoNotified) override; // notifies observers about the specific cells that are being changed
    void eraseBlind(int player, BaseBoard *b); // erases the line on board for blind effect
    void drawBlind(int player); // draws the line on board for blind effect
    void printGameOver(int winner); // print winners

    void displayScore(int score, int player); // displays the score
    void displayHighScore(int highScore); // displays the high score
    void displayLevel(int level, int player); // displays the level
    void displayPreview(int player, vector<int> preview, int colour); // displays the preview
    void displayBoard(int player, bool draw); // displays the board

};
#endif