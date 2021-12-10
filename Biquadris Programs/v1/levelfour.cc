#include <cstdlib>
#include <string>
#include <vector>

#include "levelfour.h"
#include "block.h" // F: need this??

// Constructor & Destructor
LevelFour::LevelFour(string name, bool rand): fileName(name), random(rand), lvl{3}, interval{0} { blocks.clear(); }
LevelFour::~LevelFour() {}

// Accessors
int LevelFour::getLevel() { return lvl; }
bool LevelFour::getRandom() { return random; }
string LevelFour::getFileName() { return fileName; }
int LevelFour::getInterval() { return interval; }

// Other Operations
void LevelFour::setUpLevel() {
  // If there is no file provided then we do not have to set up the sequence of predetermined blocks
  if (random == true ) { return; }

  // assuming file is provided, load the blocks from the file to the sequence of blocks
  char block;
  infile.open(fileName);
  while( infile >> block ) {
    blocks.emplace_back(block);
  }
}

Block* LevelFour::nextBlock(size_t idx) {
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
  //if ((interval % 5 == 0) && interval >= 1) return starBlock{};
  if (blocks[pos] == 'I') return new Iblock{};	
  else if (blocks[pos] == 'O') return new Oblock{};
  else if (blocks[pos] == 'J') return new Jblock{};
	else if (blocks[pos] == 'Z') return new Zblock{};
	else if (blocks[pos] == 'T') return new Tblock{};
	else if (blocks[pos] == 'L') return new Lblock{};
  
  return new Sblock{};
}

void LevelFour::resetInterval() {
  interval = 0;
}

