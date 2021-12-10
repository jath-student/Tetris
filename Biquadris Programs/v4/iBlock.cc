#include "block.h"
#include "iBlock.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Constructor
Iblock::Iblock() : Block(0, 0, 0) {}

// Destructor
Iblock::~Iblock() {}

const std::vector<int> Iblock::Ipreview {0, 1, 2, 3};

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

std::vector<std::pair<int, int>> Iblock::allFill(int x, int y, int rotation) {
    vector<pair<int, int>> allFilled;
    if (rotation == 0 || rotation == 2) {
        allFilled.push_back(make_pair(x, y+3));
        allFilled.push_back(make_pair(x+1, y+3));
        allFilled.push_back(make_pair(x+2, y+3));
        allFilled.push_back(make_pair(x+3, y+3));
    } else {
        allFilled.push_back(make_pair(x, y));
        allFilled.push_back(make_pair(x, y+1));
        allFilled.push_back(make_pair(x, y+2));
        allFilled.push_back(make_pair(x, y+3));
    }
    return allFilled;
}

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

std::vector<int> Iblock::getPreview() { 
    return Ipreview; 
}