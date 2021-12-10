#include "subject.h"

void Subject::attach( Observer *o ) {
  observers.emplace_back(o);
}
