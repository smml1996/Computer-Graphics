#ifndef OBSTACLE_H_
#define OBSTACLE_H_
#include "Obstacle.h"
#endif
class FireBall: public Obstacle{
  bool moveRight = true;
  float offsetX = 0;
  void getRandomColor();
public:
  void draw();
  bool checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ);


};
