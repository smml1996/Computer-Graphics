#ifndef OBSTACLE_H_
#define OBSTACLE_H_
#include "Obstacle.h"
#endif
class Grada : public Obstacle{
float actualHeight = 3;
bool isDescending = false;
public:
  void draw();
  bool checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ);

};
