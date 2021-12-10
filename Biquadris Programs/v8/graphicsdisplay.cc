#include "graphicsdisplay.h"
#include "window.h"
#include "baseboard.h"
#include "cell.h"
#include "absboard.h"

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include "block.h"
using namespace std;

const int WHITE = 8;
const int BLACK = 9;
const int BLIND = 10;

const int CW = 25;
const int DISPW = 35 * CW;
const int DISPH = 33 * CW;
const int MARGINL1 = 4 * CW;
const int MARGINL2 = 20 * CW;

const int HIGHSCOREX = 12 * CW;
const int HIGHSCOREY = 2 * CW;
const int HIGHSCOREX_VAL = 21 * CW;
const int HIGHSCOREY_VAL = HIGHSCOREY;

const int SCOREX = 0; // + marginl1 or margin l2
const int SCOREY = 4 * CW;
const int SCOREX_VAL = 10 * CW; // margin l1 or margin l2
const int SCOREY_VAL = SCOREY;
const int LEVELY = 2 * CW + SCOREY;

const int BOARDX = 0;
const int BOARDY = 8 * CW;
const int BOARDWID =  11 * CW;
const int BOARDHGT = 18 * CW;

const int NEXTX = 0;
const int NEXTY = 27 * CW;
const int PREVIEWX = 0;
const int PREVIEWY = NEXTY + (2 * CW);
const int PREVIEWWID = 4 * CW;
const int PREVIEWHGT = 2 * CW;
const size_t STROFFSET = 0.05;

const size_t BLOCKWID = CW - 0.02;

const int BLINDX = 2 * CW;
const int BLINDY = CW * 5;
const int BLINDW = 7 * CW;
const int BLINDH = 10 * CW;

vector<pair<char, int>> colours = {
  {'I', 0}, {'J', 1}, {'L', 2}, {'O', 3}, 
  {'S', 4}, {'T', 5}, {'Z', 6}, {'*', 7}
};

GraphicsDisplay::GraphicsDisplay(BaseBoard *brd1, BaseBoard *brd2) : gameBoard1{brd1}, gameBoard2{brd2}, xw{DISPH, DISPW} {
  createGraphicsDisplay();
}

void GraphicsDisplay::createGraphicsDisplay(){
  // Drawing boards
  xw.fillRectangle(BOARDX + MARGINL1, BOARDY, BOARDWID, BOARDHGT, BLACK);
  xw.fillRectangle(BOARDX + MARGINL2, BOARDY, BOARDWID, BOARDHGT, BLACK);

  //Drawing previews
  xw.fillRectangle(PREVIEWX + MARGINL1, PREVIEWY, PREVIEWWID, PREVIEWHGT, BLACK);
  xw.fillRectangle(PREVIEWX + MARGINL2, PREVIEWY, PREVIEWWID, PREVIEWHGT, BLACK);

  // Drawing Next
  xw.drawString(NEXTX + MARGINL1 + STROFFSET, NEXTY + STROFFSET, "Next Block:");
  xw.drawString(NEXTX + MARGINL2 + STROFFSET, NEXTY + STROFFSET, "Next Block:");

  // Drawing the Scores
  xw.drawString(HIGHSCOREX + STROFFSET, HIGHSCOREY + STROFFSET, "Highscore:");
  xw.drawString(HIGHSCOREX_VAL, HIGHSCOREY_VAL, "0");
  xw.drawString(SCOREX + STROFFSET + MARGINL1, SCOREY + STROFFSET, "Score:");
  xw.drawString(SCOREX_VAL + STROFFSET + MARGINL1, SCOREY_VAL + STROFFSET, "0");
  xw.drawString(SCOREX + STROFFSET + MARGINL2, SCOREY + STROFFSET, "Score:");
  xw.drawString(SCOREX_VAL + STROFFSET + MARGINL2, SCOREY_VAL + STROFFSET, "0");

  // Drawing the levels
  xw.drawString(SCOREX + STROFFSET + MARGINL1, LEVELY + STROFFSET, "Level:");
  xw.drawString(SCOREX_VAL + STROFFSET + MARGINL1, LEVELY + STROFFSET, "0");
  xw.drawString(SCOREX + STROFFSET + MARGINL2, LEVELY + STROFFSET, "Level:");
  xw.drawString(SCOREX_VAL + STROFFSET + MARGINL2, LEVELY + STROFFSET, "0");
}

void GraphicsDisplay::notify(Cell &whoNotified) {
  bool filled = whoNotified.getFilled();
  int curX = whoNotified.getX();
  int curY = whoNotified.getY();
  int player = whoNotified.getParent()->getPlayer();
  char cellType = whoNotified.getType();
  bool blind = whoNotified.getParent()->getBlind();

  auto it = find_if(colours.begin(), colours.end(), [cellType](const pair<char, int> &ele) {return ele.first == cellType;} );
  int cellColour = get<1>(*it); // determine which colour to rep by type, store vector<char, int> to determine colour/int?
  int leftMargin;
  player == 1 ? leftMargin = MARGINL1 : leftMargin = MARGINL2;
  if (filled) {
    xw.fillRectangle(leftMargin + (curX * CW), BOARDY + (curY * CW), BLOCKWID, BLOCKWID, cellColour);
  } else {
    xw.fillRectangle(leftMargin + (curX * CW), BOARDY + (curY * CW), CW, CW, BLACK);
  }
  if (blind) { drawBlind(player); }
}

void GraphicsDisplay::displayPreview(int player, vector<int> preview, int colour) {
  int leftMargin;
  player == 1 ? leftMargin = MARGINL1 : leftMargin = MARGINL2;
  
  xw.fillRectangle(PREVIEWX + leftMargin, PREVIEWY, PREVIEWWID, PREVIEWHGT, BLACK);

  int yAlignment = PREVIEWY;
  int xAlignment = 0;
  for (int x = 0; x < 4; x++){
    if (preview[x] > 3) { yAlignment = PREVIEWY + CW; xAlignment =  preview[x] % 4; }
    else { yAlignment = PREVIEWY; xAlignment =  preview[x]; }

     xw.fillRectangle(PREVIEWX + leftMargin + (xAlignment * CW), yAlignment, BLOCKWID, BLOCKWID, colour);
  }
}

void GraphicsDisplay::displayHighScore(int highScore) {
  xw.fillRectangle(HIGHSCOREX_VAL - 10, HIGHSCOREY_VAL - 15, CW * 2, CW, WHITE);
  xw.drawString(HIGHSCOREX_VAL + STROFFSET, HIGHSCOREY_VAL + STROFFSET, to_string(highScore));
}

void GraphicsDisplay::displayLevel(int level, int player) { 
  int leftMargin;
  player == 1 ? leftMargin = MARGINL1 : leftMargin = MARGINL2;
  xw.fillRectangle(SCOREX_VAL + leftMargin - 10, LEVELY - 15, CW, CW, WHITE);
  xw.drawString(SCOREX_VAL + STROFFSET + leftMargin, LEVELY + STROFFSET, to_string(level));
}

void GraphicsDisplay::displayScore(int score, int player) { 
  int leftMargin;
  player == 1 ? leftMargin = MARGINL1 : leftMargin = MARGINL2;
  xw.fillRectangle(SCOREX_VAL + leftMargin - 10, SCOREY - 15, CW, CW, WHITE);
  xw.drawString(SCOREX_VAL + STROFFSET + leftMargin, SCOREY + STROFFSET, to_string(score));

}

void GraphicsDisplay::notify(BaseBoard &whoNotified) {
  int player = whoNotified.getPlayer();
  vector<int> preview = (whoNotified.getNextBlock())->getPreview();
  char type = whoNotified.getNextBlock()->getType();
  auto it = find_if(colours.begin(), colours.end(), [type](const pair<char, int> &ele) {return ele.first == type;} );
  int cellColour = get<1>(*it);

  if (whoNotified.getNt().nextBlock) {
    displayPreview(player, preview, cellColour);
  }

  // Updates HS if needed
  if (whoNotified.getNt().highScore) {
    displayHighScore(gameBoard1->getHighScore());
  }

  // Update Level
  if (whoNotified.getNt().level) {
    displayLevel(gameBoard1->getLevel(), player);
  }
  // Update Score
  if (whoNotified.getNt().score) {
    if (player == 1) {
      displayScore(gameBoard1->getScore(), player);
    } else {
      displayScore(gameBoard2->getScore(), player);
    }
  }

  // Update Blind
  if (whoNotified.getNt().onBlindFX) {
    drawBlind(player);
  }
  if (whoNotified.getNt().offBlindFX) {
    if (player == 1) {
      eraseBlind(player, gameBoard1);
    } else {
      eraseBlind(player, gameBoard2);
    }
  }
  // Clear Notifications
  whoNotified.clearNotifs();
}

void GraphicsDisplay::drawBlind(int player) {
  int leftMargin;
  player == 1 ? leftMargin = MARGINL1 :  leftMargin = MARGINL2;
  xw.fillRectangle(leftMargin + BLINDX, BOARDY + BLINDY, BLINDW, BLINDH, BLIND);
}

void GraphicsDisplay::eraseBlind(int player, BaseBoard* b) {
  vector<vector<Cell>> cells = b->getBoard();
  int leftMargin;

  player == 1 ? leftMargin = MARGINL1 :  leftMargin = MARGINL2;

  // Drawing black baord for blinded part
  xw.fillRectangle(leftMargin + BLINDX, BOARDY + BLINDY, BLINDW, BLINDH, BLACK);
  for (int y = 5; y < 18; y++) {
    for (int x = 2; x < 9; x++ ) {
      if(cells[x][y].getFilled()) {
        char cellType = cells[x][y].getType();
        auto it = find_if(colours.begin(), colours.end(), [cellType](const pair<char, int> &ele) {return ele.first == cellType;} );
        int cellColour = get<1>(*it);
        xw.fillRectangle((x * CW) + leftMargin, y * CW + BOARDY, BLOCKWID, BLOCKWID, cellColour); 
      }
    }
  }
}

void GraphicsDisplay::printGameOver(int winner) {
  if (winner == -1) {
    xw.drawString((DISPW / 2) - 200, DISPH - 10, "Thank you for playing!");
    xw.drawString((DISPW / 2), DISPH - 10, "Enter text to close game.");
    return;
  }
  switch(winner) {
    case 1: 
      xw.drawString((DISPW / 2) - 200, DISPH - 10, "Player One is the winner!");
      break;
    case 2:
      xw.drawString((DISPW / 2) - 200, DISPH - 10, "Player Two is the winner!");
      break;
  }
  xw.drawString((DISPW / 2), DISPH - 10, "Enter text to close game.");
}
GraphicsDisplay::~GraphicsDisplay() {};