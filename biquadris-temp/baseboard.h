#define __BASEBOARD_H__
#ifndef __BASEBOARD_H__

class BaseBoard : public AbsBoard {
  vector<vector<Cell>> board;
  //bool isAlive;
  Block *currentBlock;
  Block *nextBlock;
  bool isBlind;
  bool isHeavy;
  bool isForce;
  bool lost = false;
  int height;
  int width;
  int score;
  int highScore;
  int player;
  int level;
  AbsLevel *currentLvl;
  
  public:

    BaseBoard(int h, int w, int plyr, int lvl)
    ~Board();

    bool getBlind();
    bool getHeavy();
    bool getForce();
    int getHeight();
    int getWidth();
    int getScore();
    int getHighScore();
    int getPlayer();
    int getLevel();
    bool getLost();

    void setBlind( bool b );
    void setHeavy( bool h );
    void setForce( bool f );
    void setHeight( int h );
    void setWidth( int w );
    void setScore( int s );
    void setHighScore( int hs );
    void setPlayer( int p );
    void setLevel( int l );
    void setLost( bool l );

    void makeBoard();



    void updateBoard(Board &board);

    void setPlayLevel(int lvl, bool rand, string fileName = "");

};
#endif