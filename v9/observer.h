#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Subject;
class Cell;
class BaseBoard;

class Observer {
 public:
  virtual void notify(Cell &whoNotified) = 0; // notifies cell
	virtual void notify(BaseBoard &whoNotified) = 0; // notifies board
  virtual ~Observer(); // destructor
};

#endif