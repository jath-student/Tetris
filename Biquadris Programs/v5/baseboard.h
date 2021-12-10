#ifndef __BASEBOARD_H__
#define __BASEBOARD_H__

#include <string>
#include <vector>

#include "placedblkinfo.h"
#include "block.h"
#include "abslevel.h"
#include "absboard.h"
#include "subject.h"
#include "observer.h"
#include "boardNotifications.h"
#include "cell.h"
#include "textdisplay.h"

class Observer;
class TextDisplay;

class BaseBoard : public Subject, public AbsBoard {
  vector<vector<Cell>> board;
  vector<vector<PlacedBlkInfo>> placedBlocks;


  Block *currentBlock = nullptr;
  Block *nextBlock = nullptr;
  AbsLevel *currentLvl = nullptr;

  bool isBlind = false;
  bool isHeavy = false;
  bool isForce = false;
  bool lost = false;
  bool spawnEffect = false;
  int height;
  int width;
  int score = 0;
  int highScore = 0;
  int player;
  int level;

  BoardNotifications nt;

public:
  BaseBoard(int h, int w, int plyr, int lvl);
  ~BaseBoard();
  bool getBlind();
  bool getHeavy();
  bool getForce();
  int getHeight();
  int getWidth();
  int getScore();
  int getHighScore();
  int getPlayer();
  int getLevel();
  bool getLost();
  bool getSpawnEffect();
  vector<vector<Cell>> getBoard();
  BoardNotifications getNt();
  AbsLevel* getCurrentLevel();
  Block* getCurrentBlock();
  Block* getNextBlock();
  void setCurrentBlock(Block* curBlock);
  void setCurrentLevel(int lvl, bool rand, string fileName);
  void setNextBlock(Block* nxtBlock);
  void setBlind(bool b);
  void setHeavy(bool h);
  void setForce(bool f);
  void setHeight(int h);
  void setWidth(int w);
  void setScore(int s);
  void setHighScore(int hs);
  void setPlayer(int p);
  void setLevel(int l);
  void setLost(bool l);
  void setSpawnEffect(bool fx);
  void makeBoard(); // creates a new board or resets
  void setType(int xCoord, int yCoord, char type); // sets the specified cell to be of type
  void resetType(int xCoord, int yCoord);          // erases the type that occupied cell
  void notifyObservers() override;
  void updateBoard(BaseBoard &board);
  void setPlayLevel(int lvl, bool rand, string fileName = "");
  void clearedLines(); // checks if any lines were cleared
  void eraseNotifications();
  void reset();
  bool validMove(int moveX, int moveY, int rotate);
  void doMove(int moveX, int moveY, int rotate);
  void setObservers(Observer *ob);
  void clearNotifs();
  friend ostream &operator<<(ostream &out, const BaseBoard &brd);

  bool gameOver();

  int removePlacedCell(int x, int y);
  void addPlacedBlk();
  void shiftPlacedBlks(int yShift);
  bool fitBlock(char block);

};
#endif