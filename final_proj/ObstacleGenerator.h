#include <vector>

#ifndef OBSTACLE_H_
#define OBSTACLE_H_
#include "Obstacle.h"
#endif
#ifndef MAIN_CHARACTER_H_
#define MAIN_CHARACTER_H_
#include "Main_Character.h"
#endif

class ObstacleGenerator{


  std::vector<Obstacle *> obstacles;
  int t;
  int tbase;
  float delta;
  int countObstacles;
  Main_Character *mc;

  void announceGameOver();

public:
  int level;
  int velocity;
  bool isGameOver;

  void generateObstacles();
  void moveObstacles();
  ObstacleGenerator(const int &velocity, Main_Character *mc);
  void levelUp();

};
