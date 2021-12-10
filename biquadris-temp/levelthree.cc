#include <cstdlib>
#include <string>
#include <vector>

#include "levelthree.h"
#include "block.h" // F: need this??

// Constructor & Destructor
LevelThree::LevelThree(string name, bool rand): lvl{3}, fileName{name}, random(rand) {}
LevelThree::~LevelThree() { blocks.clear(); }

// Accessors
int LevelThree::getLevel() { return lvl; }
bool LevelThree::getRandom() { return random; }
string LevelThree::getFileName() { return fileName; }

// Other Operations
void LevelThree::setUpLevel() {
  // If there is no file provided then we do not have to set up the sequence of predetermined blocks
  if (random == true ) { return; }

  // assuming file is provided, load the blocks from the file to the sequence of blocks
  char block;
  infile.open(fileName);
  while( infile >> block ) {
    blocks.emplace_back(block);
  }
}

Block* LevelThree::nextBlock(size_t idx) {
  size_t pos = 0;
  if ( random == true ) {
    blocks.clear();
    blocks = {'J', 'O','I', 'T', 'L', 'Z', 'Z', 'S', 'S'};
    pos = rand() % blocks.size();
  } else {
    pos = idx % blocks.size();
  }

  //Return the corresponding block
  // F: fix the constructors of the blocks
  char curBlock = blocks[pos];
  if (curBlock == 'I') return new Iblock{};	
  else if (curBlock == 'O') return new Oblock{};
  else if (curBlock == 'J') return new Jblock{};
	else if (curBlock == 'Z') return new Zblock{};
	else if (curBlock == 'T') return new Tblock{};
	else if (curBlock == 'L') return new Lblock{};
  return new Sblock{};
}


