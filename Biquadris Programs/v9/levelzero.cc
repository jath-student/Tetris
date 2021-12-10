#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "levelzero.h"
#include "block.h"

using namespace std;

// Constructor & Destructor
LevelZero::LevelZero( string name ) : lvl{0}, fileName{name} {}
LevelZero::~LevelZero() { }

// Accessors
int LevelZero::getLevel() { return lvl; }
bool LevelZero::getRandom() { return random; }
string LevelZero::getFileName() { return fileName; }


// Other Operations
void LevelZero::setUpLevel() {

  // load the blocks from the file to the sequence of blocks
  char block;

  infile.open(fileName);
  while( infile >> block ) {
    blocks.emplace_back(block);
  }
}

Block* LevelZero::nextBlock(int idx) {
  this->setUpLevel();
  // Determining which position in the array should be called
  cout << "size of vec:" << static_cast<int>(blocks.size()) << endl;
  int pos = idx % static_cast<int>(blocks.size());

  //Return the corresponding block
  char curBlock = blocks[pos];
  if (curBlock == 'I') {
    return new Iblock();	
  } else if (curBlock== 'O') {
    return new Oblock();
  } else if (curBlock == 'J') {
    return new Jblock();
  } else if (curBlock == 'Z') {
    return new Zblock();
  } else if (curBlock == 'T') {
    return new Tblock();
  }	else if (curBlock == 'L') {
    return new Lblock();
  }
  return new Sblock();
}

