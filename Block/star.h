#ifndef STARBLOCK_H
#define STARBLOCK_H

#include "block.h"
#include <vector>
#include <string>

class starblock : public Block {
	static const std::vector<std::vector<std::string>> starMatrix; // orientation of the block 
	static const std::vector<size_t> starpreview; // preview of the block

	public:	   
        virtual ~starblock() override; // destructor                  
		virtual std::vector<std::vector<std::string>> getBlock() override; // returns the block
		virtual std::vector<size_t> getPreview() override; // returns a preview of the block
		virtual char getType() override; //returns the type of block (o)
};

#endif