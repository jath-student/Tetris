#ifndef __LEVELZERO_H__
#define __LEVELZERO_H__

#include <string>
#include <fstream>

#include "abslevel.h"
#include "block.h"

using std::string;

class LevelZero : public AbsLevel {
  private:
    int lvl;
    ifstream infile;
    string fileName;
    bool random = false;
    
  public:
    LevelZero( string name ); // constructor
    ~LevelZero() override; // destructor

    int getLevel() override; // gets the level
    bool getRandom() override; // determines if level is set to random
    string getFileName() override; // gets the file name

    void setUpLevel() override; // sets up the level
    Block* nextBlock(int idx) override; // adds next block
};
#endif