#include "block.h"
#include "oBlock.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
Oblock::Oblock() : Block(0, 0, 0) {}

// Destructor
Oblock::~Oblock() {}

const std::vector<size_t> Oblock::Opreview {};

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

std::vector<size_t> Oblock::getPreview() { 
    return Opreview; 
}