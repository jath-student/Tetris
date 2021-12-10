#include <cstdlib>
#include <string>
#include <vector>

#include "leveltwo.h"
#include "block.h"

// Constructor & Destructor
LevelTwo::LevelTwo(string name, bool rand): lvl{2}, fileName(name), random(rand) {}
LevelTwo::~LevelTwo() { /*blocks.clear();*/ }

// Accessors
int LevelTwo::getLevel() { return lvl; }
bool LevelTwo::getRandom() { return random; }
string LevelTwo::getFileName() { return fileName; }

// Other Operations
void LevelTwo::setUpLevel() {
  // If there is no file provided then we do not have to set up the sequence of predetermined blocks
  if (random == true ) { return; }

  // assuming file is provided, load the blocks from the file to the sequence of blocks
  char block;
  infile.open(fileName);
  while( infile >> block ) {
    blocks.emplace_back(block);
  }
}

Block* LevelTwo::nextBlock(int idx) {
  int pos = 0;
  if ( random == true ) {
    blocks.clear();
    blocks = {'J', 'O','I', 'T', 'L', 'Z', 'S'};
    pos = rand() % blocks.size();
  } else {
    pos = idx % blocks.size();
  }

  //Return the corresponding block
  char curBlock = blocks[pos];
  if (curBlock == 'I') return new Iblock{};	
  else if (curBlock == 'O') return new Oblock{};
  else if (curBlock == 'J') return new Jblock{};
	else if (curBlock == 'Z') return new Zblock{};
	else if (curBlock == 'T') return new Tblock{};
	else if (curBlock == 'L') return new Lblock{};
  return new Sblock{};
}


