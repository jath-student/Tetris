#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "observer.h"

class Subject {
   std::vector<Observer*> observers;

 public:
   Subject();
   void attach( Observer *o );
   virtual void notifyObservers() = 0;
   virtual ~Subject() = 0;
};

#endif