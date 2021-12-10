#include <memory>

#include "heavyfx.h"
#include "baseboard.h"

HeavyFX::HeavyFX(shared_ptr<AbsBoard> component) : BoardDecorator{component} {}

void HeavyFX::updateBoard(BaseBoard &board) {
  component->updateBoard(board);
}

HeavyFX::~HeavyFX(){}