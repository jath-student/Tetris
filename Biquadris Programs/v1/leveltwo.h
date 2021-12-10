#ifndef __LEVELTWO_H__
#define __LEVELTWO_H__

#include <vector>
#include <string>
#include <fstream>

#include "abslevel.h"
#include "block.h" // F: check this??

using std::string;

class LevelTwo : public AbsLevel {
  private:
    int lvl;
    ifstream infile;
    string fileName;
    bool random = false;
  public:
    LevelTwo(string name = "", bool rand = true);
    ~LevelTwo() override;

    int getLevel() override;
    bool getRandom() override;
    string getFileName() override;

    void setUpLevel() override;
    Block* nextBlock(size_t idx) override;
};

#endif