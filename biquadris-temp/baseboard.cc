#include "baseboard.cc"

BaseBoard::BaseBoard(int h, int w, int plyr, int lvl) : isBlind(false), isHeavy(false), isForce(false), height(h), width(w), score(0), highScore(0), player(p), level(lvl) {};

// Accessors
bool BaseBoard::getBlind() { return isBlind; }
bool BaseBoard::getHeavy() { return isHeavy; }
bool BaseBoard::getForce() { return isForce; }
int BaseBoard::getHeight() { return height; }
int BaseBoard::getWidth() { return width; }
int BaseBoard::getScore() { return score; }
int BaseBoard::getHighScore() { return highScore; }
int BaseBoard::getPlayer() { return player; }
int BaseBoard::getLevel() { return level; }
bool BaseBoard::getLost() { return lost; }

// Mutators
void BaseBoard::setBlind( bool b ) { isBlind = b; }
void BaseBoard::setHeavy( bool h ) { isHeavy = h; }
void BaseBoard::setForce( bool f ) { isForce = f; }
void BaseBoard::setHeight( int h ) { height = h; }
void BaseBoard::setWidth( int w ) { width = w; }
void BaseBoard::setScore( int s ) { score = s; }
void BaseBoard::setHighScore( int hs ) { highscore = hs; }
void BaseBoard::setPlayer( int p ) { player = p; }
void BaseBoard::setLevel( int l ) { level = l; }
void BaseBoard::setLost( bool l ) { lost = l; }


void BaseBoard::makeBoard() {
  // If board is not empty, reset it
  if (board.size() != 0) { board.clear(); }
	board = vector<vector<Cell>> (height, vector<Cell>(width));
  for (int r = 0; r < height; r++) {
    for (int c = 0; c < width; c++) {
      board[r].emplace_back(Cell(c, r));
    }
  }
}


void BaseBoard::setPlayLevel(int lvl, bool rand, string fileName) {
  // delete currentLevel;
  level = lvl;
  switch(lvl) {
    case 0:
      currentLevel = new LevelZero(fileName);
      break;
    case 1:
      if (rand == true) {
        currentLevel = new LevelOne();
      } else {
        currentLevel = new LevelOne(fileName, rand);
      }
      break;
    case 2:
      if (rand == true) {
        currentLevel = new LevelTwo();
      } else {
        currentLevel = new LevelTwo(fileName, rand);
      }
      break;
    case 3:
      if (rand == true) {
        currentLevel = new LevelThree();
      } else {
        currentLevel = new LevelThree(fileName, rand);
      }
      break;
    case 4:
      if (rand == true) {
        currentLevel = new LevelFour();
      } else {
        currentLevel = new LevelFour(fileName, rand);
      }
      break;
  }

  // let textdisplay and graphics know that level was changed
  // notifyObservers?
}
