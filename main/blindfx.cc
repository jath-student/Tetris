#include <memory>

#include "blindfx.h"
#include "baseboard.h"

BlindFX::BlindFX(shared_ptr<AbsBoard> component) : BoardDecorator{component} {}

void BlindFX::updateBoard(BaseBoard &board) {
  component->updateBoard(board);
}

BlindFX::~BlindFX(){}