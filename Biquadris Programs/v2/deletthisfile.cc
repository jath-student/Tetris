#include <iostream>
#include <vector>
#include "tile.h"
#include "tileinfo.h"
#include "board.h"
#include "textdisplay.h"
#include "block.h"
#include "LevelZero.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "LevelFour.h"

using namespace std;

//validMove(int xShift, int yShift, int rotationShift) returns whether a move is valid
bool Board::validMove(int xShift, int yShift, int rotationShift) {
	
	//Edge case for checking gameover
	//Checks if it possible to set the block down
	if (xShift == 0 && yShift == 0 && rotationShift == 0) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int boardY = curBlock->getY() + i;
				int boardX = curBlock->getX() + j;
				char val;
				val = curBlock->getBlock()[curBlock->getRotation()][i][j];
				if (val != '.') {
                                        //Is it still on the board?
                                        if (boardY < 0 || boardY >= static_cast<int>(height) ||
                                                boardX < 0 || boardX >= static_cast<int>(width)) {
                                                return false;
                                        }
                                        if (theBoard[boardY][boardX].getInfo().occupied) {
                                                return false;
                                        }
                                }

			}
		}
		return true;
	}

	//Calculate the effective rotation
	//(i.e. a rotation of 450 degrees is essentially a rotation of 90 degrees)
	int effectiveRotation = (curBlock->getRotation() + rotationShift) % 4;
	
	//Blocks are defined on a 4x4 grid
	for (int i = 0; i < 4; i++) {
		 for (int j = 0; j < 4; j++) {
			 //Determine the char value of the block at the given index
			 char valAtPos = curBlock->getBlock()[effectiveRotation][i][j];
			 int boardY = curBlock->getY() + yShift + i;
			 int boardX = curBlock->getX() + xShift + j;
			 //if the value isn't '.' aka empty space, test if it is legal
			 if (valAtPos != '.') { 
				 //Is it still on the board?
				 if (boardY < 0 || boardY >= static_cast<int>(height) ||
				     boardX < 0 || boardX >= static_cast<int>(width)) {
					return false;
				 }	
				 //Is the position already occupied?
				 if (theBoard[boardY][boardX].getInfo().occupied) {
					 //Is the occupied part outside the 4x4 grid?
					 if (boardY < static_cast<int>(curBlock->getY()) || 
					     boardY > (static_cast<int>(curBlock->getY()) + 3) ||
					     boardX < static_cast<int>(curBlock->getX()) || 
					     boardX > (static_cast<int>(curBlock->getX()) + 3)) {
						 return false;
					 }
					 
					 //If it is on the grid, is it part of the original Block?
					 if (curBlock->getBlock()[curBlock->getRotation()][i + yShift][j + xShift] == '.') {
						 return false;
					 }
				 }
			 }
		 }
	}

	//If all pass, then its a valid move
	return true;
}
//moveBlock(int xShift, int yShift, int rotationShift) shifts a block on the board
void Board::moveBlock(int xShift, int yShift, int rotationShift) {	
	//Note: Setting a block in place is equivalent to moving zero with all parameters
	
	//First, unset the existing position
	
	this->unsetBlock();

	//Then, set in the new position
	
	//Calculate the effective rotation 
	//(i.e. a rotation of 450 degrees is essentially a rotation of 90 degrees)
	
	int effectiveRotation = (curBlock->getRotation() + rotationShift) % 4;

	//Blocks are defined on a 4x4 grid
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			
			//Determine the char value of the block at the given index
			char valAtPos = curBlock->getBlock()[effectiveRotation][i][j];
			int boardY = curBlock->getY() + yShift + i;
			int boardX = curBlock->getX() + xShift + j;

			//if the value isn't '.' aka not empty space, set it in place
			if (valAtPos != '.') {
				theBoard[boardY][boardX].setPiece(valAtPos);
			}
		}
	}
	
	//Update the x, y, and rotation values of the block
	curBlock->setX(curBlock->getX() + xShift);
	curBlock->setY(curBlock->getY() + yShift);
	curBlock->setRotation(effectiveRotation);
}


//Checks lines and adjusts board and score as required
void Board::checkLines() {
	//this method will only be called when a block has been placed, so increase the streak
	if (restingBlocks[restingBlocks.size() - 1][0].getLevelGenerated() == 4) {
		if (curBlock->getType() != '*') {
	       		static_cast<LevelFour*>(curLevel)->increaseStreak();
		} else {
			static_cast<LevelFour*>(curLevel)->setStreak(0);
		}
	}
	//Tracking the total lines cleared
	size_t totalLinesCleared = 0;
	//Only 4 lines can be cleared at once so iterate over the 4 rows
	for (int i = 0; i < 4; i++) {
		if (curBlock->getY() + i < height) {
			//Check if each row has any unoccupied tiles
			bool linePresent = true;
			for (int j = 0; j < static_cast<int>(width); j++) {
				if (!theBoard[curBlock->getY() + i][j].getInfo().occupied) {
					linePresent = false;
					break;
				}
			}

			//If a line is present, replace that row with the row above. Do the same for all
			//row until the the index 1 row. Unset the whole index 0 row.

			if (linePresent) {
				//Find the row that was cleared
				int shiftIndex = curBlock->getY() + i;
				
				//Check if any parts of any existing blocks were cleared and if
				//entire blocks are cleared
				for (int i = restingBlocks.size() - 1; i >= 0; i--) {
					bool needsDeleting = true;
					for (int j = 0; j < 4; j++) {
						if (restingBlocks[i][j].getY() == shiftIndex) {
							restingBlocks[i][j].setCleared(true);
						}
						if (restingBlocks[i][j].getCleared() == false) {
							needsDeleting = false;
						}
						//Special case for Cblock
						if (restingBlocks[i].size() == 1) {
							break;
						}
					}
					
					//If it block is cleared, increase score and delete from vector
					if (needsDeleting == true) {
                                                int lg = restingBlocks[i][0].getLevelGenerated();
                                                score += (1 + lg) * (1 + lg);
						notifications.scoreChanged = true;
        					notifyObservers();
                                                restingBlocks.erase(restingBlocks.begin() + i);
                                        }
				}

				//Replace the cleared row and everything else above it until
				//the index 1 row with the row above it
				for (int i = shiftIndex - 1; i > 0; i--) {
					for (int j = 0; j < static_cast<int>(width); j++) {
						if (theBoard[i][j].getInfo().occupied) {
							theBoard[i + 1][j].setPiece(theBoard[i][j].getInfo().myPiece);
						} else {
							theBoard[i + 1][j].unsetPiece();
						}
					}
				}
				//Unset the whole index 0 row as its new and fresh
				for (int i = 0; i < static_cast<int>(width); i++) {
					theBoard[0][i].unsetPiece();
				}
				totalLinesCleared++;
			}
		}
	}
	if (totalLinesCleared > 0) {
		//The blocks were shifted downwards so increment the Y coords of the blockparts
		for (int i = 0; i < static_cast<int>(restingBlocks.size()); i++) {
                	for (int j = 0; j < 4; j++) {
                        	restingBlocks[i][j].setY(restingBlocks[i][j].getY() + totalLinesCleared);
				//Special case for Cblock
				if (restingBlocks[i].size() == 1) {break;}
                	}
        	}

		//Update score with the formula
		score += (level + totalLinesCleared) * (level + totalLinesCleared);
		notifications.scoreChanged = true;
		notifyObservers();
		//Reset the streak used in Level 4
		if (level == 4) static_cast<LevelFour*>(curLevel)->setStreak(0);
	}
	//if the total lines cleared are 2 or more, prompt the user for a special effect
	if (totalLinesCleared >= 2) effectNeeded = true;

	//Delete existing block
	delete curBlock;
}

		