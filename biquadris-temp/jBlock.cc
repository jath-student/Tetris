#include "block.h"
#include "jBlock.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
Jblock::Jblock() : Block(0, 0, 0) {}

// Destructor
Jblock::~Jblock() {}

const std::vector<size_t> Jblock::Jpreview {};

// Returns J for jBlock (type)
char Jblock::getType() { 
    return 'J'; 
}

// All Block Rotations
std::vector<std::string> rotationJ0 {
    "----", 
    "----", 
    "J---", 
    "JJJ-"
};

std::vector<std::string> rotationJ90 {
    "----", 
    "JJ--", 
    "J---", 
    "J---"
}; 

std::vector<std::string> rotationJ180 {
    "----", 
    "----", 
    "JJJ-", 
    "--J-"
}; 

std::vector<std::string> rotationJ270 {
    "----", 
    "-J--", 
    "-J--", 
    "JJ--"
};

// Creates a matrix with all possible types of J blocks (all rotations)
const std::vector<std::vector<std::string>> Jblock::JMatrix = {
    rotationJ0, 
    rotationJ90, 
    rotationJ180, 
    rotationJ270
};

// Returns the matrix of the block 
std::vector<std::vector<std::string>> Jblock::getBlock() {
    return JMatrix;
}

std::vector<size_t> Jblock::getPreview() { 
    return Jpreview; 
}