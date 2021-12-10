#include <iostream>
#include <string>
#include <iomanip>
#include <string>

#include "observer.h"
#include "textdisplay.h"
#include "cell.h"
#include "baseboard.h"
#include "absboard.h"

using namespace std;

TextDisplay::TextDisplay(int wid, int hgh, BaseBoard *brd1, BaseBoard *brd2) : width{wid}, height{hgh}, board1{brd1}, board2{brd2}, spaceChar{' '} {
  void initDisplay();
}

void TextDisplay::initDisplay() {
  // initialize the Preview sections
  for (int i = 0; i < width; ++i) {
    preview1.emplace_back(spaceChar);
    preview2.emplace_back(spaceChar);
  }

  // initialize the textdisplay section
  for (int i = 0; i < height; ++i) {
    vector<char> vec;
    display1.emplace_back(vec);
    display2.emplace_back(vec);
    for (int j = 0; j < width; ++j) {
      display1[i].emplace_back(spaceChar);
      display2[i].emplace_back(spaceChar);
    }
  }
}

void TextDisplay::notifyCell(Cell &cellNotified) {
  int x = cellNotified.getX();
  int y = cellNotified.getY();

  BaseBoard *compare = cellNotified.getParent();

  if (compare == board1) { 
    display1[x][y] = cellNotified.getType();
  } else {
    display2[x][y] = cellNotified.getType();
  }
}

void TextDisplay::notifyBoard(BaseBoard &boardNotified) {
  if (boardNotified.getNt().nextBlock == true) {
    nextPreview(boardNotified.getPlayer(), boardNotified.getNextBlock());
  }
}

void TextDisplay::nextPreview(int p, Block* blk) {
  if (blk->getType() == '*') return;
  int count = 0;
  vector<int> replace = blk->getPreview();
  if (p == 1) {
    for (int i = 0; i < 8 && count < 4; i++) {
      preview1[i] = spaceChar;
    }
    for (int i = 0; i < 4; i++) {
      int idx = replace[i];
      preview1[idx] = blk->getType();
    }
  } else {
    for (int i = 0; i < 8; i++) {
      preview2[i] = spaceChar;
    }
    for (int i = 0; i < 4; i++) {
      int idx = replace[i];
      preview2[idx] = blk->getType();
    }
  }
}

void TextDisplay::blindBoard(int player, ostream out) const {
  vector<vector<char>> blindVersion;
  player == 1 ? blindVersion = display1 : blindVersion = display2;

  for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			if ((x >= 5 && x <= 14) && (y >= 2 && y <= 8)) {
				blindVersion[x][y] = '?';
			}
		}
	}

  for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
		  player == 1 ? out << blindVersion[x][y] : out << display1[x][y];
		}
     for (int y = 0; y < width; y++) {
			player == 2 ? out << blindVersion[x][y] : out << display2[x][y];
		}
    out << endl;
	}
}


void TextDisplay::displayPreview(ostream &out) const {
  // F: might need to modify this by adding spacing
  out << "Next: \n";
  for (int i = 0; i < 8; i++) {
    if (i == 4) { out << "\n"; }
    out << preview1[i];
  }
  out << "\n";
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  int spaceHigh = (td.width * 2 - td.width) / 2;
  string divider;
  string spaceBoard;
  string spaceHighscore;

  for (int i = 0; i < td.width; ++i) {
    divider += '-';
  }
  for (int i = 0; i < td.width; ++i) {
    spaceBoard += ' ';
  }
  for (int i = 0; i < spaceHigh; ++i) {
    spaceHighscore += ' ';
  }

  out << endl;
  out << spaceHighscore << "High Score:" << setw(5) << td.board1->getHighScore()
      << spaceHighscore << endl;
  out << "Level:" << setw(5) << td.board1->getLevel() << spaceBoard
      << "Level:" << setw(5) << td.board2->getLevel() << endl
      << "Score:" << setw(5) << td.board1->getScore() << spaceBoard
      << "Score:" << setw(5) << td.board2->getScore() << endl
      << divider << spaceBoard << divider << endl;

  const bool isBlind1 = td.board1->getBlind();
  if (!isBlind1 && td.board2->getBlind()) {
    for (int i = 0; i < td.height; ++i) {
      for (int j = 0; j < td.width; ++j)
        out << td.display1[i][j];
      out << spaceBoard;
      for (int j = 0; j < td.width; ++j)
        out << td.display2[i][j];
      out << endl;
    }
  } else {
    int player = 2;
    if (isBlind1) {
      player = 1;
    }
    string spaceBoard;
    for (int i = 0; i < td.width; ++i) {
      spaceBoard += ' ';
    }
    vector<vector<char>> displayTemp;
    if (player == 1) {
      displayTemp = td.display1;
    } else if (player == 2) {
      displayTemp = td.display2;
    }
    for (int i = 0; i < td.height; ++i) {
      for (int j = 0; j < td.width; ++j) {
        if (i >= 5 && i <= td.height && j >= 2 && j <= td.width) {
          displayTemp[i][j] = '?';
        }
      }
    }
    for (int i = 0; i < td.height; ++i) {
      for (int j = 0; j < td.width; ++j) {
        player == 1 ? out << displayTemp[i][j] : out << td.display1[i][j];
      }
      out << spaceBoard;
      for (int j = 0; j < td.width; ++j) {
        player == 2 ? out << displayTemp[i][j] : out << td.display2[i][j];
      }
      out << endl;
    }
  }

  out << divider << spaceBoard << divider << endl;
  td.displayPreview(out);
  out << endl;
  return out;
}