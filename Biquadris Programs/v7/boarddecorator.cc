#include "boarddecorator.h"
#include "abslevel.h"

BoardDecorator::BoardDecorator(shared_ptr<AbsBoard> comp) : component{comp} {}

void BoardDecorator::updateBoard(BaseBoard &board) {
  component->updateBoard(board);
}

BoardDecorator::~BoardDecorator() {}


