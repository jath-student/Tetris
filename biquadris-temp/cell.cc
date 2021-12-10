#include "cell.h"
#include "subject.h"
#include "observer.h"

Cell::Cell(const int x, const int y) : x{x}, y{y}, filled{false}, type{' '} {}

void Cell::resetCell() {
  filled = false;
  type = ' ';
  notifyObservers();
}

// Accessors
int Cell::getX() { return x; }
int Cell::getY() { return y; }
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
  if (!filled) {
    filled = true;
  }
  notifyObservers();
}

void Cell::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this); // &ob ?
}



