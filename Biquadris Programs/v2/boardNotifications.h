#ifndef __BOARDNOTIFICATIONS_H__
#define __BOARDNOTIFICATIONS_H__

class BaseBoard;

struct BoardNotifications {
  bool score = false;
  bool highScore = false;
  bool onBlindFX = false;
  bool offBlindFX = false;
  bool nextBlock = false;
  bool level = false;
};

#endif