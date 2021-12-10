#ifndef __LEVELZERO_H__
#define __LEVELZERO_H__

#include <vector>
#include <string>
#include <fstream>

#include "abslevel.h"
#include "block.h" // F: check this??

using std::string;

using std::string;

class LevelZero : public AbsLevel {
  private:
    int lvl;
    ifstream infile;
    string fileName;
    bool random = false;
  public:
    LevelZero( string name );
    ~LevelZero() override;

    int getLevel() override;
    bool getRandom() override;
    string getFileName() override;

    void setUpLevel() override;
    Block* nextBlock(size_t idx) override;
};
#endif