#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>
#include <utility>


// This class is a general outline of a block 

class Block {
	// x refers to the x-coordinate of a block, y refers to the y-coordinate of a block, 
	// and rotation refers to how much the block is rotated (i.e. 90 degrees)
    int x, y, rotation; 
		bool heavy = false;
	
	public:
		Block(int x, int y, int rotation, bool heavy = false); // constructor for block
		virtual ~Block(); // destructor for block
		virtual char getType() = 0; // returns the type of block (i.e. zBlock, sBlock, etc.)
		int getX(); // returns the x-coordinate of the block
		int getY(); // returns the y-coordinate of the block
		int getRotation(); // returns the amount of how much the block is rotated by
		void setX(int xCor); // sets x-coordinate
		void setY(int yCor); // sets y-coordinate
		void setRotation(int rotationAmt); // sets the rotation amount
		virtual std::vector<std::pair<int, int>> allFill(int x, int y, int rotation) = 0;
		virtual std::vector<std::vector<std::string>> getBlock() = 0; // gets the vector of block
		bool blockIsHeavy(); // returns if block is heavy
		virtual std::vector<int> getPreview() = 0;  // get the preview of a block
};

#endif
