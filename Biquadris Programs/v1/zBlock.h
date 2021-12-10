#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "block.h"
#include <vector>
#include <string>

class Zblock : public Block {
	static const std::vector<std::vector<std::string>> ZMatrix; // orientation of the block 
	static const std::vector<size_t> Zpreview; // preview of the block

	public:	   
    Zblock();
		virtual ~Zblock() override; // destructor                  
		virtual std::vector<std::vector<std::string>> getBlock() override; // returns the block
		virtual std::vector<size_t> getPreview() override; // returns a preview of the block
		virtual char getType() override; //returns the type of block (z)
};

#endif