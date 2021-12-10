#include <string>
#include <vector>
#include <fstream>

#include "levelzero.h"
#include "block.h" // F: need this??

// Constructor & Destructor
LevelZero::LevelZero( string name ) : lvl{0}, fileName{name} {}
LevelZero::~LevelZero() { blocks.clear(); }

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

Block * LevelZero::nextBlock(size_t idx) {
  // Determining which position in the array should be called
  size_t pos = idx % blocks.size();

  //Return the corresponding block
  // F: fix the constructors of the blocks
  char curBlock = blocks[pos];
  if (curBlock == 'I') return new Iblock{};	
  else if (curBlock== 'O') return new Oblock{};
  else if (curBlock == 'J') return new Jblock{};
	else if (curBlock == 'Z') return new Zblock{};
	else if (curBlock == 'T') return new Tblock{};
	else if (curBlock == 'L') return new Lblock{};
  return new Sblock{};
}

