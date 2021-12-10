#ifndef STARBLOCK_H
#define STARBLOCK_H

#include "block.h"
#include <vector>
#include <string>

class starblock : public Block {
	static const std::vector<std::vector<std::string>> starMatrix; // orientation of the block 
	static const std::vector<int> starpreview; // preview of the block

	public:	 
    starblock();  
    ~starblock() override; // destructor                  
		std::vector<std::vector<std::string>> getBlock() override; // returns the block
		std::vector<int> getPreview() override; // returns a preview of the block
		char getType() override; //returns the type of block (o)
};

#endif