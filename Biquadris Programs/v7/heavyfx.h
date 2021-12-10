#ifndef __HEAVYFX_H__
#define __HEAVYFX_H__

#include <memory> 
#include "absboard.h"
#include "boarddecorator.h"

class HeavyFX : public BoardDecorator {
  public:
    HeavyFX(shared_ptr<AbsBoard> comp);
    void updateBoard(BaseBoard &board) override;
    ~HeavyFX();
};
#endif