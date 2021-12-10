#include <cstdlib>
#include <string>
#include <vector>

#include "levelone.h"
#include "block.h" // F: need this??

// Constructor & Destructor
LevelOne::LevelOne(string name, bool rand): lvl{1}, fileName(name), random(rand) {}
LevelOne::~LevelOne() { blocks.clear(); }

// Accessors
int LevelOne::getLevel() { return lvl; }
bool LevelOne::getRandom() { return random; }
string LevelOne::getFileName() { return fileName; }

// Other Operations
void LevelOne::setUpLevel() {
  // If there is no file provided then we do not have to set up the sequence of predetermined blocks
  if (random == true ) { return; }

  // assuming file is provided, load the blocks from the file to the sequence of blocks
  char block;
  infile.open(fileName);
  while( infile >> block ) {
    blocks.emplace_back(block);
  }
}

Block* LevelOne::nextBlock(size_t idx) {
  size_t pos = 0;
  if ( random == true ) {
    blocks.clear();
    blocks = {'J', 'J', 'O', 'O', 'I', 'I', 'T', 'T', 'L', 'L', 'Z', 'S'};
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


