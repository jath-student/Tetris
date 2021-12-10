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
    LevelOne(string name = "", bool rand = true);
    ~LevelOne() override;

    int getLevel() override;
    bool getRandom() override;
    string getFileName() override;

    void setUpLevel() override;
    Block* nextBlock(int idx) override;
};

#endif