#include <string>
#include <iostream>
#include "commandhandler.h"
#include "block.h"
#include "oBlock.h"
#include "iBlock.h"
#include "jBlock.h"
#include "sBlock.h"
#include "tBlock.h"
#include "lBlock.h"
#include "zBlock.h"
#include "abslevel.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"

using namespace std;

// HINT??
int main() {
  CommandHandler ch;
  ch.callCommands("left");
  ch.callCommands("lef");
  ch.callCommands("re");
  ch.callCommands("ra");
  ch.addRename("super", "left");
  ch.callCommands("sup");
  //ch.addMacro("moves");
  //ch.callCommands("+moves");
  ch.callCommands("3ri");
  ch.callCommands("0ri");
  ch.callCommands("1ri");
  ch.callCommands("2rest");
  ch.callCommands("0nora");
  ch.callCommands("3right");

  // testing functions for level
  LevelZero l0 {"biquadris_sequence1.txt"};
  cout << l0.getLevel() << endl;
  cout << l0.getRandom() << endl;
  cout << l0.getFileName() << endl;

  l0.setUpLevel();
  Block* curBlock;
  int counter = 0;
  while (counter < 20 ) {
    curBlock = l0.nextBlock(counter);
    cout << curBlock->getType() << " ";
    counter++;
    delete curBlock;
  }
  cout << "\n";

  LevelOne l1a {"biquadris_sequence1.txt"};
  cout << l1a.getLevel() << endl;
  cout << l1a.getRandom() << endl;
  cout << l1a.getFileName() << endl;
  counter = 0;
  while (counter < 20 ) {
    curBlock = l1a.nextBlock(counter);
    cout << curBlock->getType() << " ";
    counter++;
    delete curBlock;
  }
  cout << "\n";

  LevelOne l1b {};
  cout << l1b.getLevel() << endl;
  cout << l1b.getRandom() << endl;
  cout << l1b.getFileName() << endl;
  counter = 0;
  while (counter < 20 ) {
    curBlock = l1b.nextBlock(counter);
    cout << curBlock->getType() << " ";
    counter++;
    delete curBlock;
  }
  cout << "\n";


  LevelTwo l2a {"biquadris_sequence2.txt"};
  cout << l2a.getLevel() << endl;
  cout << l2a.getRandom() << endl;
  cout << l2a.getFileName() << endl;
  counter = 0;
  while (counter < 20 ) {
    curBlock = l2a.nextBlock(counter);
    cout << curBlock->getType() << " ";
    counter++;
    delete curBlock;
  }
  cout << "\n";

  LevelTwo l2b {};
  cout << l2b.getLevel() << endl;
  cout << l2b.getRandom() << endl;
  cout << l2b.getFileName() << endl;
  counter = 0;
  while (counter < 20 ) {
    curBlock = l2b.nextBlock(counter);
    cout << curBlock->getType() << " ";
    counter++;
    delete curBlock;
  }
  cout << "\n";

  LevelThree l3a {"biquadris_sequence1.txt"};
  cout << l3a.getLevel() << endl;
  cout << l3a.getRandom() << endl;
  cout << l3a.getFileName() << endl;
  counter = 0;
  while (counter < 20 ) {
    curBlock = l3a.nextBlock(counter);
    cout << curBlock->getType() << " ";
    counter++;
    delete curBlock;
  }
  cout << "\n";

  LevelThree l3b {};
  cout << l3b.getLevel() << endl;
  cout << l3b.getRandom() << endl;
  cout << l3b.getFileName() << endl;
  counter = 0;
  while (counter < 20 ) {
    curBlock = l3b.nextBlock(counter);
    cout << curBlock->getType() << " ";
    counter++;
    delete curBlock;
  }
  cout << "\n";


  LevelFour l4a {"biquadris_sequence1.txt"};
  cout << l4a.getLevel() << endl;
  cout << l4a.getRandom() << endl;
  cout << l4a.getFileName() << endl;
  counter = 0;
  while (counter < 20 ) {
    curBlock = l4a.nextBlock(counter);
    cout << curBlock->getType() << " ";
    counter++;
    delete curBlock;
  }
  cout << "\n";

  LevelFour l4b {};
  cout << l4b.getLevel() << endl;
  cout << l4b.getRandom() << endl;
  cout << l4b.getFileName() << endl;
  counter = 0;
  while (counter < 20 ) {
    curBlock = l4b.nextBlock(counter);
    cout << curBlock->getType() << " ";
    counter++;
    delete curBlock;
  }
  cout << "\n";

}