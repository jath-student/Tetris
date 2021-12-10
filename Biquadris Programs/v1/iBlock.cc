#include "block.h"
#include "iBlock.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
Iblock::Iblock() : Block(0, 0, 0) {}

// Destructor
Iblock::~Iblock() {}

const std::vector<size_t> Iblock::Ipreview {};

// Returns I for iBlock (type)
char Iblock::getType() { 
    return 'I'; 
}

// All Block Rotations
std::vector<std::string> rotationI0 {
    "----", 
    "----", 
    "----", 
    "IIII"
};

std::vector<std::string> rotationI90 {
    "I---", 
    "I---", 
    "I---", 
    "I---"
}; 

std::vector<std::string> rotationI180 {
    "----", 
    "----", 
    "----", 
    "IIII"
}; 

std::vector<std::string> rotationI270 {
    "I---", 
    "I---", 
    "I---", 
    "I---"
};

// Creates a matrix with all possible types of J blocks (all rotations)
const std::vector<std::vector<std::string>> Iblock::IMatrix = {
    rotationI0, 
    rotationI90, 
    rotationI180, 
    rotationI270
};

// Returns the matrix of the block 
std::vector<std::vector<std::string>> Iblock::getBlock() {
    return IMatrix;
}

std::vector<size_t> Iblock::getPreview() { 
    return Ipreview; 
}