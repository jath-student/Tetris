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
    LevelZero( string name );
    ~LevelZero() override;

    int getLevel() override;
    bool getRandom() override;
    string getFileName() override;

    void setUpLevel() override;
    Block* nextBlock(int idx) override;
};
#endif