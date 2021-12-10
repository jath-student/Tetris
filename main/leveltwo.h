#ifndef __LEVELTWO_H__
#define __LEVELTWO_H__

#include <vector>
#include <string>
#include <fstream>

#include "abslevel.h"
#include "block.h"

using std::string;

class LevelTwo : public AbsLevel {
  private:
    int lvl;
    ifstream infile;
    string fileName;
    bool random = false;

  public:
    LevelTwo(string name = "", bool rand = true); // constructor
    ~LevelTwo() override; // destructor

    int getLevel() override; // gets the level
    bool getRandom() override; // determines if level is set to random
    string getFileName() override; // gets the file name

    void setUpLevel() override; // sets the level
    Block* nextBlock(int idx) override; // adds next block
};

#endif