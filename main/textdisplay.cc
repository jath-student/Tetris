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
  initDisplay();
}

void TextDisplay::initDisplay() {
  // initialize the Preview sections
  for (int i = 0; i < 8; ++i) {
    preview1.emplace_back(spaceChar);
    preview2.emplace_back(spaceChar);
  }

  // initialize the textdisplay section
  for (int i = 0; i < width; ++i) {
    vector<char> vec;
    display1.emplace_back(vec);
    display2.emplace_back(vec);
    for (int j = 0; j < height; ++j) {
      display1[i].emplace_back(spaceChar);
      display2[i].emplace_back(spaceChar);
    }
  }
}

void TextDisplay::notify(Cell &whoNotified) {
  int x = whoNotified.getX();
  int y = whoNotified.getY();
  
  // Change the type of cell
  BaseBoard *compare = whoNotified.getParent();
  if (compare == board1) { 
    display1[x][y] = whoNotified.getType();
  } else {
    display2[x][y] = whoNotified.getType();
  }
  
}

void TextDisplay::notify(BaseBoard &whoNotified) {
  if (whoNotified.getNt().nextBlock == true) {
    nextPreview(whoNotified.getPlayer(), whoNotified.getNextBlock());
  }
}

void TextDisplay::nextPreview(int p, Block* blk) {
  if (blk->getType() == '*') return;
  int count = 0;
  vector<int> replace = blk->getPreview();
  if (p == 1) {
    preview1.clear();
    for (int i = 0; i < 8; i++) {
      if (count < 4 && i == replace[count]) {
        preview1.emplace_back(blk->getType());
        count++;
      } else {
        preview1.emplace_back(spaceChar);
      }
    }
  } else {
    preview2.clear();
    for (int i = 0; i < 8; i++) {
      if (count < 4 && i == replace[count]) {
        preview2.emplace_back(blk->getType());
        count++;
      } else {
        preview2.emplace_back(spaceChar);
      }
    }
  }
}

void TextDisplay::blindBoard(int player, ostream out) const {
  vector<vector<char>> blindVersion;
  player == 1 ? blindVersion = display1 : blindVersion = display2;

  for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if ((x >= 5 && x <= 14) && (y >= 2 && y <= 8)) {
				blindVersion[x][y] = '?';
			}
		}
	}

  for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
		  player == 1 ? out << blindVersion[x][y] : out << display1[x][y];
		}
     for (int y = 0; y < width; y++) {
			player == 2 ? out << blindVersion[x][y] : out << display2[x][y];
		}
    out << endl;
	}
}


void TextDisplay::displayPreview(ostream &out) const {
  out << "Next: \t\t      Next:\n";
  for (int i = 0; i < 4; i++) {
    out << preview1[i];
  }
  out << "\t\t       ";
  for (int i = 0; i < 4; i++) {
    out << preview2[i];
  }
  out << "\n";
    for (int i = 4; i < 8; i++) {
    out << preview1[i];
  }
  out << "\t\t       ";
  for (int i = 4; i < 8; i++) {
    out << preview2[i];
  }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  int spaceBW = (td.height * 2 - td.width) / 2;
  string line(td.width, '-');
  string lineHS(td.width * 2 - 4, '-');
  string spaceBoard(td.width, ' ');
  string spaceHeader(td.width + 1, ' ');
  string spaceHighscore(spaceBW - 3, ' ');
  string bigLine = line + line + line;


  // Printing header with highscore, levels and current scores
  out << bigLine << endl;
  out << spaceHighscore << "| Highscore: " << setw(3) << td.board1->getHighScore() << " |\n" << spaceHighscore 
      << lineHS << endl;
  out << " Score:" << setw(3) << td.board1->getScore() << spaceHeader  << "Score:" << setw(3) << td.board2->getScore() 
      << "\n" << " Level:" << setw(3) << td.board1->getLevel() << spaceBoard << " Level:" << setw(3) << td.board2->getLevel() << 
      "\n" << line << spaceBoard << line << endl;

  const bool isBlind1 = td.board1->getBlind();
  const bool isBlind2 = td.board2->getBlind();
  // Both Boards are regular no blind effect
  if (!isBlind1 && !isBlind2) {
    for (int i = 0; i < td.height; ++i) {
      for (int j = 0; j < td.width; ++j)
        out << td.display1[j][i];
      out << spaceBoard;
      for (int j = 0; j < td.width; ++j)
        out << td.display2[j][i];
      out << endl;
    }
  } else if (isBlind1 && !isBlind2) { // Player 1 has Blind Board
    for (int i = 0; i < td.height; ++i) {
      for (int j = 0; j < td.width; ++j) {
        if (j >= 2 && j <= 8 && i >= td.height - 4 && i >= td.height - 15) {
          out << '?';
        } else {
          out << td.display1[j][i];
        }
      }
      out << spaceBoard;
      for (int j = 0; j < td.width; ++j){
        out << td.display2[j][i];
      }
      out << endl;
    }
  } else { // Player 1 has Blind Board
    for (int i = 0; i < td.height; ++i) {
      for (int j = 0; j < td.width; ++j) {
        out << td.display1[j][i];
      }
      out << spaceBoard;
      for (int j = 0; j < td.width; ++j){
        if (j >= 2 && j <= 8 && i <= td.height - 4 && i >= td.height - 12) {
          out << '?';
        } else {
          out << td.display2[j][i];
        }
      }
      out << endl;
    }
  }

  out << line << spaceBoard << line << endl;
  td.displayPreview(out);
  out << endl;
  return out;
}

TextDisplay::~TextDisplay() {}