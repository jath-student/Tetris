#ifndef OBLOCK_H
#define OBLOCK_H

#include "block.h"
#include <vector>
#include <string>
#include <utility>

class Oblock : public Block {
	static const std::vector<std::vector<std::string>> OMatrix; // orientation of the block 
	static const std::vector<int> Opreview; // preview of the block

	public:
		Oblock();	   
    ~Oblock() override; // destructor                  
		std::vector<std::vector<std::string>> getBlock() override; // returns the block
		std::vector<std::pair<int, int>> allFill(int x, int y, int rotation) override;
		std::vector<int> getPreview() override; // returns a preview of the block
		char getType() override; //returns the type of block (o)
};

#endif