#include <cstdlib>
#include <string>
#include <vector>

#include "levelthree.h"
#include "block.h"

// Constructor & Destructor
LevelThree::LevelThree(string name, bool rand): lvl{3}, fileName{name}, random(rand) {}
LevelThree::~LevelThree() { /*blocks.clear();*/ }

// Accessors
int LevelThree::getLevel() { return lvl; }
bool LevelThree::getRandom() { return random; }
string LevelThree::getFileName() { return fileName; }

// Other Operations
void LevelThree::setUpLevel() {
  // If there is no file provided then we do not have to set up the sequence of predetermined blocks
  if (random == true ) { return; }
  blocks.clear();
  // assuming file is provided, load the blocks from the file to the sequence of blocks
  char block;
  infile.open(fileName);
  while( infile >> block ) {
    blocks.emplace_back(block);
  }
}

Block* LevelThree::nextBlock(int idx) {
  int pos = 0;
  if ( random == true ) {
    blocks.clear();
    blocks = {'J', 'O','I', 'T', 'L', 'Z', 'Z', 'S', 'S'};
    pos = rand() % blocks.size();
  } else {
    pos = idx % blocks.size();
  }

  //Return the corresponding block
  char curBlock = blocks[pos];
  if (curBlock == 'I') return new Iblock{true};	
  else if (curBlock == 'O') return new Oblock{true};
  else if (curBlock == 'J') return new Jblock{true};
	else if (curBlock == 'Z') return new Zblock{true};
	else if (curBlock == 'T') return new Tblock{true};
	else if (curBlock == 'L') return new Lblock{true};
  return new Sblock{true};
}


