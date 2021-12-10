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


using namespace std;

// HINT??
int main() {
  CommandHandler ch;
  ch.callCommands("left");
  cout << "next";
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
}