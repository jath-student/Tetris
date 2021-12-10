#ifndef __CELL_H__
#define __CELL_H__

#include "subject.h"
#include "observer.h"
#include <iostream>

class BaseBoard;

class Cell : public Subject {
  int x, y;
  bool filled;
  BaseBoard *parent;
  char type;

public:
  Cell(const int x, const int y, BaseBoard *brd); // constructor

  // setters
  void setType(const char c);
  void setFilled(bool fill);
  void setX(int xCoord);
  void setY(int yCoord);
  
  // getters
  char getType();
  bool getFilled();
  int getX();
  int getY();
  BaseBoard* getParent();

  void resetCell(); // resets the cell
  void notifyObservers() override; // notifies the observers
};
#endif