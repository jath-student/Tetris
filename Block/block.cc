#include "block.h"
#include <vector>
#include <string>

using namespace std;

Block::Block(int x, int y, int rotation) {
    this->x = x;
    this->y = y;
    this->rotation = rotation;
}

Block::~Block() {}

int  Block::getX() {return x;}

int  Block::getY() {return y;}

int  Block::getRotation() {return rotation;}

void Block::setX(int xCor) {x = xCor;}

void Block::setY(int yCor) {y = yCor;}

void Block::setRotation(int rotationAmt) {rotation = rotationAmt;}
