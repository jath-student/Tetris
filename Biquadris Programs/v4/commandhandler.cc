#include "commandhandler.h"
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <sstream>
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
    return theCmd;
  }
  cout << "INVALID INPUT.\n";
  return theCmd;
}


// void CommandHandler::callMacroCmd(string cmd) {
//   auto itNew = find_if(allMacros.begin(), allMacros.end(), [cmd](const pair<string, vector<int>> &ele) {return ele.first == cmd;} );
//   if (itNew != allMacros.end()) {
//     int total = static_cast<int>((get<1>(*itNew)).size());
//     for (int i = 0; i < total; i++) {
//       executeFunction((get<1>(*itNew))[i]);
//     }
//   }
// }

int CommandHandler::extractMultiplier(string cmd) {
  string number = "";
  for (int i = 0; i < cmd.length() && cmd[i] >= '0' && cmd[i] <= '9'; i++) {
    number += cmd[i];
  }
  if (number == "") { return 1; }
  return stoi(number);
}

string CommandHandler::extractCommand(string cmd) {
  string  command = "";
  for (int i = 0; i < cmd.length(); i++) {
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
    cout << "INVALID COMMAND\n";
  } else if (cmd[0] == '+') {
    cout << "macro\n";
    //callMacroCmd(cmd);
  }
  //cout << "extracted cmd: " << extractCommand(cmd) << endl;
  string command = callRegularCmd( extractCommand(cmd) );
  return command;
}

void CommandHandler::addRename(string cmdName, string original) {
  auto itNew = find_if(allCommands.begin(), allCommands.end(), [cmdName](const pair<string, int> &ele) {return ele.first == cmdName;} );
  auto itExist = find(mainCommands.begin(), mainCommands.end(), original);
  if (callRegularCmd(cmdName) == "-2") { cout << " INPUT TOO VAGUE.\n"; return; }
  if (itNew == allCommands.end() && itExist != mainCommands.end()) {
    allCommands.emplace_back(make_pair(cmdName, itExist - mainCommands.begin()));
  } 
}

// void CommandHandler::addMacro(string macroName) {
//   string theMacro = "+" + macroName;
//   auto itNew = find_if(allMacros.begin(), allMacros.end(), [theMacro](const pair<string, vector<int>> &ele) {return ele.first == theMacro;} );
//   if (itNew == allMacros.end()) {
//     vector<int> sequenceCmds;
//     string addCmd;
//     while (cin >> addCmd) {
//       if (addCmd == "EM") {
//         cout << "end macro";
//         if (!sequenceCmds.empty()) {
//           allMacros.emplace_back(make_pair(theMacro, sequenceCmds));
//         }
//         break;
//       } 
//       auto itRealCmd = find(mainCommands.begin(), mainCommands.end(), addCmd);
//       if (itRealCmd != mainCommands.end()) {
//         sequenceCmds.push_back(itRealCmd - mainCommands.begin());
//       } else {
//         cout << "fake cmd";
//       }
//     }
//   }

  //for (int i = 0; i < static_cast<int>(allMacros.size()); i++) {
  //  cout << "Macro Name: " << get<0>(allMacros[i]) << endl;
  //  for (int j = 0; j < static_cast<int>(get<1>(allMacros[i]).size()); j++) {
  //    cout << get<1>(allMacros[i])[j] << ", ";
  //  }
  //  cout << endl;
  //}