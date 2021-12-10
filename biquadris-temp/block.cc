#include "block.h"
#include <vector>
#include <string>

using namespace std;

Block::Block(size_t x, size_t y, size_t rotation) {
    this->x = x;
    this->y = y;
    this->rotation = rotation;
}

Block::~Block() {}

size_t  Block::getX() {return x;}

size_t  Block::getY() {return y;}

size_t  Block::getRotation() {return rotation;}

void Block::setX(size_t xCor) {x = xCor;}

void Block::setY(size_t yCor) {y = yCor;}

void Block::setRotation(size_t rotationAmt) {rotation = rotationAmt;}
