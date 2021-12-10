#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>
#include "observer.h"

using namespace std;

class Subject {
protected:
   std::vector<Observer*> observers;
 public:
   Subject();
   void attach( Observer *o );
   virtual void notifyObservers() = 0;
};

#endif