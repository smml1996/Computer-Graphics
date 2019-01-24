#ifndef OBSTACLE_H_
#define OBSTACLE_H_
#include "Obstacle.h"
#endif

#include <iostream>
#include <vector>

using namespace std;

#define HUECO 0
#define TUNEL 1
#define TRIANGLE 2
#define PARED 3
#define CAJA 4
#define COIN 5



class CompositeObstacle : public Obstacle{
  pair<int, int> getColumns();
  vector<Obstacle *> unitObstacles;
  int velocity;
  public:
    void createComposite(int type, int velocity);
    bool checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ);

    void draw();
};
