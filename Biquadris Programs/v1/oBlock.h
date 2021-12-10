#ifndef OBLOCK_H
#define OBLOCK_H

#include "block.h"
#include <vector>
#include <string>

class Oblock : public Block {
	static const std::vector<std::vector<std::string>> OMatrix; // orientation of the block 
	static const std::vector<size_t> Opreview; // preview of the block

	public:
		Oblock();	   
    virtual ~Oblock() override; // destructor                  
		virtual std::vector<std::vector<std::string>> getBlock() override; // returns the block
		virtual std::vector<size_t> getPreview() override; // returns a preview of the block
		virtual char getType() override; //returns the type of block (o)
};

#endif