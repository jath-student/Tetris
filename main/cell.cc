#include "cell.h"
#include "subject.h"
#include "observer.h"

using namespace std;

Cell::Cell(const int x, const int y, BaseBoard *brd) : x{x}, y{y}, filled{false}, parent{brd}, type{' '} {}

void Cell::resetCell() {
  filled = false;
  type = ' ';
  notifyObservers();
}

// Accessors
int Cell::getX() { return x; }
int Cell::getY() { return y; }
BaseBoard* Cell::getParent() { return parent; };
bool Cell::getFilled() { return filled; }
char Cell::getType() { return type; }

// Mutators
void Cell::setFilled(bool fill) { 
  filled = fill; 
  if (!fill) { resetCell(); }
  notifyObservers();
}
void Cell::setX(int xCoord) { x = xCoord; }
void Cell::setY(int yCoord) { y = yCoord; }

void Cell::setType(const char c) {
  type = c;
  if (c != ' ') {
    filled = true;
    notifyObservers();
  } else {
    resetCell();
  }
}

void Cell::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}
