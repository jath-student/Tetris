#ifndef __ABSBOARD_H__
#define __ABSBOARD_H__

class BaseBoard;

class AbsBoard {
  public:
    virtual void updateBoard(BaseBoard &board) = 0;
    virtual ~AbsBoard();
};

#endif