#include "commandhandler.h"
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <sstream>
using namespace std;
CommandHandler::CommandHandler() {}

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
    return "";
  } else if (count == 1) {
    string finalCmd = newCmds[0];
    newCmds.clear();
    return finalCmd;
  } else {
    if (pLen == static_cast<int>(completeStr.length())) { return ""; }
    string str = partialStr;
    str.push_back(completeStr[pLen]);
    return filterCommand(str, completeStr, newCmds);
  }
}

void executeFunction(int callFunction) {
  switch (callFunction) {
    case 0:
      cout << "function for left\n";
      break;
    case 1:
      cout << "function for right\n";
      break;
    case 2:
      cout << "function for down\n";
      break;
    case 3:
      cout << "function for clockwise\n";
      break;
    case 4:
      cout << "function for counterclockwise\n";
      break;
    case 5:
      cout << "function for drop\n";
      break;
    case 6:
      cout << "function for levelup\n";
      break;
    case 7:
      cout << "function for leveldown\n";
      break;
    case 8:
      cout << "function for norandom file\n";
      break;
    case 9:
      cout << "function for random\n";
      break;
    case 10:
      cout << "function for sequence file\n";
      break;
    case 11:
      cout << "function for I\n";
      break;
    case 12:
      cout << "function for J\n";
      break;
    case 13:
      cout << "function for L\n";
      break;
    case 14:
      cout << "function for O\n";
      break;
    case 15:
      cout << "function for T\n";
      break;
    case 16:
      cout << "function for S\n";
      break;
    case 17:
      cout << "function for Z\n";
      break;
    case 18:
      cout << "function for restart\n";
      break;
    default:
      cout << "invalid command\n";

    // can simplfy the single character blocks
  }
}

// Calls the regular command
void CommandHandler::callRegularCmd(string cmd, int totalTimes) {
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
  if (theCmd != "") {
    cout << theCmd << " was called." << endl;
    auto it = find_if(allCommands.begin(), allCommands.end(), [theCmd](const pair<string, int> &ele) {return ele.first == theCmd;} );
    if (theCmd == "hint" || theCmd == "restart" || theCmd == "random" || theCmd == "norandom") { totalTimes = 1;}
    for (int i = 0; i < totalTimes; i++) {
      executeFunction(get<1>(*it));
    }
  } else {
    cout << "Command DNE.\n";
    return;
  }
}


void CommandHandler::callMacroCmd(string cmd) {
  auto itNew = find_if(allMacros.begin(), allMacros.end(), [cmd](const pair<string, vector<int>> &ele) {return ele.first == cmd;} );
  if (itNew != allMacros.end()) {
    int total = static_cast<int>((get<1>(*itNew)).size());
    for (int i = 0; i < total; i++) {
      executeFunction((get<1>(*itNew))[i]);
    }
  }
}
void CommandHandler::callCommands(string cmd) {
  if (cmd == "") { 
    cout << "empty\n";
    return;
  } else if (cmd[0] == '+') {
    cout << "macro\n";
    callMacroCmd(cmd);
  } else {
    string number = "";
    string theCmd = "";
    int i = 0;
    int totalLen = static_cast<int>(cmd.length());
    bool multiplier = true;
    bool noMultiplier = true;
    while (i < totalLen) {
      if ((cmd[i] >= '0'&& cmd[i] <= '9') && multiplier == true) {
        number += cmd[i];
        noMultiplier = false;
      } else {
        theCmd += cmd[i];
        multiplier = false;
      }
      i++;
    }
    //theCmd = filterCommand(theCmd);
    if (noMultiplier == true) {
      callRegularCmd(theCmd, 1);
      cout << "no mult\n";
      return;
    }
    cout << "mult exists\n";
    callRegularCmd(theCmd, stoi(number));
  }
}

void CommandHandler::addRename(string cmdName, string original) {
  auto itNew = find_if(allCommands.begin(), allCommands.end(), [cmdName](const pair<string, int> &ele) {return ele.first == cmdName;} );
  auto itExist = find(mainCommands.begin(), mainCommands.end(), original);
  if (itNew == allCommands.end() && itExist != mainCommands.end()) {
    allCommands.emplace_back(make_pair(cmdName, itExist - mainCommands.begin()));
  } 
}

void CommandHandler::addMacro(string macroName) {
  string theMacro = "+" + macroName;
  auto itNew = find_if(allMacros.begin(), allMacros.end(), [theMacro](const pair<string, vector<int>> &ele) {return ele.first == theMacro;} );
  if (itNew == allMacros.end()) {
    vector<int> sequenceCmds;
    string addCmd;
    while (cin >> addCmd) {
      if (addCmd == "EM") {
        cout << "end macro";
        if (!sequenceCmds.empty()) {
          allMacros.emplace_back(make_pair(theMacro, sequenceCmds));
        }
        break;
      } 
      auto itRealCmd = find(mainCommands.begin(), mainCommands.end(), addCmd);
      if (itRealCmd != mainCommands.end()) {
        sequenceCmds.push_back(itRealCmd - mainCommands.begin());
      } else {
        cout << "fake cmd";
      }
    }
  }

  //for (int i = 0; i < static_cast<int>(allMacros.size()); i++) {
  //  cout << "Macro Name: " << get<0>(allMacros[i]) << endl;
  //  for (int j = 0; j < static_cast<int>(get<1>(allMacros[i]).size()); j++) {
  //    cout << get<1>(allMacros[i])[j] << ", ";
  //  }
  //  cout << endl;
  //}
}