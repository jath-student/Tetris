#ifndef __ABSLEVEL_H__
#define __ABSLEVEL_H__

// include all block files
#include <vector>
#include "block.h"
#include "iBlock.h"
#include "jBlock.h"
#include "lBlock.h"
#include "oBlock.h"
#include "sBlock.h"
#include "zBlock.h"
#include "tBlock.h"

using namespace std;

 class AbsLevel {
   protected:
    vector<char> blocks;
   public:
    virtual int getLevel() = 0; // return the value of the level
    virtual bool getRandom() = 0; // Return value of random
    virtual string getFileName() = 0; // Return the file name
    
    virtual void setUpLevel() = 0;
    virtual Block* nextBlock(size_t idx) = 0;
    
    virtual ~AbsLevel(); // Destructor    

 };
#endif