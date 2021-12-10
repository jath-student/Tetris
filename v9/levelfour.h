#ifndef __LEVELFOUR_H__
#define __LEVELFOUR_H__

#include <vector>
#include <string>
#include <fstream>

#include "abslevel.h"
#include "block.h"

using std::string;

class LevelFour : public AbsLevel {
  private:
    int lvl;
    int interval;
    ifstream infile;
    string fileName;
    bool random = false;

  public:
    LevelFour(string name = "", bool rand = true); // constructor
    ~LevelFour() override; // destructor

    int getLevel() override; // gets the level
    bool getRandom() override; // determines if level is set to random
    string getFileName() override; // gets the file name
    int getInterval(); // gets the interval for star block
    void increaseInterval(); // increases the interval for star block

    void setUpLevel() override; // sets up the level
    Block* nextBlock(int idx) override; // adds next block
    void resetInterval(); // resets the interval
};

#endif