#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "baseboard.h"
#include "placedblkinfo.h"
#include "cell.h"
#include "block.h"
#include "textdisplay.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"

using namespace std;

// Constructor and Destructor
BaseBoard::BaseBoard(int h, int w, int plyr, int lvl) : height(h), width(w), player(plyr), level(lvl) {
  makeBoard();
}

BaseBoard::~BaseBoard() {
	delete currentBlock;
	delete nextBlock;
	delete currentLvl;
}


// Accessors
vector<vector<Cell>> BaseBoard::getBoard() { return board; }
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
bool BaseBoard::getSpawnEffect() {return spawnEffect; }
Block* BaseBoard::getCurrentBlock() { return currentBlock; }
Block* BaseBoard::getNextBlock() { return nextBlock; }
AbsLevel* BaseBoard::getCurrentLevel() { return currentLvl; } //
BoardNotifications BaseBoard::getNt() { return nt; }

// Mutators
void BaseBoard::setBlind(bool b) { 
  isBlind = b; 
  if (isBlind == true) {
    nt.onBlindFX = true;
    nt.offBlindFX = false;
  } else {
    nt.offBlindFX = true;
    nt.onBlindFX = false;
  }
  notifyObservers();
}
void BaseBoard::setHeavy(bool h) { isHeavy = h; }
void BaseBoard::setForce(bool f) { isForce = f; }
void BaseBoard::setHeight(int h) { height = h; }
void BaseBoard::setWidth(int w) { width = w; }
void BaseBoard::setScore(int s) { score = s; }
void BaseBoard::setHighScore(int hs) { 
  highScore = hs; 
  nt.highScore = true; 
  notifyObservers();
}
void BaseBoard::setPlayer(int p) { player = p; }
void BaseBoard::setLevel(int l) { level = l; }
void BaseBoard::setLost(bool l) { lost = l; }
void BaseBoard::setSpawnEffect(bool fx) { spawnEffect = fx; }
void BaseBoard::setCurrentBlock(Block* curBlock) { currentBlock = curBlock; }
void BaseBoard::setNextBlock(Block* nxtBlock) { 
  nextBlock = nxtBlock;
  nt.nextBlock = true;
  notifyObservers();
}
void BaseBoard::setCurrentLevel(int lvl, bool rand, string fileName) {
  delete currentLvl;
  level = lvl;
  switch (lvl) {
  case 0:
    currentLvl = new LevelZero(fileName);
    break;
  case 1:
    rand == true ? currentLvl = new LevelOne() : currentLvl = new LevelOne(fileName, rand);
    break;
  case 2:
    rand == true ? currentLvl = new LevelTwo() : currentLvl = new LevelTwo(fileName, rand);
    break;
  case 3:
    rand == true ? currentLvl = new LevelThree() : currentLvl = new LevelThree(fileName, rand);
    break;
  case 4:
    rand == true ? currentLvl = new LevelFour() : currentLvl = new LevelFour(fileName, rand);
    break;
  }
  nt.level = true;
  notifyObservers();
}

// Shifts all the coords of resting blocks down by 1
void BaseBoard::shiftPlacedBlks(int yShift) {
  int totalPlaced = static_cast<int>(placedBlocks.size());
  for (int blocks = 0; blocks < totalPlaced; blocks++) {
    for (int i = 0; i < 4; i++) {
      int yCoord = placedBlocks[blocks][i].getY();
      if ( yCoord < yShift) {
        placedBlocks[blocks][i].setY(yCoord + 1);
      }
    }
  }
}

// adds a block to placed blocks array
void BaseBoard::addPlacedBlk() {
  int curX = currentBlock->getX();
  int curY = currentBlock->getY();
  int curRot = currentBlock->getRotation();
  vector<pair<int, int>> currentCoords = currentBlock->allFill(curX, curY, curRot);
  
  if (currentBlock->getType() == '*') {
    vector<PlacedBlkInfo> newStarPlaced = {PlacedBlkInfo(get<0>(currentCoords[0]), get<1>(currentCoords[0]), level)};
  }
  vector<PlacedBlkInfo> newPlacedBlk {PlacedBlkInfo(get<0>(currentCoords[0]), get<1>(currentCoords[0]), level),
                                      PlacedBlkInfo(get<0>(currentCoords[1]), get<1>(currentCoords[1]), level),
                                      PlacedBlkInfo(get<0>(currentCoords[2]), get<1>(currentCoords[2]), level),
                                      PlacedBlkInfo(get<0>(currentCoords[3]), get<1>(currentCoords[3]), level)};
  placedBlocks.emplace_back(newPlacedBlk);                          
}

// removes a cell from the placed blocks vector, if entire block is remoevd then outputs level block was gen
int BaseBoard::removePlacedCell(int x, int y) {
  int num = 0;
  int totalPlaced = static_cast<int>(placedBlocks.size());
  for (int blocks = 0; blocks < totalPlaced; blocks++) {
    int numPlacedCells = static_cast<int>(placedBlocks[blocks].size());
    for (int i = 0; i < numPlacedCells; i++) {
      if (placedBlocks[blocks][i].getX() == x && placedBlocks[blocks][i].getY() == y) {
        placedBlocks[blocks][i].setEmpty(true);
        for (int j = 0; j < numPlacedCells; j++) {
          if (placedBlocks[blocks][j].getEmpty() == false) {
            return 0;
          }
          num = j;
        }
        int level = placedBlocks[blocks][num].getLevelCreated();
        placedBlocks.erase(placedBlocks.begin() + blocks);
        return level + 1;
      }
    }
  }
  return 0;
} 


void BaseBoard::updateBoard(BaseBoard &board) {}

void BaseBoard::makeBoard() {
  // If board is not empty, reset it
  if (board.size() != 0) {
    reset();
    board.clear();
  }
  for (int x = 0; x < width; x++) {
    vector<Cell> vec;
    board.emplace_back(vec);
    for (int y = 0; y < height; y++) {
      board[x].emplace_back(Cell(x, y, this));
    }
  }
}

void BaseBoard::reset() {
  if (level == 4) {
    (static_cast<LevelFour*>(currentLvl))->resetInterval();
  }

  setHeavy(false);
  setForce(false);
  setBlind(false);

  score = 0;
  nt.score = true;
  notifyObservers();

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      board[x][y].resetCell();
    }
  }

  placedBlocks.clear();
  delete currentBlock;
  delete nextBlock;
  
}

void BaseBoard::notifyObservers() {
  for (auto &o : observers) o->notify(*this);
}

void BaseBoard::setObservers(Observer *ob) {
	this->attach(ob);
	for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      board[x][y].attach(ob);
    }
  }
}

void BaseBoard::setType(int xCoord, int yCoord, char type) {
  board[xCoord][yCoord].setType(type);
}

void BaseBoard::resetType(int xCoord, int yCoord) {
  board[xCoord][yCoord].resetCell();
}

void BaseBoard::clearNotifs() { nt = {false, false, false, false, false, false}; }

// determines if gameOver
bool BaseBoard::gameOver() {
  int curX = currentBlock->getX();
  int curY = currentBlock->getY();
  int curRot = currentBlock->getRotation();
  vector<pair<int,int>> isValidCoord = currentBlock->allFill(curX, curY, curRot);
  int totalLength = static_cast<int>(isValidCoord.size());
  for (int i = 0; i < totalLength; i++) {
    int checkY = get<1>(isValidCoord[i]);
    if (checkY <= 3) {
      return true;
    }
  }
  return false;
}
bool BaseBoard::validMove(int moveX, int moveY, int rotate) {
  int curX = currentBlock->getX();
  int curY = currentBlock->getY();
  int curRot = currentBlock->getRotation();
  int calcRot = ( rotate + curRot);
  int newRot;
  if (calcRot == -1) {
    newRot = 3;
  } else {
    newRot = calcRot % 4;
  }
  
  vector<pair<int, int>> currentOccupyCoords = currentBlock->allFill(curX, curY, curRot);

  // get fn of 4 pair of ints of what the new block occupies using fn params and current coords
  vector<pair<int, int>> newOccupyCoords = currentBlock->allFill(curX + moveX, curY + moveY, newRot); 

  for (int i = 0; i < 4; i++) {
    int checkX = get<0>(newOccupyCoords[i]);
    int checkY = get<1>(newOccupyCoords[i]);
    if (checkX < 0 || checkY < 0 || checkX >= width || checkY >= height) {
      return false;
    }
    if (board[checkX][checkY].getFilled()) {
      auto it = find(currentOccupyCoords.begin(), currentOccupyCoords.end(), newOccupyCoords[i]);
      if (it == currentOccupyCoords.end()) {
        return false;
      }
    }
  }
  return true;
}

void BaseBoard::doMove(int moveX, int moveY, int rotate) {
  int curX = currentBlock->getX();
  int curY = currentBlock->getY();
  int curRot = currentBlock->getRotation();

  int calcRot = ( rotate + curRot);
  int newRot;
  if (calcRot == -1) {
    newRot = 3;
  } else {
    newRot = calcRot % 4;
  }
  // get the vector of new x,y coordinates each block will occupy
  vector<pair<int, int>> currentOccupyCoords = currentBlock->allFill(curX, curY, curRot);

  currentBlock->setX(curX + moveX);
  currentBlock->setY(curY + moveY);
  currentBlock->setRotation(newRot);
  
  // get fn of 4 pair of ints of what the new block occupies using fn params and current coords
  vector<pair<int, int>> newOccupyCoords = currentBlock->allFill(curX + moveX, curY + moveY, newRot); 

  // resetting the old occupied cells
  for (int i = 0; i < 4; i++) {
    int checkX = get<0>(currentOccupyCoords[i]);
    int checkY = get<1>(currentOccupyCoords[i]);
    board[checkX][checkY].resetCell();
  }
  // setting the new occupied cells
  for (int i = 0; i < 4; i++) {
    int checkX = get<0>(newOccupyCoords[i]);
    int checkY = get<1>(newOccupyCoords[i]);
    board[checkX][checkY].setType(currentBlock->getType());
  }
}

void BaseBoard::clearedLines() {
  int maxY = 0;
  int minY = 0;
  int linesChecked = 0;
  int linesComp = 0;
  bool complete = true;

  int curX = currentBlock->getX();
  int curY = currentBlock->getY();
  int curRot = currentBlock->getRotation();

  int linePoints = 0;

  // Loop through the current coordinates of the block and find max and min y values
  vector<pair<int,int>> coordsCurrent = currentBlock->allFill(curX, curY, curRot);
  minY = get<1>(coordsCurrent[0]);
  maxY = minY;

  // FInd rows we will check
  for (int i = 1; i < 4; i++) {
    if (get<1>(coordsCurrent[i]) > maxY) {
      maxY = get<1>(coordsCurrent[i]);
    }
    if (get<1>(coordsCurrent[i]) < minY) {
      minY = get<1>(coordsCurrent[i]);
    }
  }

  for (int i = maxY; i >= minY && linesChecked <= 4; i--) {
    complete = true;
    for (int j = 0; j < width; j++) {
      if (!board[j][i].getFilled()) {
        complete = false;
        break;
      }
    }

    if (complete == true) {
      linesComp++;
      for (int f = 0; f < width; f++) {
        int p = removePlacedCell(f, i);
        if (p != 0) {
          linePoints += p * p;
        }
      }
      for (int k = i; k > 0; k--) {
        for (int r = 0; r < width; r++) {
          board[r][k].setType(board[r][k - 1].getType());
        }
      }
      shiftPlacedBlks(i);
      for (int r = 0; r < width; r++) {
        board[r][0].resetCell();
      }
      i++;
    }
    linesChecked++;
  }
  if (level == 4 && linesComp == 0 ) { 
    (static_cast<LevelFour*>(currentLvl))->increaseInterval();
  } else if (level == 4 && linesComp > 0) { 
    (static_cast<LevelFour*>(currentLvl))->resetInterval(); 
  }
  if (level == 4 && currentBlock->getType() == '*') {
    (static_cast<LevelFour*>(currentLvl))->resetInterval();
  }
  
  if (linesComp > 0) {
    score += (level + linesComp) * (level + linesComp) + linePoints; // formula for score
    nt.score = true;
    notifyObservers();
    if (score > highScore) {
      setHighScore(score);
    }
    notifyObservers();
  }

  if (linesComp >= 2) { setSpawnEffect(true); } else { setSpawnEffect(false);}
    
  //Delete current block
  delete currentBlock;
}

bool BaseBoard::fitBlock(char block) {
  // If want to replace with the same type of block, return false
  if (block == currentBlock->getType()) { return false;}
  int x = currentBlock->getX();
  int y = currentBlock->getY();
  vector<pair<int, int>> swapBlock;
  vector<pair<int, int>> remCurBlock = currentBlock->allFill(x, y, currentBlock->getRotation());
  if (block == 'S') {
    swapBlock.push_back(make_pair(x+1, y+2));
    swapBlock.push_back(make_pair(x+2, y+2));
    swapBlock.push_back(make_pair(x, y+3));
    swapBlock.push_back(make_pair(x+1, y+3));
  } else if (block == 'Z') {
    swapBlock.push_back(make_pair(x, y+2));
    swapBlock.push_back(make_pair(x+1, y+2));
    swapBlock.push_back(make_pair(x+1, y+3));
    swapBlock.push_back(make_pair(x+2, y+3));
  } else if (block == 'T') {
    swapBlock.push_back(make_pair(x, y+2));
    swapBlock.push_back(make_pair(x+1, y+2));
    swapBlock.push_back(make_pair(x+2, y+2));
    swapBlock.push_back(make_pair(x+1, y+3));
  } else if (block == 'J') {
    swapBlock.push_back(make_pair(x, y+2));
    swapBlock.push_back(make_pair(x, y+3));
    swapBlock.push_back(make_pair(x+1, y+3));
    swapBlock.push_back(make_pair(x+2, y+3));
  } else if (block == 'L') {
    swapBlock.push_back(make_pair(x, y+3));
    swapBlock.push_back(make_pair(x+1, y+3));
    swapBlock.push_back(make_pair(x+2, y+2));
    swapBlock.push_back(make_pair(x+2, y+3));
  } else if (block == 'I') {
    swapBlock.push_back(make_pair(x, y+3));
    swapBlock.push_back(make_pair(x+1, y+3));
    swapBlock.push_back(make_pair(x+2, y+3));
    swapBlock.push_back(make_pair(x+3, y+3));
  } else if (block == 'O') {
    swapBlock.push_back(make_pair(x, y+2));
    swapBlock.push_back(make_pair(x, y+3));
    swapBlock.push_back(make_pair(x+1, y+2));
    swapBlock.push_back(make_pair(x+1, y+3));
  }
  for (int i = 0; i < 4; i++) {
    if (board[get<0>(swapBlock[i])][get<1>(swapBlock[i])].getFilled()) { 
      auto it = find(remCurBlock.begin(), remCurBlock.end(), swapBlock[i]);
      if (it == remCurBlock.end()) { return false; } 
    }
  }

  // If reached this point then block will be swapped
  for (int i = 0; i < 4; i++) {
    board[get<0>(remCurBlock[i])][get<1>(remCurBlock[i])].resetCell();
  }
  for (int i = 0; i < 4; i++) {
    board[get<0>(swapBlock[i])][get<1>(swapBlock[i])].setType(block);
  }
  return true;
}