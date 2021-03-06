#include <cstdlib>
#include <string>
#include <vector>

#include "levelfour.h"
#include "block.h"

// Constructor & Destructor
LevelFour::LevelFour(string name, bool rand): lvl{4}, interval{0}, fileName{name}, random{rand} { /*blocks.clear();*/ }
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

Block* LevelFour::nextBlock(int idx) {
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
  if ((interval % 5 == 0) && interval >= 1) return new starblock{};
  if (curBlock == 'I') return new Iblock{};	
  else if (curBlock == 'O') return new Oblock{};
  else if (curBlock == 'J') return new Jblock{};
	else if (curBlock == 'Z') return new Zblock{};
	else if (curBlock == 'T') return new Tblock{};
	else if (curBlock == 'L') return new Lblock{};
  
  return new Sblock{};
}

void LevelFour::resetInterval() {
  interval = 0;
}

