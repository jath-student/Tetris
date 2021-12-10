#ifndef LBLOCK_H
#define LBLOCK_H

#include "block.h"
#include <vector>
#include <string>

class Lblock : public Block {
	static const std::vector<std::vector<std::string>> LMatrix; // orientation of the block 
	static const std::vector<size_t> Lpreview; // preview of the block

	public:	   
    Lblock();
		virtual ~Lblock() override; // destructor                  
		virtual std::vector<std::vector<std::string>> getBlock() override; // returns the block
		virtual std::vector<size_t> getPreview() override; // returns a preview of the block
		virtual char getType() override; //returns the type of block (l)
};

#endif