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
    LevelFour(string name = "", bool rand = true);
    ~LevelFour() override;

    int getLevel() override;
    bool getRandom() override;
    string getFileName() override;
    int getInterval();
    void increaseInterval();

    void setUpLevel() override;
    Block* nextBlock(int idx) override;
    void resetInterval();
};

#endif