#ifndef SBLOCK_H
#define SBLOCK_H

#include "block.h"
#include <vector>
#include <string>
#include <utility>

class Sblock : public Block {
	static const std::vector<std::vector<std::string>> SMatrix; // orientation of the block 
	static const std::vector<int> Spreview; // preview of the block

	public:	 
		Sblock(bool hvy = false);  
    ~Sblock() override; // destructor                  
		std::vector<std::vector<std::string>> getBlock() override; // returns the block
		std::vector<std::pair<int, int>> allFill(int x, int y, int rotation) override;
		std::vector<int> getPreview() override; // returns a preview of the block
		char getType() override; //returns the type of block (s)
};

#endif