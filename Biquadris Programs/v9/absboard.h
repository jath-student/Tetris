#ifndef __ABSBOARD_H__
#define __ABSBOARD_H__

class BaseBoard;

// The abstract board class used to manage the main board
//  and the boards with special effects added
class AbsBoard {
  public:
    virtual void updateBoard(BaseBoard &board) = 0; // updates the board
    virtual ~AbsBoard(); // destructor
};

#endif