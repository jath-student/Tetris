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
#include "commandhandler.h"

using namespace std;

int main (int argc, char *argv[]) {
  //cout << "checkpt 1" << endl;
  // command line args
  bool textOnly = false;
  bool scriptF1 = false;
  bool scriptF2 = false;
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
      scriptF1 = true;
      scriptfile1 = argv[i+1];
      i++;
    } else if ( c == "-scriptfile2") {
      scriptF2 = true;
      scriptfile2 = argv[i+1];
      i++;
    } else if ( c == "-startlevel") {
      startLevel = atoi(argv[i+1]);
      i++;
    } else {
      cout << "ERROR: CMD LINE ARG IS INVALID: " << c << endl;
    }
  }
  //cout << "checkpt 2" << endl;

  // SETTING UP THE GAME
  //BaseBoard *game;
  //cout << "checkpt 3" << endl;
  
  BaseBoard *gameBoard1 = new BaseBoard(18, 11, 1, startLevel);
  BaseBoard* gameBoard2 = new BaseBoard(18, 11, 2, startLevel);
  TextDisplay td{11, 18, gameBoard1, gameBoard2};
  // graphcs??

  CommandHandler ch{};
  //cout << "checkpt 5" << endl;
  shared_ptr<AbsBoard> board1(gameBoard1);
  shared_ptr<AbsBoard> board2(gameBoard2);
  gameBoard1->setObservers(&td);
  gameBoard2->setObservers(&td);
  int p1CurLvl = startLevel;
  int p2CurLvl = startLevel;
  int p1NextLvl = startLevel;
  int p2NextLvl = startLevel;

  //cout << "checkpt 8" << endl;
  

  string command = "";

  if ( startLevel == 0 ) {
    gameBoard1->setCurrentLevel(startLevel, false, scriptfile1);
    gameBoard2->setCurrentLevel(startLevel, false, scriptfile2);

    gameBoard1->getCurrentLevel()->setUpLevel();
    gameBoard2->getCurrentLevel()->setUpLevel();

    //cout << gameBoard1->getCurrentLevel()->getLevel() << endl;
    //cout << gameBoard1->getCurrentLevel()->getFileName() << endl;
    //cout << scriptfile2 << endl;
  }

  /*if (scriptF1 == true) {
    gameBoard1->setCurrentLevel(startLevel, false, scriptfile1);
  } else {
    gameBoard1->setCurrentLevel(startLevel, true, scriptfile1);
  }

  if (scriptF2 == true) {
    gameBoard1->setCurrentLevel(startLevel, false, scriptfile1);
  } else {
    gameBoard1->setCurrentLevel(startLevel, true, scriptfile1);
  }*/

  // IF GRAPHICS IS ON CREATE THAT
  if (!textOnly) { }

  //AbsLevel* curLvl1 = (gameBoard1->getCurrentLevel());
  //AbsLevel* curLvl2 = (gameBoard2->getCurrentLevel());
  //cout << "checkpt 10" << endl;
  //cout << gameBoard1->getCurrentLevel()->getFileName();
  //cout << "checkpt 10b" << endl;
  
  gameBoard1->setCurrentBlock((gameBoard1->getCurrentLevel())->nextBlock(0));
  //cout << "checkpt 11" << endl;
  gameBoard1->setNextBlock((gameBoard1->getCurrentLevel())->nextBlock(1));
  //cout << "checkpt 13" << endl;
  gameBoard2->setCurrentBlock(gameBoard2->getCurrentLevel()->nextBlock(0));
  gameBoard2->setNextBlock(gameBoard2->getCurrentLevel()->nextBlock(1));

  //cout << "checkpt 13" << endl;

  gameBoard1->doMove(0, 0, 0);
  gameBoard2->doMove(0, 0, 0);

  command = "-1";
  int mult = 1;
  int counter = 2;
  int j = 1;
  bool gameOver = false;
  BaseBoard* activeBoard;
  int tTurns = 0;
  int p1NxtBlock = 2;
  int p2NxtBlock = 2;
  int dropCounter = 0;
  while (true) {
    // Determine which player is moving
    (tTurns % 2 == 0) ? activeBoard = gameBoard1 : activeBoard = gameBoard2;
    while( (command == "" || command == "-2" || command == "-1") && dropCounter == 0) {
      cout << "Enter your command: \n";
      cin >> command;
      mult = ch.extractMultiplier(command);
      command = ch.callCommands(command);
      if (command == "restart" || command == "hint" || command == "norandom" || command == "random") { mult = 1; }
      if (command == "drop") { dropCounter = mult; mult = 1; }
    }
    
    if (command == "right") {
      while (activeBoard->validMove(1, 0, 0) && mult > 0) {
        activeBoard->doMove(1, 0, 0);
        mult--;
      }
    } else if (command == "left") {
      while (activeBoard->validMove(-1, 0, 0) && mult > 0) {
        activeBoard->doMove(-1, 0, 0);
        mult--;
      }
    } else if (command == "down") {
      while (activeBoard->validMove(0, 1, 0) && mult > 0) {
        activeBoard->doMove(0, 1, 0);
        mult--;
      }

    } else if (command == "drop") {
      while (activeBoard->validMove(0, 1, 0)) {
        activeBoard->doMove(0, 1, 0);
      }
      if (activeBoard->gameOver()) { gameOver = true; dropCounter = 0; break;} else {
        activeBoard->addPlacedBlk();
        activeBoard->clearedLines();
        activeBoard->setCurrentBlock((activeBoard->getNextBlock()));
        activeBoard->setNextBlock((activeBoard->getCurrentLevel())->nextBlock( 
          (activeBoard->getPlayer() == 1) ? p1NxtBlock : p2NxtBlock ));
        activeBoard->doMove(0, 0, 0);
        (activeBoard->getPlayer() == 1) ? p1NxtBlock++ : p2NxtBlock++;
        dropCounter--;
      }
      // setting new highscore
      if (activeBoard == gameBoard1 && activeBoard->getHighScore() > gameBoard2->getHighScore()) {
        gameBoard2->setHighScore(activeBoard->getHighScore());
      } else if (activeBoard == gameBoard2 && activeBoard->getHighScore() > gameBoard1->getHighScore()) {
        gameBoard1->setHighScore(activeBoard->getHighScore());
      }
    } else if (command == "counterclockwise") {
      while (activeBoard->validMove(0, 0, -1) && mult > 0) {
        activeBoard->doMove(0, 0, -1);
        mult--;
      }
    } else if (command == "clockwise") {
      while (activeBoard->validMove(0, 0, 1) && mult > 0) {
        activeBoard->doMove(0, 0, 1);
        mult--;
      }
    } else if (command == "restart") {
      activeBoard->reset();
      activeBoard->setCurrentBlock((activeBoard->getCurrentLevel())->nextBlock(0));
      activeBoard->setNextBlock((activeBoard->getCurrentLevel())->nextBlock(1));
      activeBoard->doMove(0, 0, 0);
    } else if ( command == "S" ) {
      if (activeBoard->fitBlock('S')) {
        int xCoord = (activeBoard->getCurrentBlock())->getX();
        int yCoord = (activeBoard->getCurrentBlock())->getY();
        delete activeBoard->getCurrentBlock();
        Block* newBlock = new Sblock();
        activeBoard->setCurrentBlock(newBlock);
        activeBoard->doMove(xCoord, yCoord, 0);
      }
    } else if ( command == "Z" ) {
      if (activeBoard->fitBlock('Z')) {
        int xCoord = (activeBoard->getCurrentBlock())->getX();
        int yCoord = (activeBoard->getCurrentBlock())->getY();
        delete activeBoard->getCurrentBlock();
        Block* newBlock = new Zblock();
        activeBoard->setCurrentBlock(newBlock);
        activeBoard->doMove(xCoord, yCoord, 0);
      }
    } else if ( command == "O" ) {
      if (activeBoard->fitBlock('O')) {
        int xCoord = (activeBoard->getCurrentBlock())->getX();
        int yCoord = (activeBoard->getCurrentBlock())->getY();
        delete activeBoard->getCurrentBlock();
        Block* newBlock = new Oblock();
        activeBoard->setCurrentBlock(newBlock);
        activeBoard->doMove(xCoord, yCoord, 0);
      }
    } else if ( command == "L" ) {
      if (activeBoard->fitBlock('L')) {
        int xCoord = (activeBoard->getCurrentBlock())->getX();
        int yCoord = (activeBoard->getCurrentBlock())->getY();
        delete activeBoard->getCurrentBlock();
        Block* newBlock = new Lblock();
        activeBoard->setCurrentBlock(newBlock);
        activeBoard->doMove(xCoord, yCoord, 0);
      }
    } else if ( command == "J" ) {
      if (activeBoard->fitBlock('J')) {
        int xCoord = (activeBoard->getCurrentBlock())->getX();
        int yCoord = (activeBoard->getCurrentBlock())->getY();
        delete activeBoard->getCurrentBlock();
        Block* newBlock = new Jblock();
        activeBoard->setCurrentBlock(newBlock);
        activeBoard->doMove(xCoord, yCoord, 0);
      }
    } else if ( command == "I" ) {
      if (activeBoard->fitBlock('I')) {
        int xCoord = (activeBoard->getCurrentBlock())->getX();
        int yCoord = (activeBoard->getCurrentBlock())->getY();
        delete activeBoard->getCurrentBlock();
        Block* newBlock = new Iblock();
        activeBoard->setCurrentBlock(newBlock);
        activeBoard->doMove(xCoord, yCoord, 0);
      }
      
    } else if ( command == "T" ) {
      if (activeBoard->fitBlock('T')) {
        int xCoord = (activeBoard->getCurrentBlock())->getX();
        int yCoord = (activeBoard->getCurrentBlock())->getY();
        delete activeBoard->getCurrentBlock();
        Block* newBlock = new Tblock();
        activeBoard->setCurrentBlock(newBlock);
        activeBoard->doMove(xCoord, yCoord, 0);
      }   
    }
    mult = 1;
    if (dropCounter == 0 && command == "drop" ) { tTurns++; command = "-1"; }  
    cout << td;
  }

  if (gameOver) {
    cout << "\n\n********************** GAME OVER **********************\n\t\t     ";
    int player = activeBoard->getPlayer();
    player == 1 ? cout << "Player 2 wins.\n" : cout << "Player 1 wins.\n";
    cout << "**********************           **********************" << endl;
  }
  //gameBoard2->reset();
  //gameBoard1->reset();
}
