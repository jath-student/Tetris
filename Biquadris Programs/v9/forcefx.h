
#ifndef __FORCEFX_H__
#define __FORCEFX_H__

#include <memory> 
#include "absboard.h"
#include "boarddecorator.h"

class ForceFX : public BoardDecorator {
  char forceBlock;
  public:
    ForceFX(shared_ptr<AbsBoard> comp, char b); // constructor
    void updateBoard(BaseBoard &board) override; // updates the board
    ~ForceFX(); // destructor
};
#endif