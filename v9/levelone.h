#ifndef __LEVELONE_H__
#define __LEVELONE_H__

#include <vector>
#include <string>
#include <fstream>

#include "abslevel.h"
#include "block.h"

using std::string;

class LevelOne : public AbsLevel {
  private:
    int lvl;
    ifstream infile;
    string fileName;
    bool random = false;
  
  public:
    LevelOne(string name = "", bool rand = true); // constructor
    ~LevelOne() override; // destructor

    int getLevel() override; // gets the level
    bool getRandom() override; // determines if level is set to random
    string getFileName() override; // gets the file name

    void setUpLevel() override; // sets the level
    Block* nextBlock(int idx) override; // adds new block
};

#endif