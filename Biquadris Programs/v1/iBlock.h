#ifndef IBLOCK_H
#define IBLOCK_H

#include "block.h"
#include <vector>
#include <string>

class Iblock : public Block {
	static const std::vector<std::vector<std::string>> IMatrix; // orientation of the block 
	static const std::vector<size_t> Ipreview; // preview of the block

	public:	   
    Iblock();
		virtual ~Iblock() override; // destructor                  
		virtual std::vector<std::vector<std::string>> getBlock() override; // returns the block
		virtual std::vector<size_t> getPreview() override; // returns a preview of the block
		virtual char getType() override; //returns the type of block (i)
};

#endif