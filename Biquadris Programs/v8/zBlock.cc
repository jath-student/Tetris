#include "block.h"
#include "zBlock.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
Zblock::Zblock(bool hvy) : Block(0, 0, 0, hvy) {}

// Destructor
Zblock::~Zblock() {}

// Returns Z for zBlock (type)
char Zblock::getType() { 
    return 'Z'; 
}

// Returns indexes to turn on for preview section
const std::vector<int> Zblock::Zpreview {0, 1, 5, 6};

// All Block Rotations
std::vector<std::string> rotationZ0 {
    "----", 
    "----", 
    "ZZ--", 
    "-ZZ-"
};

std::vector<std::string> rotationZ90 {
    "----", 
    "-Z--", 
    "ZZ--", 
    "Z---", 
}; 

std::vector<std::string> rotationZ180 {
    "----", 
    "----", 
    "ZZ--", 
    "-ZZ-"
};

std::vector<std::string> rotationZ270 {
    "----", 
    "-Z--", 
    "ZZ--", 
    "Z---", 
}; 

// Determines which cell's the block will occupy if the top-left corner of the
//   4x4 grid is at the x,y coordinates specified with the specified rotation
std::vector<std::pair<int, int>> Zblock::allFill(int x, int y, int rotation) {
    vector<pair<int, int>> allFilled;
    if (rotation == 0 || rotation == 2) {
        allFilled.push_back(make_pair(x, y+2));
        allFilled.push_back(make_pair(x+1, y+2));
        allFilled.push_back(make_pair(x+1, y+3));
        allFilled.push_back(make_pair(x+2, y+3));
    } else {
        allFilled.push_back(make_pair(x+1, y+1));
        allFilled.push_back(make_pair(x+1, y+2));
        allFilled.push_back(make_pair(x, y+2));
        allFilled.push_back(make_pair(x, y+3));
    }
    return allFilled;
}

// Creates a matrix with all possible types of J blocks (all rotations)
const std::vector<std::vector<std::string>> Zblock::ZMatrix = {
    rotationZ0, 
    rotationZ90, 
    rotationZ180, 
    rotationZ270
};

// Returns the matrix of the block 
std::vector<std::vector<std::string>> Zblock::getBlock() {
    return ZMatrix;
}

// Returns preview
std::vector<int> Zblock::getPreview() { 
    return Zpreview; 
}
