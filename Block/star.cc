#include "block.h"
#include "star.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
starblock::starblock() : Block(0, 0, 0) {}

// Destructor
starblock::~starblock() {}

// Returns L for lBlock (type)
char starblock::getType() { 
    return '*'; 
}

// All Block Rotations
const std::vector<std::vector<std::string>> starblock::starMatrix = {
    "*"
};

// Returns the matrix of the block 
std::vector<std::vector<std::string>> Lblock::getBlock() {
    return starMatrix;
}

std::vector<size_t> Lblock::getPreview() { 
    return starpreview; 
}