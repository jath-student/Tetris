#include "block.h"
#include "sBlock.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
Sblock::Sblock(bool hvy) : Block(0, 0, 0, hvy) {}

// Destructor
Sblock::~Sblock() {}

// Returns indexes to turn on for preview section
const std::vector<int> Sblock::Spreview {1, 2, 4, 5};

// Returns S for sBlock (type)
char Sblock::getType() { 
    return 'S'; 
}

// All Block Rotations
std::vector<std::string> rotationS0 {
    "----", 
    "----", 
    "-SS-", 
    "SS--"
};

std::vector<std::string> rotationS90 {
    "----", 
    "S---", 
    "SS--", 
    "-S--", 
}; 

std::vector<std::string> rotationS180 {
    "----", 
    "----", 
    "-SS-", 
    "SS--"
};

std::vector<std::string> rotationS270 {
    "----", 
    "S---", 
    "SS--", 
    "-S--", 
}; 

// Determines which cell's the block will occupy if the top-left corner of the
//   4x4 grid is at the x,y coordinates specified with the specified rotation
std::vector<std::pair<int, int>> Sblock::allFill(int x, int y, int rotation) {
    vector<pair<int, int>> allFilled;
    if (rotation == 0 || rotation == 2) {
        allFilled.push_back(make_pair(x+1, y+2));
        allFilled.push_back(make_pair(x+2, y+2));
        allFilled.push_back(make_pair(x, y+3));
        allFilled.push_back(make_pair(x+1, y+3));
    } else {
        allFilled.push_back(make_pair(x, y+1));
        allFilled.push_back(make_pair(x, y+2));
        allFilled.push_back(make_pair(x+1, y+2));
        allFilled.push_back(make_pair(x+1, y+3));
    }
    return allFilled;
}

// Creates a matrix with all possible types of J blocks (all rotations)
const std::vector<std::vector<std::string>> Sblock::SMatrix = {
    rotationS0, 
    rotationS90, 
    rotationS180, 
    rotationS270
};

// Returns the matrix of the block 
std::vector<std::vector<std::string>> Sblock::getBlock() {
    return SMatrix;
}

// Returns preview
std::vector<int> Sblock::getPreview() { 
    return Spreview; 
}

