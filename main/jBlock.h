#ifndef JBLOCK_H
#define JBLOCK_H

#include "block.h"
#include <vector>
#include <string>
#include <utility>

class Jblock : public Block {
	static const std::vector<std::vector<std::string>> JMatrix; // orientation of the block 
	static const std::vector<int> Jpreview; // preview of the block

	public:	   
    Jblock(bool hvy = false);
		~Jblock() override; // destructor                    
		std::vector<std::vector<std::string>> getBlock() override; // returns the block
		std::vector<std::pair<int, int>> allFill(int x, int y, int rotation) override;
		std::vector<int> getPreview() override; // returns a preview of the block
		char getType() override; //returns the type of block (j)
};

#endif