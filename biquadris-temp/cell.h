#ifndef __CELL_H__
#define __CELL_H__
#include "subject.h"
#include "observer.h"
#include <iostream>
//#include <pthread.h>

class Cell : public Subject {
  int x, y;
  bool filled;
  char type;

public:
  Cell(const int x, const int y);

  void setType(const char c);
  void setFilled(bool fill);
  void setX(int xCoord);
  void setY(int yCoord);
  
  char getType();
  bool getFilled();
  int getX();
  int getY();

  void resetCell(); // resets the cell
  void notifyObservers();
  //void dropDown();
};
#endif