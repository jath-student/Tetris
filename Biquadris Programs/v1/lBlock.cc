#include "block.h"
#include "lBlock.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
Lblock::Lblock() : Block(0, 0, 0) {}

// Destructor
Lblock::~Lblock() {}

const std::vector<size_t> Lblock::Lpreview {};

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

std::vector<size_t> Lblock::getPreview() { 
    return Lpreview; 
}