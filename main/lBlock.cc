#include "block.h"
#include "lBlock.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
Lblock::Lblock(bool hvy) : Block(0, 0, 0, hvy) {}

// Destructor
Lblock::~Lblock() {}

// Returns indexes to turn on for preview section
const std::vector<int> Lblock::Lpreview {2, 4, 5, 6};

// Returns L for lBlock (type)
char Lblock::getType() { 
    return 'L'; 
}

// All Block Rotations
std::vector<std::string> rotationL0 {
    "----", 
    "----", 
    "--L-", 
    "LLL-"
};

std::vector<std::string> rotationL90 {
    "----", 
    "L---", 
    "L---", 
    "LL--"
}; 

std::vector<std::string> rotationL180 {
    "----", 
    "----", 
    "LLL-", 
    "L---"
}; 

std::vector<std::string> rotationL270 {
    "----", 
    "LL--", 
    "-L--", 
    "-L--"
};

// Determines which cell's the block will occupy if the top-left corner of the
//   4x4 grid is at the x,y coordinates specified with the specified rotation
std::vector<std::pair<int, int>> Lblock::allFill(int x, int y, int rotation) {
    vector<pair<int, int>> allFilled;
    if (rotation == 0) {
        allFilled.push_back(make_pair(x, y+3));
        allFilled.push_back(make_pair(x+1, y+3));
        allFilled.push_back(make_pair(x+2, y+2));
        allFilled.push_back(make_pair(x+2, y+3));
    } else if (rotation == 1) {
        allFilled.push_back(make_pair(x, y+1));
        allFilled.push_back(make_pair(x, y+2));
        allFilled.push_back(make_pair(x, y+3));
        allFilled.push_back(make_pair(x+1, y+3));
    } else if (rotation == 2) {
        allFilled.push_back(make_pair(x, y+2));
        allFilled.push_back(make_pair(x, y+3));
        allFilled.push_back(make_pair(x+1, y+2));
        allFilled.push_back(make_pair(x+2, y+2));
    } else if (rotation == 3) {
       allFilled.push_back(make_pair(x, y+1));
       allFilled.push_back(make_pair(x+1, y+1));
       allFilled.push_back(make_pair(x+1, y+2));
       allFilled.push_back(make_pair(x+1, y+3));
    }
    return allFilled;
}

// Creates a matrix with all possible types of J blocks (all rotations)
const std::vector<std::vector<std::string>> Lblock::LMatrix = {
    rotationL0, 
    rotationL90, 
    rotationL180, 
    rotationL270
};

// Returns the matrix of the block 
std::vector<std::vector<std::string>> Lblock::getBlock() {
    return LMatrix;
}

// Returns preview
std::vector<int> Lblock::getPreview() { 
    return Lpreview; 
}