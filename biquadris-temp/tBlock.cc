#include "block.h"
#include "tBlock.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
Tblock::Tblock() : Block(0, 0, 0) {}

// Destructor
Tblock::~Tblock() {}

const std::vector<size_t> Tblock::Tpreview {};

// Returns T for tBlock (type)
char Tblock::getType() { 
    return 'T'; 
}

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

std::vector<size_t> Tblock::getPreview() { 
    return Tpreview; 
}
