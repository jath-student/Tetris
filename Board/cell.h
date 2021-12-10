#ifndef __CELL_H__
#define __CELL_H__

#include <iostream>
#include <pthread.h>

class Cell {
  bool filled;
  char type;
  int x;
  int y;

public:
  Cell(const int x, const int y);
  void setType(const char c);
  void dropDown();
};
#endif