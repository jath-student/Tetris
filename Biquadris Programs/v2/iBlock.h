#ifndef IBLOCK_H
#define IBLOCK_H

#include "block.h"
#include <vector>
#include <string>
#include <utility>

class Iblock : public Block {
	static const std::vector<std::vector<std::string>> IMatrix; // orientation of the block 
	static const std::vector<int> Ipreview; // preview of the block

	public:	   
    Iblock();
		~Iblock() override; // destructor                  
		std::vector<std::vector<std::string>> getBlock() override; // returns the block
		std::vector<std::pair<int, int>> allFill(int x, int y, int rotation) override;
		std::vector<int> getPreview() override; // returns a preview of the block
		char getType() override; //returns the type of block (i)
};

#endif