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
const int HSSPACE = 8; 
const int LVLSPACE = 10;
const int BOARDSPACE = 15;
const int PREVIEWSPACE = 15;
const int PREVIEWBOTTOM = 15;

size_t cw = 22;
size_t midSpace = 8;
size_t borderS = 5;
size_t dispH = (18 + (borderS * 3)) * cw;
size_t dispW = ((11 * 2) + midSpace + (borderS * 2)) * cw;
size_t boardW = 11 * cw;
size_t boardH = 18 * cw;

size_t marginT = cw * 7;
size_t marginB = dispH - marginT + 30;
size_t space = 8 * cw;
size_t marginL1 = cw * 5;
size_t marginL2 = marginL1 + boardW + space;

string spaceHS(16, ' '), spaceLvl(31, ' ');


vector<pair<char, int>> colourCombos = {
  {'I', 0}, {'J', 1}, {'L', 2}, {'O', 3}, 
  {'S', 4}, {'T', 5}, {'Z', 6}, {'*', 7}
};


GraphicsDisplay::GraphicsDisplay(BaseBoard *brd1, BaseBoard *brd2): gameBoard1{brd1}, gameBoard2{brd2}, 
     xw{1000, 750}{
  createGraphicsDisplay();
  //xw{static_cast<int>(cw * dispW), static_cast<int>(cw * dispH)}
}

void GraphicsDisplay::createGraphicsDisplay() {
    //int topBorder = marginT; // might need to change these numbers when we acc see the display
    //marginL1 = 15; // might need to change these numbers when we acc see the display
    //midSpace = 20; // might need to change these numbers when we acc see the display
    
    // printing highscores and levels
    string hs = "High Score: " + spaceHS + to_string(gameBoard1->getHighScore());
    string p1L = "Level: " + spaceLvl + to_string(gameBoard1->getLevel());  
    string p2L = "Level: " + spaceLvl + to_string(gameBoard2->getLevel()); 

    // drawing the board out
    xw.drawString((dispW - space) / 2, marginT - 80, hs);
    xw.drawString(marginL1, marginT - 40, p1L);
	  xw.drawString(marginL1, marginT - 20, "Score: " + spaceLvl + "0");
	  xw.drawString(marginL2, marginT - 40, p2L);
    xw.drawString(marginL2, marginT - 20, "Score: " + spaceLvl + "0");

    // background for boards
    xw.fillRectangle(marginL1, marginT, boardW - 0.01, boardH - 0.01, BLACK);
    xw.fillRectangle(marginL2, marginT, boardW - 0.01, boardH - 0.01, BLACK);
    // next block
    xw.drawString(marginL1, dispH - marginT + 10, "Next Block:");
    xw.drawString(marginL2, dispH - marginT + 10, "Next Block:");
}

void GraphicsDisplay::notify(Cell &whoNotified) {
  bool filled = whoNotified.getFilled();
  int curX = whoNotified.getX();
  int curY = whoNotified.getY();
  int player = whoNotified.getParent()->getPlayer();
  char cellType = whoNotified.getType();
  bool blind = whoNotified.getParent()->getBlind();

  auto it = find_if(colourCombos.begin(), colourCombos.end(), [cellType](const pair<char, int> &ele) {return ele.first == cellType;} );
  int cellColour = get<1>(*it); // determine which colour to rep by type, store vector<char, int> to determine colour/int?
  size_t blkWid = cw - 0.01; // cellWidth subtract something to show blackoutline

  int leftMargin;
  player == 1 ? leftMargin = marginL1 : leftMargin = marginL2;

  if (filled) {
    xw.fillRectangle((marginT + curX * cw), (marginL1 + curY * cw), blkWid, blkWid, cellColour);
  } else {
    xw.fillRectangle((marginT + curX * cw), (marginL1 + curY * cw), blkWid, blkWid, BLACK);
  }

  if (blind) { drawBlind(player); }
}


// space vars: highscore, level, board, preview
void GraphicsDisplay::notify(BaseBoard &whoNotified) {
  int player = whoNotified.getPlayer();
  vector<int> preview = (whoNotified.getNextBlock())->getPreview();
  char type = whoNotified.getNextBlock()->getType();
  auto it = find_if(colourCombos.begin(), colourCombos.end(), [type](const pair<char, int> &ele) {return ele.first == type;} );
  int cellColour = get<1>(*it);
  size_t blkWid = cw - 0.01;
  size_t offset = 0.005;
  if (whoNotified.getNt().nextBlock) {
    for (int i = 0; i < 4; i++) { 
      for (int j = 0; j < 2; j++) {
        if (player == 1) {
          xw.fillRectangle((i * cw) + marginL1, (j * cw) + marginB, cw + 1, cw + 1, WHITE);
        } else {
          xw.fillRectangle((i * cw) + marginL2, (j * cw)  + marginB, cw + 1, cw + 1, WHITE);
        }
      }
    }
    size_t marginLeft;
    player == 1 ? marginLeft = marginL1 : marginLeft = marginL2;
    cout << marginLeft << endl;
    for (int i = 0; i < static_cast<int>(preview.size()); i++) {
      size_t curCell = preview[i];
      if (curCell > 3) {
        xw.fillRectangle((curCell % 4) * cw + marginLeft + offset, (1 * cw) + marginB + offset, blkWid, blkWid, cellColour);
      } else {
        xw.fillRectangle((curCell + cw) + marginLeft + offset, (0 * cw) + marginB + offset, blkWid, blkWid, cellColour);
      }
    }
  }

  // Updates HS if needed
  if (whoNotified.getNt().highScore) {
    string drawHS, textSpace;
    //for (int i = 0; i < 10; i++) { textSpace += " ";}
    drawHS = "High Score: " + spaceHS + to_string(gameBoard1->getHighScore());
    xw.fillRectangle(marginL1 * 4.3, marginT - 90, 80, 15, WHITE); // F: check nums
    xw.drawString((dispW - space) / 2, marginT - 80, drawHS);
  }

  // Update Level
  if (whoNotified.getNt().level) {
    string lvlP1 = "Level: " + spaceLvl + to_string(gameBoard1->getLevel());
    string lvlP2 = "Level: " + spaceLvl + to_string(gameBoard2->getLevel());
    string drawLevel = lvlP1 + "       " + lvlP2; // F: check
    xw.fillRectangle(marginL1 * 4, marginT - 50, 25, 15, WHITE); // F: check nums
    xw.drawString(marginL1, marginT - 40, drawLevel);
  }
  // Update Score
  if (whoNotified.getNt().score) {
    string lvlP1 = "Score: " + spaceLvl + to_string(gameBoard1->getScore());
    string lvlP2 = "Score: " + spaceLvl + to_string(gameBoard2->getScore());
    string drawScore = lvlP1 + "       " + lvlP2;
    xw.fillRectangle(marginL1 * 2.6, marginT - 30, 100, 15, WHITE); // F: check nums
    xw.drawString(marginL1, marginT - 20, drawScore); /// F: check
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
  if (player == 1) {
    xw.fillRectangle((2 * cw) + marginL1, (5 * cw) + marginT, 7 * cw, 10 * cw, BLIND); // need const for blind colour
  } else {
    xw.fillRectangle((2 * cw) + marginL2, (5 * cw) + marginT, 7 * cw, 10 * cw, BLIND);
  }
}

void GraphicsDisplay::eraseBlind(int player, BaseBoard* board) {
  size_t blkWid = cw - 0.01;
  vector<vector<Cell>> cells = board->getBoard();
  if (player == 1) { // drawing entire board black
    xw.fillRectangle(2 * cw + marginL1, 5 * cw + marginT, 7 * cw, 10 * cw, BLACK);
  } else {
    xw.fillRectangle(2 * cw + marginL2, 5 * cw + marginT, 7 * cw, 10 * cw, BLACK);
  }
  size_t marginLeft = player == 1 ? marginL1 : marginL2;
  for (int y = 5; y < 15; y++) {
    for (int x = 2; x < 9; x++ ) {
      if(cells[x][y].getFilled()) {
        char cellType = cells[x][y].getType();
        auto it = find_if(colourCombos.begin(), colourCombos.end(), [cellType](const pair<char, int> &ele) {return ele.first == cellType;} );
        int cellColour = get<1>(*it);
        xw.fillRectangle(x * cw + marginLeft, y * cw + marginT, blkWid, blkWid, cellColour); 
      }
    }
  }
}

void GraphicsDisplay::printGameOver(int winner) {
  switch(winner) {
    case 1: 
      xw.drawString((dispW / 2) - 45, (dispH / 2), "Player One Won!");
      break;
    case 2:
      xw.drawString((dispW / 2) - 45, (dispH / 2), "Player Two Won!");
      break;
  }
}

GraphicsDisplay::~GraphicsDisplay() {};