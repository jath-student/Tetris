#include "block.h"
#include "oBlock.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
Oblock::Oblock(bool hvy) : Block(0, 0, 0, hvy) {}

// Destructor
Oblock::~Oblock() {}

// Returns indexes to turn on for preview section
const std::vector<int> Oblock::Opreview {0, 1, 4,5};

// Returns O for oBlock (type)
char Oblock::getType() { 
    return 'O'; 
}

// All Block Rotations
std::vector<std::string> rotationO0 {
    "----", 
    "----", 
    "OO--", 
    "OO--"
};

std::vector<std::string> rotationO90 {
    "----", 
    "----", 
    "OO--", 
    "OO--"
}; 

std::vector<std::string> rotationO180 {
    "----", 
    "----", 
    "OO--", 
    "OO--"
}; 

std::vector<std::string> rotationO270 {
    "----", 
    "----", 
    "OO--", 
    "OO--"
};

// Determines which cell's the block will occupy if the top-left corner of the
//   4x4 grid is at the x,y coordinates specified with the specified rotation
std::vector<std::pair<int, int>> Oblock::allFill(int x, int y, int rotation) {
    vector<pair<int, int>> allFilled;
    allFilled.push_back(make_pair(x, y+2));
    allFilled.push_back(make_pair(x, y+3));
    allFilled.push_back(make_pair(x+1, y+2));
    allFilled.push_back(make_pair(x+1, y+3));
    return allFilled;
}

// Creates a matrix with all possible types of J blocks (all rotations)
const std::vector<std::vector<std::string>> Oblock::OMatrix = {
    rotationO0, 
    rotationO90, 
    rotationO180, 
    rotationO270
};

// Returns the matrix of the block 
std::vector<std::vector<std::string>> Oblock::getBlock() {
    return OMatrix;
}

// Returns preview
std::vector<int> Oblock::getPreview() { 
    return Opreview; 
}