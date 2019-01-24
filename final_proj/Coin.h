#ifndef OBSTACLE_H_
#define OBSTACLE_H_
#include "Obstacle.h"
#endif


class Coin : public Obstacle{
public:
  Coin();
  void draw();
  bool checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ);


};
