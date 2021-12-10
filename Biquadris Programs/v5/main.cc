#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>

#include "abslevel.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "baseboard.h"
#include "textdisplay.h"
#include "forcefx.h"
#include "blindfx.h"
#include "heavyfx.h"
//#include "graphics.h"
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
  //vector<string> sequenceCmdsp1;
  //vector<string> sequenceCmdsp2;
 //bool usingSequencep1 = false;
  //bool usingSequencep2 = false;

  string command = "";
  //string inputFile = "";
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
  int dropCounter = 1;
  bool noRandom1 = false;
  bool noRandom2 = false;
  string spawnEffect = "";
  string inputFile;
  while (true) {
    // Determine which player is moving
    (tTurns % 2 == 0) ? activeBoard = gameBoard1 : activeBoard = gameBoard2;
    //int activePlayer = activeBoard->getPlayer();
    //bool activeSeq = activeBoard->getPlayer() == 1 ? usingSequencep1 : usingSequencep2;
    if (command != "drop" ) {
      while( (command == "" || command == "-2" || command == "-1")) {
        dropCounter = 1;
        //if (activeSeq != true) {
          cout << "Enter your command: \n";
          cin >> command;
        //} else if (activePlayer == 1) {
        //  if (sequenceCmdsp1.empty()) {
        //    cin >> command;
        //    usingSequencep1 = false;
        //    activeSeq = false;
        //  } else {
         //   command = sequenceCmdsp1.back();
         //   sequenceCmdsp1.pop_back();
          //}
       // } else {
       //   if (sequenceCmdsp2.empty()) {
        //    cin >> command;
         //   usingSequencep2 = false;
         //   activeSeq = false;
         // } else {
         //   command = sequenceCmdsp2.back();
        //    sequenceCmdsp2.pop_back();
         // }
       // }
        if (cin.eof()) { return 0; }
        mult = ch.extractMultiplier(command);
        command = ch.callCommands(command);
        if (command == "restart" || command == "hint" || command == "norandom" || command == "random") { mult = 1; }
        if (command == "drop") { dropCounter = mult; mult = 1; }
      }
    }
    //cout << dropCounter << "dropCounter";
    if (command == "right") {
      while (activeBoard->validMove(1, 0, 0) && mult > 0) {
        activeBoard->doMove(1, 0, 0);
        mult--;
      }
      //cout << "done right";
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

      if (activeBoard->getLevel() == 4 ) {
        int intrvl = (static_cast<LevelFour*>(activeBoard->getCurrentLevel()))->getInterval();
         
        if (intrvl % 5 == 0 && intrvl > 0) { 
          cout << "WEE GOT A STAR BLOCK\n" ;
          static_cast<LevelFour*>(activeBoard->getCurrentLevel())->resetInterval();
          Block* currentTemp = activeBoard->getCurrentBlock(); // store current block in a temp variable
          activeBoard->setCurrentBlock(activeBoard->getNextBlock()); // set current block to star block
          activeBoard->setNextBlock((activeBoard->getCurrentLevel())->nextBlock( // set nextBlock to block after star
            (activeBoard->getPlayer() == 1) ? p1NxtBlock : p2NxtBlock ));
          activeBoard->doMove(5, 0, 0); // move star to center
          while(activeBoard->validMove(0, 1, 0)) { // move star down as much as possible
            activeBoard->doMove(0, 1, 0);
          }
          if (activeBoard->gameOver()) { gameOver = true; dropCounter = 0; break;} else {
            activeBoard->addPlacedBlk();
            activeBoard->clearedLines();
            activeBoard->setCurrentBlock(currentTemp);
            activeBoard->doMove(0, 0, 0);
          }
        }
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
    } else if ( command == "S" || command == "Z" || command == "T" || command == "O" ||
                command == "L" || command == "J" || command == "I") {
      if (activeBoard->fitBlock(command[0])) {
        Block* newBlock = ch.getForceBlock( activeBoard->getLevel() > 2 ? false : true,
                                             command[0] );
        int xCoord = (activeBoard->getCurrentBlock())->getX();
        int yCoord = (activeBoard->getCurrentBlock())->getY();
        delete activeBoard->getCurrentBlock();
        activeBoard->setCurrentBlock(newBlock);
        activeBoard->doMove(xCoord, yCoord, 0);
      }
    } else if (command == "levelup") {
      int currentLevel = activeBoard->getLevel();
     /* if (activeBoard->getPlayer() == 1 && noRandom1 == true && currentLevel == 3) { // keep noRandom property while transitioning from level 4 to 3
        activeBoard->setCurrentLevel(4, false, scriptfile1); // Set random blocks to default
        activeBoard->getCurrentLevel()->setUpLevel();
      } else if (activeBoard->getPlayer() == 2 && noRandom2 == true && currentLevel == 3) {
        activeBoard->setCurrentLevel(4, false, scriptfile2); // Set random blocks to default
        activeBoard->getCurrentLevel()->setUpLevel();
      } else {*/
        if (currentLevel != 4) {
          for (int m = 0; m < mult && currentLevel < 4; m++) {
            currentLevel++;
          }
          activeBoard->setCurrentLevel(currentLevel, true, ""); // Set random blocks to default
          activeBoard->getCurrentLevel()->setUpLevel();
          if (activeBoard->getPlayer() == 1) { p1NxtBlock = 0; }
          else { p2NxtBlock = 0; }
        }
     // }
    } else if (command == "leveldown") {
      int currentLevel = activeBoard->getLevel();
     /* if (activeBoard->getPlayer() == 1 && noRandom1 == true && mult == 1 && currentLevel == 4) { // keep noRandom property while transitioning from level 4 to 3
        activeBoard->setCurrentLevel(3, false, scriptfile2); // Set random blocks to default
        activeBoard->getCurrentLevel()->setUpLevel();
      } else if (activeBoard->getPlayer() == 2 && noRandom2 == true && mult == 1 && currentLevel == 4) {
        activeBoard->setCurrentLevel(3, false, scriptfile2); // Set random blocks to default
        activeBoard->getCurrentLevel()->setUpLevel();
      } else {*/
        if (currentLevel != 0) { 
          for (int m = mult; m > 0 && currentLevel > 0; m--) {
            currentLevel--;
          }
          if (activeBoard->getPlayer() == 1) { 
            p1NxtBlock = 0;
            currentLevel == 0 ? inputFile = scriptfile1 : inputFile = "";
          } else { 
            p2NxtBlock = 0;
            currentLevel == 0 ? inputFile = scriptfile2 : inputFile = "";
          }
          activeBoard->setCurrentLevel(currentLevel, false, inputFile); // Set random blocks to default
          activeBoard->getCurrentLevel()->setUpLevel();
        }
      //}
    }
   /* } else if (command == "sequence") {
      cin >> inputFile;
      ifstream fileExists(inputFile);
      string temp = "";
      if (fileExists.good()) {
        if (activePlayer == 1) {
          sequenceCmdsp1.clear();
          while (fileExists >> temp) {
            sequenceCmdsp1.insert(sequenceCmdsp1.begin(), temp);
          }
          usingSequencep1 = true;
        } else {
          sequenceCmdsp1.clear();
          while (fileExists >> temp) {
            sequenceCmdsp2.insert(sequenceCmdsp2.begin(), temp);
          }
          usingSequencep2 = true;
        }
      } else {
        cout << "INVALID INPUT: The file you have specified does not exist.\n";
      }*/
    /*} else if (command == "norandom") {
      if (activeBoard->getLevel() == 3 || activeBoard->getLevel() == 4) {
        cin >> inputFile;
        ifstream fileExists(inputFile);
        if (fileExists.good()) {
          activeBoard->setCurrentLevel(activeBoard->getLevel(), false, inputFile);
          activeBoard->getCurrentLevel()->setUpLevel();

          if (activePlayer == 1) {
            noRandom1 = true;
            p1NxtBlock = 0;
            scriptfile1 = inputFile;
          } else {
            noRandom2 = true;
            p2NxtBlock = 0;
            scriptfile2 = inputFile;
          }
        } else {
          cout << "INVALID INPUT: The file you have specified does not exist.\n";
        }
      }
    } else if (command == "random") {
      bool noRandom = activeBoard->getPlayer() == 1 ? noRandom1 : noRandom2;
      if ((activeBoard->getLevel() == 3 || activeBoard->getLevel() == 4) && noRandom == true) {
        activeBoard->setCurrentLevel(activeBoard->getLevel(), true, "");
        activeBoard->getCurrentLevel()->setUpLevel();
      }
    }*/
    
    //cout << "the spawn effect is "; 
    activeBoard->getSpawnEffect() == true ? cout << "true\n" : cout <<"false\n";
    // Check if should spawn effect on opponent
    if (activeBoard->getSpawnEffect()) {
      cout << td;
      string cmd;
      spawnEffect = ch.callEffectCmd("x");
      if (spawnEffect == "Force") {
        char forceBlk = ch.forceEffectBlock('x');
        if (activeBoard->getPlayer() == 1) {
          gameBoard2->setForce(true);
          board2.reset(new ForceFX{board2, forceBlk});
          board2->updateBoard(*gameBoard2);
          if(gameBoard2->getLost()) { 
            gameOver = true; 
            activeBoard = gameBoard2; 
            break;
          }
        } else {
          gameBoard1->setForce(true);
          board1.reset(new ForceFX{board1, forceBlk});
          board1->updateBoard(*gameBoard1);
          if(gameBoard1->getLost()) { 
            gameOver = true; 
            activeBoard = gameBoard1; 
            break;
          }
        }
      } else if (spawnEffect == "Heavy") {
        if (activeBoard->getPlayer() == 1) {
          gameBoard2->setHeavy(true);
          board2.reset(new HeavyFX{board2});
          board2->updateBoard(*gameBoard2);
        } else {
          gameBoard1->setHeavy(true);
          board1.reset(new HeavyFX{board1});
          board1->updateBoard(*gameBoard1);
        }

      } else if (spawnEffect == "Blind") {
        if (activeBoard->getPlayer() == 1) {
          gameBoard2->setBlind(true);

          board2.reset(new BlindFX{board2});
          board2->updateBoard(*gameBoard2);
        } else {
          gameBoard1->setBlind(true);
          board1.reset(new BlindFX{board1});
          board1->updateBoard(*gameBoard1);
        }
      }
    }

    vector<string> moveCommands = {"right", "left", "down", "clockwise", "counterclockwise"};
    auto checkMove = find(moveCommands.begin(), moveCommands.end(), command);

    if (activeBoard->getHeavy() && command.length() != 1 && checkMove != moveCommands.end()) {
      if(activeBoard->validMove(0, 1, 0)) {
        activeBoard->doMove(0, 1, 0);
      }
      if (activeBoard->validMove(0, 1, 0)) {
        activeBoard->doMove(0, 1, 0);
      }
    }

    if ((activeBoard->getCurrentBlock())->blockIsHeavy() && checkMove != moveCommands.end()) {
      if(activeBoard->validMove(0, 1, 0)) {
        activeBoard->doMove(0, 1, 0);
      }
    }

    mult = 1;
    if (gameOver) break;
    
    // Turning off variables associated with special effects
    if (command == "drop" && activeBoard->getHeavy()) { activeBoard->setHeavy(false); }
    if (command == "drop" && activeBoard->getBlind()) { activeBoard->setBlind(false); }
    if (command == "drop" && activeBoard->getForce()) { activeBoard->setForce(false); }
    if (command == "drop" && activeBoard->getSpawnEffect()) { activeBoard->setSpawnEffect(false); }


    if (dropCounter == 0 && command == "drop" ) { 
      tTurns++; command = "-1"; 
    } else if (command != "drop" && dropCounter > 0) {
      command = "-1";
    }  
    
    cout << td;
  }

  if (gameOver) {
    cout << "\n\n********************** GAME OVER **********************\n\t\t     ";
    int player = activeBoard->getPlayer();
    player == 1 ? cout << "Player 2 wins.\n" : cout << "Player 1 wins.\n";
    cout << "**********************           **********************" << endl;
  }
}
