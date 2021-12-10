#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>
#include "observer.h"

using namespace std;

class Subject {
protected:
   std::vector<Observer*> observers; // all obsrvers

 public:
   //Subject();
   void attach( Observer *o ); // attaches observers onto subject
   virtual void notifyObservers() = 0; // notifies observers
};

#endif