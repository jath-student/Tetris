#include "block.h"
#include "sBlock.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
Sblock::Sblock() : Block(0, 0, 0) {}

// Destructor
Sblock::~Sblock() {}

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

std::vector<int> Sblock::getPreview() { 
    return Spreview; 
}

