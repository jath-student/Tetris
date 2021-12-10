#include <memory>

#include "forcefx.h"
#include "baseboard.h"

ForceFX::ForceFX(shared_ptr<AbsBoard> component, char b) : BoardDecorator{component}, forceBlock{b} {}

void ForceFX::updateBoard(BaseBoard &board) {
  component->updateBoard(board);

  //Determine if heavy param needs to be added to block
  
  bool executeForce = board.getForce();
  if (executeForce == true) {
    bool makeHeavy = true;
    if (board.getLevel() <= 2) { makeHeavy = false; }

    Block *forceBlk;
    if (forceBlock == 'I') { forceBlk = new Iblock(makeHeavy); }
    if (forceBlock == 'O') { forceBlk = new Oblock(makeHeavy); }
    if (forceBlock == 'J') { forceBlk = new Jblock(makeHeavy); }
    if (forceBlock == 'Z') { forceBlk = new Zblock(makeHeavy); }
    if (forceBlock == 'T') { forceBlk = new Tblock(makeHeavy); }
    if (forceBlock == 'L') { forceBlk = new Lblock(makeHeavy); }
    if (forceBlock == 'S') { forceBlk = new Sblock(makeHeavy); }

    if (board.fitBlock(forceBlock)) {
      int xCoord = (board.getCurrentBlock())->getX();
      int yCoord = (board.getCurrentBlock())->getY();
      delete board.getCurrentBlock();
      board.setCurrentBlock(forceBlk);
      board.doMove(xCoord, yCoord, 0);
    } else {
      delete forceBlk;
      board.setLost(true);
    }
  }
}

ForceFX::~ForceFX(){}