#ifndef JBLOCK_H
#define JBLOCK_H

#include "block.h"
#include <vector>
#include <string>

class Jblock : public Block {
	static const std::vector<std::vector<std::string>> JMatrix; // orientation of the block 
	static const std::vector<size_t> Jpreview; // preview of the block

	public:	   
    Jblock();
		virtual ~Jblock() override; // destructor                    
		virtual std::vector<std::vector<std::string>> getBlock() override; // returns the block
		virtual std::vector<size_t> getPreview() override; // returns a preview of the block
		virtual char getType() override; //returns the type of block (j)
};

#endif