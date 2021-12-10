#ifndef __PLACEDBLKINFO_H__
#define __PLACEDBLKINFO_H__

class PlacedBlkInfo {
  int x, y, levelCreated;
  bool empty = false;

  public:
    PlacedBlkInfo(int xCoord, int yCoord, int lvl);
    ~PlacedBlkInfo();

    int getX();
    int getY();
    int getLevelCreated();
    bool getEmpty();

    void setX( int xCoord );
    void setY( int yCoord );
    void setLevelCreated(int lvl );
    void setEmpty( bool mt);
};
#endif
