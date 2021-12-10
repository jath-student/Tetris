#define __ABSBOARD_H__
#ifndef __ABSBOARD_H__

class AbsBoard {

  public:
    virtual ~AbsBoard();
    virtual void updateBoard(Board &board);
};

#endif