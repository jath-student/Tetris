#ifndef __BOARDDECORATOR_H__
#define __BOARDDECORATOR_H__ 

#include <memory>
#include "absboard.h"

using namespace std;

class BoardDecorator : public AbsBoard  {
  protected:
    shared_ptr<AbsBoard> component;
  public:
    BoardDecorator(shared_ptr<AbsBoard> component);
    void updateBoard(BaseBoard &board) override;
    virtual ~BoardDecorator();

};

#endif


