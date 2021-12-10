#ifndef __LEVELTHREE_H__
#define __LEVELTHREE_H__

#include <vector>
#include <string>
#include <fstream>

#include "abslevel.h"
#include "block.h"

using std::string;

class LevelThree : public AbsLevel {
  private:
    int lvl;
    ifstream infile;
    string fileName;
    bool random = false;
  public:
    LevelThree(string name = "", bool rand = true);
    ~LevelThree() override;

    int getLevel() override;
    bool getRandom() override;
    string getFileName() override;

    void setUpLevel() override;
    Block* nextBlock(int idx) override;
};

#endif