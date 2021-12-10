#ifndef SBLOCK_H
#define SBLOCK_H

#include "block.h"
#include <vector>
#include <string>

class Sblock : public Block {
	static const std::vector<std::vector<std::string>> SMatrix; // orientation of the block 
	static const std::vector<size_t> Spreview; // preview of the block

	public:	 
		Sblock();  
    virtual ~Sblock() override; // destructor                  
		virtual std::vector<std::vector<std::string>> getBlock() override; // returns the block
		virtual std::vector<size_t> getPreview() override; // returns a preview of the block
		virtual char getType() override; //returns the type of block (s)
};

#endif