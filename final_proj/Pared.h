#ifndef OBSTACLE_H_
#define OBSTACLE_H_
#include "Obstacle.h"
#endif
class Pared :  public Obstacle{

public:
  void draw();
  bool checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ);


};
