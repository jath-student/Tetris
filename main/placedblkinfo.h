#ifndef __PLACEDBLKINFO_H__
#define __PLACEDBLKINFO_H__

class PlacedBlkInfo {
  int x, y, levelCreated;
  bool empty = false;

  public:
    PlacedBlkInfo(int xCoord, int yCoord, int lvl); // constructor
    ~PlacedBlkInfo(); // destructor

    // getters
    int getX();
    int getY();
    int getLevelCreated();
    bool getEmpty();

    // setters
    void setX( int xCoord );
    void setY( int yCoord );
    void setLevelCreated(int lvl );
    void setEmpty( bool mt);
};
#endif
