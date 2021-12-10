#include "commandhandler.h"
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <sstream>
#include "block.h"
#include "iBlock.h"
#include "jBlock.h"
#include "lBlock.h"
#include "oBlock.h"
#include "sBlock.h"
#include "zBlock.h"
#include "tBlock.h"

using namespace std;
CommandHandler::CommandHandler() {}
CommandHandler::~CommandHandler() {
  allMacros.clear();
  mainCommands.clear();
  allMacros.clear();
}
string filterCommand(string partialStr, string completeStr, vector<string> oldCmds) {
  int count = 0;
  int totalCommands = oldCmds.size();
  vector<string> newCmds;
  int pLen = static_cast<int>(partialStr.length());
  for (int i = 0; i < totalCommands; i++) { // collecting a vector of all similar strings
    if (oldCmds[i].compare(0, pLen, partialStr) == 0) {
      if (pLen == static_cast<int>(oldCmds[i].length())) {
        string finalCmd = oldCmds[i];
        newCmds.clear();
        oldCmds.clear();
        return finalCmd;
      }
      newCmds.emplace_back(oldCmds[i]);
      count++;
    }
  }
  
  oldCmds.clear();
  if (count == 0) {
    newCmds.clear();
    return "-1";
  } else if (count == 1) {
    string finalCmd = newCmds[0];
    newCmds.clear();
    return finalCmd;
  } else {
    if (pLen == static_cast<int>(completeStr.length())) { return "-2"; }
    string str = partialStr;
    str.push_back(completeStr[pLen]);
    return filterCommand(str, completeStr, newCmds);
  }
}


// Calls the regular command
string CommandHandler::callRegularCmd(string cmd) {
  // making a vector of all the commands available by name
  vector<string> cmdNameCopy;
  int numCmds = static_cast<int>(allCommands.size());
  for (int i = 0; i < numCmds; i++) {
    cmdNameCopy.emplace_back(get<0>(allCommands[i]));
  }

  // creating a string out of the first letter of the word and calling filter function
  string str = "";
  str += cmd[0];
  string theCmd = filterCommand(str, cmd, cmdNameCopy);

  // determining which command to call from the output
  if (theCmd != "-1" || theCmd != "-2") {
   auto itNew = find_if(allCommands.begin(), allCommands.end(), [theCmd](const pair<string, int> &ele) {return ele.first == theCmd;} );
    if (itNew == allCommands.end()) { return "-1";}
    int index = (*itNew).second;
    theCmd = mainCommands[index];
    //cout << "the command is " << theCmd << endl;
    return theCmd;
  }
  cout << "INVALID INPUT.\n";
  return theCmd;
}

int CommandHandler::extractMultiplier(string cmd) {
  string number = "";
  for (int i = 0; i < static_cast<int>(cmd.length()) && cmd[i] >= '0' && cmd[i] <= '9'; i++) {
    number += cmd[i];
  }
  if (number == "") { return 1; }
  return stoi(number);
}

string CommandHandler::extractCommand(string cmd) {
  string  command = "";
  for (int i = 0; i < static_cast<int>(cmd.length()); i++) {
    if (!(cmd[i] >= '0' && cmd[i] <= '9')) { command += cmd[i]; }
  }
  //cout << "returnining: " << command << endl;
  return command;
}

string CommandHandler::callCommands(string cmd) {
  //cout << "the command is: " << cmd << endl;
  if (cmd == "") { // no empty strings
    cout << "INVALID INPUT\n";
    return "-1";
  } else if (cmd[0] == '-') { // cannot start with a -
    cout << "INVALID COMMAND.\n";
  }
  string command = callRegularCmd( extractCommand(cmd) );
  return command;
}

void CommandHandler::addRename(string cmdName, string original) {
  auto itNew = find_if(allCommands.begin(), allCommands.end(), [cmdName](const pair<string, int> &ele) {return ele.first == cmdName;} );
  auto itExist = find(mainCommands.begin(), mainCommands.end(), original);

  // making a vector of all the commands available by name
  vector<string> cmdNameCopy;
  int numCmds = static_cast<int>(allCommands.size());
  for (int i = 0; i < numCmds; i++) {
    cmdNameCopy.emplace_back(get<0>(allCommands[i]));
  }

  string str = "";
  str += cmdName[0];
  string theCmd = filterCommand(str, cmdName, cmdNameCopy);

  if (theCmd == "-2") { cout << " INPUT TOO VAGUE.\n"; return; }
  if (itNew == allCommands.end() && itExist != mainCommands.end()) {
    allCommands.emplace_back(make_pair(cmdName, (itExist - mainCommands.begin())));
  } 
}
string CommandHandler::callEffectCmd(string cmd) {
  cout << "\n\n************ Score Multiplier Bonus Effects ************\n\t     ";
  cout << "Score Multiplier Bonus Effects (Type your option):\n\t 1) Force \n\t 2) Heavy \n\t 3) Blind\n";
  cout << "**************************************************************\n";
  while (cin >> cmd) {
    cout << "COMMAND IS " << cmd;
    if (cmd == "Heavy" || cmd == "Force" || cmd == "Blind") { return cmd; }
    else { cout << "\nINVALID INPUT.\n"; }
  }
  return "-1";
}

char CommandHandler::forceEffectBlock(char cmd) {
  cout << "Enter the block you would like to make the opponent use: \n";
  while(cin >> cmd) {
    if (cmd == 'S' || cmd == 'Z' || cmd == 'T' || cmd =='J' || cmd == 'L' ||cmd == 'O' || cmd == 'I') {
      return cmd;
    }
    cout << "INVALID INPUT.\n";
  }
  return ' ';
}

Block* CommandHandler::getForceBlock(bool hvy, char cmd) {
  if (cmd  == 'I') {
    return new Iblock(hvy);	
  } else if (cmd == 'O') {
    return new Oblock(hvy);
  } else if (cmd == 'J') {
    return new Jblock(hvy);
  } else if (cmd == 'Z') {
    return new Zblock(hvy);
  } else if (cmd == 'T') {
    return new Tblock(hvy);
  }	else if (cmd == 'L') {
    return new Lblock(hvy);
  }
  return new Sblock(hvy);
}