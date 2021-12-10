#include "block.h"
#include "starblock.h"

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
const std::vector<int> starblock::starpreview {0, 0, 0, 0};

// All Block Rotations
const std::vector<std::vector<std::string>> starblock::starMatrix = {
    {"....", "....", "....", "*..."},
    {"....", "....", "....", "*..."},
    {"....", "....", "....", "*..."},
    {"....", "....", "....", "*..."}
};

// Returns the matrix of the block 
std::vector<std::vector<std::string>> starblock::getBlock() {
    return starMatrix;
}

std::vector<int> starblock::getPreview() { 
    return starpreview; 
}