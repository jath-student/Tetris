#include "block.h"
#include "tBlock.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
Tblock::Tblock() : Block(0, 0, 0) {}

// Destructor
Tblock::~Tblock() {}

// Returns T for tBlock (type)
char Tblock::getType() { 
    return 'T'; 
}

const std::vector<int> Tblock::Tpreview {0, 1, 2, 5};

// All Block Rotations
std::vector<std::string> rotationT0 {
    "----", 
    "----", 
    "TTT-", 
    "-T--"
};

std::vector<std::string> rotationT90 {
    "----", 
    "-T--", 
    "TT--", 
    "-T--", 
}; 

std::vector<std::string> rotationT180 {
    "----", 
    "----", 
    "-T--", 
    "TTT-"
};

std::vector<std::string> rotationT270 {
    "----", 
    "T---", 
    "TT--", 
    "T---", 
}; 

std::vector<std::pair<int, int>> Tblock::allFill(int x, int y, int rotation) {
    vector<pair<int, int>> allFilled;
    if (rotation == 0) {
        allFilled.push_back(make_pair(x, y+2));
        allFilled.push_back(make_pair(x+1, y+2));
        allFilled.push_back(make_pair(x+2, y+2));
        allFilled.push_back(make_pair(x+1, y+3));
    } else if (rotation == 1) {
        allFilled.push_back(make_pair(x+1, y+1));
        allFilled.push_back(make_pair(x, y+2));
        allFilled.push_back(make_pair(x+1, y+3));
        allFilled.push_back(make_pair(x+1, y+2));
    } else if (rotation == 2) {
       allFilled.push_back(make_pair(x+1, y+2));
       allFilled.push_back(make_pair(x, y+3));
       allFilled.push_back(make_pair(x+1, y+3));
       allFilled.push_back(make_pair(x+2, y+3));
    } else if (rotation == 3) {
       allFilled.push_back(make_pair(x, y+1));
       allFilled.push_back(make_pair(x, y+2));
       allFilled.push_back(make_pair(x, y+3));
       allFilled.push_back(make_pair(x+1, y+2));
    }
    return allFilled;
}

// Creates a matrix with all possible types of J blocks (all rotations)
const std::vector<std::vector<std::string>> Tblock::TMatrix = {
    rotationT0, 
    rotationT90, 
    rotationT180, 
    rotationT270
};

// Returns the matrix of the block 
std::vector<std::vector<std::string>> Tblock::getBlock() {
    return TMatrix;
}

std::vector<int> Tblock::getPreview() { 
    return Tpreview; 
}