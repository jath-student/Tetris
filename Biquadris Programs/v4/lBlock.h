#ifndef LBLOCK_H
#define LBLOCK_H

#include "block.h"
#include <vector>
#include <string>
#include <utility>

class Lblock : public Block {
	static const std::vector<std::vector<std::string>> LMatrix; // orientation of the block 
	static const std::vector<int> Lpreview; // preview of the block

	public:	   
    Lblock();
		~Lblock() override; // destructor                  
		std::vector<std::vector<std::string>> getBlock() override; // returns the block
		std::vector<std::pair<int, int>> allFill(int x, int y, int rotation) override;
		std::vector<int> getPreview() override; // returns a preview of the block
		char getType() override; //returns the type of block (l)
};

#endif