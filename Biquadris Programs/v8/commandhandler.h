#ifndef __COMMANDHANDLER_H__
#define __COMMANDHANDLER_H__

#include <vector>
#include <string>
#include <utility>
#include "block.h"
using namespace std;

class CommandHandler {
  private:
    vector<string> mainCommands = {"left", "right", "down", "clockwise", "counterclockwise", "drop", 
                                  "levelup", "leveldown", "norandom", "random", "sequence", 
                                  "I", "J", "L", "O", "T", "S", "Z", "restart", "rename", "hint", "stopgame"};
    vector<pair<string, int>> allCommands = { {"left", 0}, {"right", 1}, {"down", 2}, {"clockwise", 3},
                                                 {"counterclockwise", 4}, {"drop", 5}, {"levelup", 6},
                                                 {"leveldown", 7}, {"norandom", 8}, {"random", 9}, {"sequence", 10},
                                                 {"I", 11}, {"J", 12}, {"L", 13}, {"O", 14}, {"T", 15}, {"S", 16}, {"Z", 17}, {"restart", 18}, {"rename", 19}, {"hint", 20}, {"stopgame", 21}};
    vector<pair<string, vector<int>>> allMacros;
  public:
    CommandHandler();
    ~CommandHandler();
    string callCommands(string cmd); // calls the commands, the main part of command handler
    void addRename(string cmdName, string original); // adds a command for rename
    int extractMultiplier(string cmd); // returns the multiplier value
    string extractCommand(string cmd);
    string callRegularCmd(string cmd);
    string callEffectCmd(string cmd);
    char forceEffectBlock(char cmd);
    Block* getForceBlock(bool hvy, char cmd);
};

#endif