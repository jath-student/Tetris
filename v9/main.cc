#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>
#include <stdlib.h>

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
#include "graphicsdisplay.h"
#include "window.h"
#include "block.h"
#include "commandhandler.h"

using namespace std;

int main (int argc, char *argv[]) {

  // Setting defaults to possible command line arguments
  bool textOnly = false; // Determines if game is run in text-only mode
  bool scriptF1 = false; // Determines if a special scriptfile is being used for player 1
  bool scriptF2 = false; // Determines if a special scriptfile is being used for player 2
  string scriptfile1 = "sequence1.txt";  // Current scriptfile for player 1
  string scriptfile2 = "sequence2.txt"; // Current scriptfile for player 2
  int startLevel = 0; // Current start level
  srand(1317); // setting initial seed

  // Applying command-line specified flags if available, argv[0] is the file name, so we start loop at index 1
  for (int i = 1; i < argc; i++) {
    string c = argv[i];
    if (c == "-text") { 
      textOnly = true;
    } else if ( c == "-seed" ) {
      try {
        if (i + 1 >= argc) {
         cerr << "Error: Invalid use of -seed.\n" << endl;
         return 1;
        }
        int seed = atoi(argv[i+1]);
        srand(seed);
      } catch (...) {
        cerr << "Error: cannot be converted to a valid seed.\n" << endl;
        return 1;
      }
      i++;
    } else if ( c == "-scriptfile1") {
      scriptF1 = true;
      if (i + 1 >= argc) {
        cerr << "Error: Invalid use of -scriptfile1.\n" << endl;
        return 1;
      }
      scriptfile1 = argv[i+1];
      ifstream openFile(scriptfile2);
      if (!openFile.good()) {
        cerr << "Error: scriptfile 1 is invalid.\n" << endl;
        return 1;
      }
      i++;
    } else if ( c == "-scriptfile2") {
      scriptF2 = true;
      if (i + 1 >= argc) {
        cerr << "Error: Invalid use of -scriptfile2.\n" << endl;
        return 1;
      }
      scriptfile2 = argv[i+1];
      ifstream openFile(scriptfile1);
      if (!openFile.good()) {
        cerr << "Error: scriptfile 2 is invalid.\n" << endl;
        return 1;
      }
      i++;
    } else if ( c == "-startlevel") {
      try {
        if (i + 1 >= argc) {
        cerr << "Error: Invalid use of -startlevel.\n" << endl;
        return 1;
        }
        startLevel = atoi(argv[i+1]);
      } catch (...) {
        cerr << "Error: cannot be converted to a valid level.\n" << endl;
        return 1;
      }
      if (startLevel > 4) { startLevel = 4; cout << "Setting level to max level 4.\n";}
      else if (startLevel < 0) {startLevel = 0; cout << "Setting level to min level 1.\n"; }
      i++;
    } else {
      cerr << "Error: Invalid command line argument: " << c << endl;
      return 1;
    }
  }
   
  // Initializing two gameboards, textdisplay, and graphics
  BaseBoard *gameBoard1 = new BaseBoard(18, 11, 1, startLevel);
  BaseBoard *gameBoard2 = new BaseBoard(18, 11, 2, startLevel);
  TextDisplay td{11, 18, gameBoard1, gameBoard2};
  GraphicsDisplay* gd;
  

  CommandHandler ch{};
  shared_ptr<AbsBoard> board1(gameBoard1);
  shared_ptr<AbsBoard> board2(gameBoard2);
  gameBoard1->setObservers(&td);
  gameBoard2->setObservers(&td);

  // Setting up initial levels specified by cmd-line flags or default level 0
  gameBoard1->setCurrentLevel(startLevel, !scriptF1, scriptfile1);
  gameBoard2->setCurrentLevel(startLevel, !scriptF2, scriptfile2);

  gameBoard1->getCurrentLevel()->setUpLevel();
  gameBoard2->getCurrentLevel()->setUpLevel();

  // Turns on graphics if available
  if (!textOnly) { 
    gd = new GraphicsDisplay{gameBoard1, gameBoard2};
    gameBoard1->setObservers(gd);
    gameBoard2->setObservers(gd);
  }

  // creating and setting up the very first two blocks to have on each board respectively
  gameBoard1->setCurrentBlock((gameBoard1->getCurrentLevel())->nextBlock(0));
  gameBoard1->setNextBlock((gameBoard1->getCurrentLevel())->nextBlock(1));
  gameBoard2->setCurrentBlock(gameBoard2->getCurrentLevel()->nextBlock(0));
  gameBoard2->setNextBlock(gameBoard2->getCurrentLevel()->nextBlock(1));

  // Moving first two blocks onto each board
  gameBoard1->doMove(0, 0, 0);
  gameBoard2->doMove(0, 0, 0);


  // The Game Variables

  BaseBoard* activeBoard; // Pointer to active Game Board

  const int width = gameBoard2->getWidth(); // width of Game Board
  const int height = gameBoard2->getHeight(); // height of Game Board
  int tTurns = 0; // Keeps track of which player is the active player
  int p1NxtBlock = 2; // Keeps track of the next block to add during player 1 turn
  int p2NxtBlock = 2; // Keeps track of the next block to add during player 2 turn
  int dropCounter = 1; // Keeps track of how many blocks to drop during active player's turn
  int activePlayer = 1; // The current active player
  int mult = 1; // Keeps track of current multiplier for commands

  string spawnEffect = ""; // Determines the spawn effect
  string inputFile = ""; // Holds input files
  string command = "-1"; // Holds current command
  
  vector<string> sequenceCmdsp1; // Holds sequence of commands for player 1
  vector<string> sequenceCmdsp2; // Holds sequence of commands for player 2

  bool gameOver = false; // Tracks if game is over
  bool usingSequencep1 = false; // Tracks if player 1 is using commands from a sequence
  bool usingSequencep2 = false; // Tracks if player 2 is using commands from a sequence
  bool activeSeq; // Determines if the active player is using commands from a sequence
  bool noRandom1 = false; // Determines if norandom command is active for player 1
  bool noRandom2 = false; // Determines if random command is active for player 2
  bool noRandom = false; // Determines if active player has no random activated

  cout << td;
  // The Game Loop
  while (true) {
    // Determine which player is moving
    (tTurns % 2 == 0) ? activeBoard = gameBoard1 : activeBoard = gameBoard2;
    activePlayer = activeBoard->getPlayer();
    activePlayer == 1 ? activeSeq = usingSequencep1 : activeSeq = usingSequencep2;
    activePlayer == 1 ? noRandom = noRandom1 : noRandom = noRandom2;

    if (command != "drop") {
      while( (command == "" || command == "-2" || command == "-1")) {
        dropCounter = 1;

        if (!activeSeq) {
          cout << "Enter your command: \n";
          cin >> command;
        } else if (activePlayer == 1) {
          if (sequenceCmdsp1.empty()) {
            cin >> command;
            usingSequencep1 = false;
            activeSeq = false;
          } else {
            command = sequenceCmdsp1.back();
            sequenceCmdsp1.pop_back();
          }
        } else {
          if (sequenceCmdsp2.empty()) {
            cin >> command;
            usingSequencep2 = false;
            activeSeq = false;
          } else {
            command = sequenceCmdsp2.back();
            sequenceCmdsp2.pop_back();
          }
        }
        
        if (cin.eof()) { return 0; }
        mult = ch.extractMultiplier(command);
        command = ch.callCommands(command);
        if (command == "restart" || command == "hint" || command == "norandom" || command == "random") { mult = 1; }
        if (command == "drop") { dropCounter = mult; mult = 1; }
      }
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
          (activePlayer == 1) ? p1NxtBlock : p2NxtBlock ));
        activeBoard->doMove(0, 0, 0);
        (activePlayer == 1) ? p1NxtBlock++ : p2NxtBlock++;
        dropCounter--;
      }

      if (activeBoard->getLevel() == 4 ) {
        int intrvl = (static_cast<LevelFour*>(activeBoard->getCurrentLevel()))->getInterval();
        if (intrvl % 5 == 0 && intrvl > 0) { 
          static_cast<LevelFour*>(activeBoard->getCurrentLevel())->resetInterval();
          Block* currentTemp = activeBoard->getCurrentBlock(); // store current block in a temp variable
          activeBoard->setCurrentBlock(activeBoard->getNextBlock()); // set current block to star block
          activeBoard->setNextBlock((activeBoard->getCurrentLevel())->nextBlock( // set nextBlock to block after star
            (activePlayer == 1) ? p1NxtBlock : p2NxtBlock ));
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
        Block* newBlock = ch.getForceBlock( activeBoard->getLevel() > 2 ? true : false,
                                             command[0] );
        int xCoord = (activeBoard->getCurrentBlock())->getX();
        int yCoord = (activeBoard->getCurrentBlock())->getY();
        delete activeBoard->getCurrentBlock();
        activeBoard->setCurrentBlock(newBlock);
        activeBoard->doMove(xCoord, yCoord, 0);
      }
    } else if (command == "levelup") {
      int currentLevel = activeBoard->getLevel();
      int setLvl = mult + currentLevel > 3 ? 4 : 3;
      if (activePlayer == 1 && noRandom1 == true && currentLevel + mult >= 3) { // keep noRandom property while transitioning from level 4 to 3
        activeBoard->setCurrentLevel(setLvl, false, scriptfile1); // Set random blocks to default
        activeBoard->getCurrentLevel()->setUpLevel();
      } else if (activePlayer == 2 && noRandom2 == true && currentLevel + mult >= 3) {
        activeBoard->setCurrentLevel(setLvl, false, scriptfile2); // Set random blocks to default
        activeBoard->getCurrentLevel()->setUpLevel();
      } else {
        if (currentLevel != 4) {
          for (int m = 0; m < mult && currentLevel < 4; m++) {
            currentLevel++;
          }
          activeBoard->setCurrentLevel(currentLevel, true, ""); // Set random blocks to default
          activeBoard->getCurrentLevel()->setUpLevel();
          if (activePlayer == 1) { p1NxtBlock = 0; }
          else { p2NxtBlock = 0; }
        }
      }
    } else if (command == "leveldown") {
      int currentLevel = activeBoard->getLevel();
      if (activePlayer == 1 && noRandom1 == true && mult == 1 && currentLevel == 4) { // keep noRandom property while transitioning from level 4 to 3
        activeBoard->setCurrentLevel(3, false, scriptfile1); // Set random blocks to default
        activeBoard->getCurrentLevel()->setUpLevel();
      } else if (activePlayer == 2 && noRandom2 == true && mult == 1 && currentLevel == 4) {
        activeBoard->setCurrentLevel(3, false, scriptfile2); // Set random blocks to default
        activeBoard->getCurrentLevel()->setUpLevel();
      } else {
        if (currentLevel != 0) { 
          for (int m = mult; m > 0 && currentLevel > 0; m--) {
            currentLevel--;
          }
          if (activePlayer == 1) { 
            p1NxtBlock = 0;
            currentLevel == 0 ? inputFile = scriptF1 : inputFile = "";
          } else { 
            p2NxtBlock = 0;
            currentLevel == 0 ? inputFile = scriptF2 : inputFile = "";
          }
          activeBoard->setCurrentLevel(currentLevel, true, inputFile); // Set random blocks to default
          activeBoard->getCurrentLevel()->setUpLevel();
        }
      }
    } else if (command == "sequence") {
      cin >> inputFile;
      ifstream theFile(inputFile);
      string temp;
      if (theFile.good()) {
        if (activePlayer == 1) {
          sequenceCmdsp1.clear();
          while (theFile >> temp) {
            sequenceCmdsp1.insert(sequenceCmdsp1.begin(), temp);
          }
          usingSequencep1 = true;
        } else {
          sequenceCmdsp2.clear();
          while (theFile >> temp) {
            sequenceCmdsp2.insert(sequenceCmdsp2.begin(), temp);
          }
          usingSequencep2 = true;
        }
      } else {
        cout << "INVALID INPUT: The file you have specified does not exist.\n";
      }
    } else if (command == "norandom") {
      if (activeBoard->getLevel() == 3 || activeBoard->getLevel() == 4) {
        cin >> inputFile;
        ifstream theFile(inputFile);
        if (theFile.good()) {
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
      if ((activeBoard->getLevel() == 3 || activeBoard->getLevel() == 4) && noRandom == true) {
        activeBoard->setCurrentLevel(activeBoard->getLevel(), true, "");
        activeBoard->getCurrentLevel()->setUpLevel();
        activePlayer == 1 ? noRandom1 = false : noRandom2 = false;
      }
    } else if (command == "rename") {
      string original, renameCommand;
      cin >> original;
      cin >> renameCommand;
      ch.addRename(renameCommand, original);
    } else if (command == "hint") {
      bool movedBlk = false;
      int curY = activeBoard->getCurrentBlock()->getY();
      for (int i = 0; i < width && movedBlk == false; i++) {
        for (int j = 0; j < height && movedBlk == false; j++) {
          for (int k = 0; k < 4 && movedBlk == false; k++) {
            if ( !(i == 0 && j == 0 && k == 0) && (curY + j) >= 3  && activeBoard->validMove(i, j, k) ) {
              activeBoard->doMove(i, j, k);
              while (activeBoard->validMove(0, 1, 0)) {
                activeBoard->doMove(0, 1, 0);
              }
              movedBlk = true;
            }
          }
        }
      }
      if (activeBoard->gameOver()) { gameOver = true; break; }
      if (!activeBoard->validMove(0, 1, 0)) { command = "drop"; dropCounter = 1;}
    } else if (command == "stopgame") {
      cout << "Thanks for playing! Enter text to close the game.\n";
      if (!textOnly) { gd->printGameOver(-1); }
      string stopGame;
      cin >> stopGame;
      if (!textOnly) { delete gd;}
      return 0;
    }
    if (gameOver) break;

    // Check if spawn effect should be applied on opponent
    if (activeBoard->getSpawnEffect()) {
      cout << td;
      string cmd;
      spawnEffect = ch.callEffectCmd("x");
      if (spawnEffect == "Force") {
        char forceBlk = ch.forceEffectBlock('x');
        if (activePlayer == 1) {
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
        if (activePlayer == 1) {
          gameBoard2->setHeavy(true);
          board2.reset(new HeavyFX{board2});
          board2->updateBoard(*gameBoard2);
        } else {
          gameBoard1->setHeavy(true);
          board1.reset(new HeavyFX{board1});
          board1->updateBoard(*gameBoard1);
        }

      } else if (spawnEffect == "Blind") {
        if (activePlayer == 1) {
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

    if (gameOver) break;

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
    
    // Turning off variables associated with special effects
    if (command == "drop" && activeBoard->getHeavy()) { activeBoard->setHeavy(false); }
    if (command == "drop" && activeBoard->getBlind()) { activeBoard->setBlind(false); }
    if (command == "drop" && activeBoard->getForce()) { activeBoard->setForce(false); }
    if (command == "drop" && activeBoard->getSpawnEffect()) { activeBoard->setSpawnEffect(false); }


    if (dropCounter == 0 && command == "drop" ) { 
      tTurns++; 
      command = "-1"; 
    } else if (command != "drop" && dropCounter > 0) {
      command = "-1";
    }  
    mult = 1;
    cout << td;
  }

  // Displays winning player
  if (gameOver) {
    cout << "\n\n********************** GAME OVER **********************\n\t\t     ";
    activePlayer == 1 ? cout << "Player 2 wins.\n" : cout << "Player 1 wins.\n";
    cout << "**********************           **********************" << endl;
    cout << "Enter any text to close game\n";
    if (!textOnly) {
      if (activePlayer == 1) {
        gd->printGameOver(2);
      } else {
        gd->printGameOver(1);
      }
    }
    string stopGame;
    cin >> stopGame;
  }
  if (!textOnly) {
    delete gd;
  }
}
