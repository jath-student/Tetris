#include "placedblkinfo.h"

PlacedBlkInfo::PlacedBlkInfo(int xCoord, int yCoord, int lvl) : x{xCoord}, y{yCoord}, levelCreated{lvl} {}

int PlacedBlkInfo::getX() { return x; }
int PlacedBlkInfo::getY() { return y; }
int PlacedBlkInfo::getLevelCreated() { return levelCreated; }
bool PlacedBlkInfo::getEmpty() { return empty; }

void PlacedBlkInfo::setX( int xCoord ) { x = xCoord; }
void PlacedBlkInfo::setY( int yCoord ) { y = yCoord; }
void PlacedBlkInfo::setLevelCreated(int lvl ) { levelCreated = lvl; }
void PlacedBlkInfo::setEmpty( bool mt ) {empty = mt; }

PlacedBlkInfo::~PlacedBlkInfo() {}