#ifndef __LEVELFOUR_H__
#define __LEVELFOUR_H__

#include <vector>
#include <string>
#include <fstream>

#include "abslevel.h"
#include "block.h" // F: check this??

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

    void setUpLevel() override;
    Block* nextBlock(size_t idx) override;
    void resetInterval();
};

#endif