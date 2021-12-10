#ifndef TBLOCK_H
#define TBLOCK_H

#include "block.h"
#include <vector>
#include <string>

class Tblock : public Block {
	static const std::vector<std::vector<std::string>> TMatrix; // orientation of the block 
	static const std::vector<size_t> Tpreview; // preview of the block

	public:	   
		Tblock();
		virtual ~Tblock() override; // destructor                  
		virtual std::vector<std::vector<std::string>> getBlock() override; // returns the block
		virtual std::vector<size_t> getPreview() override; // returns a preview of the block
		virtual char getType() override; //returns the type of block (t)
};

#endif