#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>

#include "abslevel.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "baseboard.h"
#include "textdisplay.h"
//#include "graphics.h"
//#include "commandhandler.h"
//#include "blind.h"
//#include "force.h"
//#include "heavy.h"
#include "block.h"
#include "iBlock.h"

using namespace std;

int main (int argc, char *argv[]) {
  // command line args
  bool textOnly = false;
  int seed = 13;
  string scriptfile1 = "sequence1.txt";
  string scriptfile2 = "sequence2.txt";
  int startLevel = 0;

  // argv[0] is the file name
  // F: WE WILL NEED SOME TRY AND CATCH HERE IF PARAMS ARE NOT VALID
  for (int i = 1; i < argc; i++) {
    string c = argv[i];
    if (c == "-text") { 
      textOnly = true;
    } else if ( c == "-seed" ) {
      seed = atoi(argv[i+1]);
      i++;
    } else if ( c == "-scriptfile1") {
      scriptfile1 = argv[i+1];
      i++;
    } else if ( c == "-scriptfile2") {
      scriptfile2 = argv[i+1];
      i++;
    } else if ( c == "-startlevel") {
      startLevel = atoi(argv[i+1]);
      i++;
    } else {
      cout << "ERROR: CMD LINE ARG IS INVALID: " << c << endl;
    }
  }

  // SETTING UP THE GAME
  BaseBoard* gameBoard1 = new BaseBoard(19, 11, 1, startLevel);
  BaseBoard* gameBoard2 = new BaseBoard(19, 11, 2, startLevel);
  TextDisplay td{11, 19, gameBoard1, gameBoard2};
  // graphcs??

  shared_ptr<AbsBoard> board1(gameBoard1);
  shared_ptr<AbsBoard> board2(gameBoard2);

  gameBoard1->setObservers(&td);
  gameBoard2->setObservers(&td);




}
