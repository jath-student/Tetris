#include "block.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

Block::Block(int x, int y, int rotation, bool heavy) {
    this->x = x;
    this->y = y;
    this->rotation = rotation;
    this->heavy = heavy;
}

Block::~Block() {}

int  Block::getX() {return x;}

int  Block::getY() {return y;}

int  Block::getRotation() {return rotation;}

void Block::setX(int xCor) {x = xCor;}

void Block::setY(int yCor) {y = yCor;}

void Block::setRotation(int rotationAmt) {rotation = rotationAmt;}

bool Block::blockIsHeavy() { return heavy; }
