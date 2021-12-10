#ifndef __BLINDFX_H__
#define __BLINDFX_H__

#include <memory> 
#include "absboard.h"
#include "boarddecorator.h"

class BlindFX : public BoardDecorator {
  public:
    BlindFX(shared_ptr<AbsBoard> comp);
    void updateBoard(BaseBoard &board) override;
    ~BlindFX();
};
#endif