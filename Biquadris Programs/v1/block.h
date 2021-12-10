#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>

// This class is a general outline of a block 

class Block {
	// x refers to the x-coordinate of a block, y refers to the y-coordinate of a block, 
	// and rotation refers to how much the block is rotated (i.e. 90 degrees)
    size_t x, y, rotation; 
	
	public:
		Block(size_t x, size_t y, size_t rotation); // constructor for block
		virtual ~Block(); // destructor for block
		virtual char getType() = 0; // returns the type of block (i.e. zBlock, sBlock, etc.)
		size_t getX(); // returns the x-coordinate of the block
		size_t getY(); // returns the y-coordinate of the block
		size_t getRotation(); // returns the amount of how much the block is rotated by
		void setX(size_t xCor); // sets x-coordinate
		void setY(size_t yCor); // sets y-coordinate
		void setRotation(size_t rotationAmt); // sets the rotation amount
		virtual std::vector<std::vector<std::string>> getBlock() = 0; // gets the vector of block
		virtual std::vector<size_t> getPreview() = 0;  // get the preview of a block
};

#endif
