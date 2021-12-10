#include "block.h"
#include "jBlock.h"

#include <vector>
#include <string>

using namespace std;

// Constructor
Jblock::Jblock() : Block(0, 0, 0) {}

// Destructor
Jblock::~Jblock() {}

const std::vector<int> Jblock::Jpreview {0, 4, 5, 6};

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

std::vector<std::pair<int, int>> Jblock::allFill(int x, int y, int rotation) {
    vector<pair<int, int>> allFilled;
    if (rotation == 0) {
        allFilled.push_back(make_pair(x, y+2));
        allFilled.push_back(make_pair(x, y+3));
        allFilled.push_back(make_pair(x+1, y+3));
        allFilled.push_back(make_pair(x+2, y+3));
    } else if (rotation == 1) {
        allFilled.push_back(make_pair(x, y+1));
        allFilled.push_back(make_pair(x, y+2));
        allFilled.push_back(make_pair(x, y+3));
        allFilled.push_back(make_pair(x+1, y+1));
    } else if (rotation == 2) {
        allFilled.push_back(make_pair(x, y+2));
        allFilled.push_back(make_pair(x+1, y+2));
        allFilled.push_back(make_pair(x+2, y+2));
        allFilled.push_back(make_pair(x+2, y+3));
    } else if (rotation == 3) {
       allFilled.push_back(make_pair(x, y+3));
       allFilled.push_back(make_pair(x+1, y+1));
       allFilled.push_back(make_pair(x+1, y+2));
       allFilled.push_back(make_pair(x+1, y+3));
    }
    return allFilled;
}

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

std::vector<int> Jblock::getPreview() { 
    return Jpreview; 
}