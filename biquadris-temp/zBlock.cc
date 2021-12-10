#include "block.h"
#include "zBlock.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
Zblock::Zblock() : Block(0, 0, 0) {}

// Destructor
Zblock::~Zblock() {}

// Returns Z for zBlock (type)
char Zblock::getType() { 
    return 'Z'; 
}

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

std::vector<size_t> Zblock::getPreview() { 
    return Zpreview; 
}

const std::vector<size_t> Zblock::Zpreview {};