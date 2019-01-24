#ifndef OBSTACLE_GENERATOR_H_
#define OBSTACLE_GENERATOR_H_
#include "ObstacleGenerator.h"
#endif
#ifndef COMPOSITE_OBSTACLE_H_
#define COMPOSITE_OBSTACLE_H_
#include "CompositeObstacle.h"
#endif


#ifndef OBSTACLE_H_
#define OBSTACLE_H_
#include "Obstacle.h"
#endif
#include "FireBall.h"
#include "Grada.h"

#ifndef HUECO_H_
#define HUECO_H_
#include "Hueco.h"
#endif

#ifndef TUNEL_H_
#define TUNEL_H_
#include "Tunel.h"
#endif


#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "Triangle.h"
#endif

#ifndef PARED_H_
#define PARED_H_
#include "Pared.h"
#endif


#ifndef CAJA_H_
#define CAJA_H_
#include "Caja.h"
#endif
#ifndef COIN_H_
#define COIN_H_
#include "Coin.h"
#endif
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* t */
#include <GLUT/glut.h>
#include <iostream>


using namespace std;


void ObstacleGenerator::announceGameOver(){

  for(int i =0; i < obstacles.size(); i++){
    obstacles[i]->~Obstacle();
  }

  obstacles.erase(obstacles.begin(), obstacles.end());

  mc->~Main_Character();
}
ObstacleGenerator::ObstacleGenerator(const int &velocity, Main_Character *mc){
  this->level = 1;
  this->velocity = velocity;
  this->mc = mc;
  t = 0;
  tbase = 0;
  delta = 0.0;
  countObstacles = 0;
  srand(time(NULL));
  isGameOver = false;
}

void ObstacleGenerator::moveObstacles(){

  if(isGameOver) return;


  generateObstacles();

  for(int i=0; i < obstacles.size();){
    if(!obstacles[i]->isValid){
      obstacles[i]->~Obstacle();
      obstacles.erase(obstacles.begin() + i);
    }else{
      i++;
    }
  }


  for(int i = 0; i < obstacles.size(); i++){
    obstacles[i]->move(velocity);
    if(obstacles[i]->checkColision(mc->status, mc->actualColumn, mc->y, mc->sizeCharacter, 22.0)){
      if(obstacles[i]->isCoin){
        mc->score+=10;
        obstacles[i]->~Obstacle();
        obstacles.erase(obstacles.begin() + i);
        i--;
      }else{
        isGameOver = true;
        announceGameOver();
      }
    }else if(obstacles[i]->isCaja){
        for(int b = 0; b < mc->bullets.size(); b++){
          if(obstacles[i]->checkColision(0, mc->bullets[b]->column, 0.0, 0.0, mc->bullets[b]->offsetZ)){

            obstacles.erase(obstacles.begin() + i);
            mc->bullets.erase(mc->bullets.begin() + b);
            i--;
            break;

          }
        }
    }

  }
}

void ObstacleGenerator::levelUp(){
  level++;
  Obstacle::level+=1;
}
void ObstacleGenerator::generateObstacles(){

  t = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
  delta = float(t -tbase)/1000.0;// delta t
    if(this->level == 1){
      if((obstacles.size() < 2 && delta > 2.0) || obstacles.size() == 0){
        countObstacles ++;
        if(countObstacles % ((rand() % 4)+1) == 0){
          obstacles.push_back(new Coin);
          return;
        }
        int randomNum = rand() % 101;
        bool isComposite = false;

        int randomNum2 = rand()%101;
        if(randomNum2 < 31 ){
          isComposite = true;
          obstacles.push_back(new CompositeObstacle);
        }
        if(randomNum <51){
          if(isComposite){
             static_cast<CompositeObstacle*>(obstacles[obstacles.size()-1])->createComposite(TRIANGLE, this->velocity);
          }else
            obstacles.push_back(new Triangle);
        }else if(randomNum < 76){
          if(isComposite){
            static_cast<CompositeObstacle*>(obstacles[obstacles.size()-1])->createComposite(HUECO, this->velocity);
          }else
            obstacles.push_back(new Hueco);
        }else{
          if(isComposite){
            static_cast<CompositeObstacle*>(obstacles[obstacles.size()-1])->createComposite(CAJA, this->velocity);
          }else
            obstacles.push_back(new Caja);
        }
        tbase = t;

      }


    }else if(this->level ==  2){

      if((obstacles.size() < 4 && delta > 1.0) || obstacles.size() == 0){
        countObstacles ++;
        if(countObstacles % ((rand() % 7) + 1) == 0){
          obstacles.push_back(new Coin);
          return;
        }
      int randomNum = rand() % 301;
      bool isComposite = false;

      int randomNum2 = rand()%101;
      if(randomNum2 < 61 ){
        isComposite = true;
        obstacles.push_back(new CompositeObstacle);
      }
      if(randomNum <51){
        if(isComposite){
           static_cast<CompositeObstacle*>(obstacles[obstacles.size()-1])->createComposite(TRIANGLE, this->velocity);
        }else
          obstacles.push_back(new Triangle);
      }else if(randomNum < 101){
        if(isComposite){
          static_cast<CompositeObstacle*>(obstacles[obstacles.size()-1])->createComposite(CAJA, this->velocity);
        }else
          obstacles.push_back(new Caja);
      }else if(randomNum < 151){
        if(isComposite){
          static_cast<CompositeObstacle*>(obstacles[obstacles.size()-1])->createComposite(HUECO, this->velocity);
        }else
          obstacles.push_back(new Hueco);
      }else if(randomNum < 201){
        if(isComposite){
          static_cast<CompositeObstacle*>(obstacles[obstacles.size()-1])->createComposite(TUNEL, this->velocity);
        }else
          obstacles.push_back(new Tunel);
      }else if(randomNum < 251){
        if(isComposite){
          static_cast<CompositeObstacle*>(obstacles[obstacles.size()-1])->createComposite(PARED, this->velocity);
        }else
          obstacles.push_back(new Pared);
      }
      tbase = t;

    }
    }else{
        if((obstacles.size() < 6 && delta > 0.75) || obstacles.size() == 0){
          countObstacles ++;
          int randomNum = rand() % 401;
          if(countObstacles % ((rand() % 10) +1) == 0){
            obstacles.push_back(new Coin);
            return;
          }

          bool isComposite = false;

          int randomNum2 = rand()%101;
          if(randomNum2 < 86 ){
            isComposite = true;
            obstacles.push_back(new CompositeObstacle);
          }
          if(randomNum <51){
            if(isComposite){
               static_cast<CompositeObstacle*>(obstacles[obstacles.size()-1])->createComposite(TRIANGLE, this->velocity);
            }else
              obstacles.push_back(new Triangle);
          }else if(randomNum < 101){
            if(isComposite){
              static_cast<CompositeObstacle*>(obstacles[obstacles.size()-1])->createComposite(CAJA, this->velocity);
            }else
              obstacles.push_back(new Caja);
          }else if(randomNum < 151){
            if(isComposite){
              static_cast<CompositeObstacle*>(obstacles[obstacles.size()-1])->createComposite(HUECO, this->velocity);
            }else
              obstacles.push_back(new Hueco);
          }else if(randomNum < 201){
            if(isComposite){
              static_cast<CompositeObstacle*>(obstacles[obstacles.size()-1])->createComposite(TUNEL, this->velocity);
            }else
              obstacles.push_back(new Tunel);
          }else if(randomNum < 251){
            if(isComposite){
              static_cast<CompositeObstacle*>(obstacles[obstacles.size()-1])->createComposite(PARED, this->velocity);
            }else
              obstacles.push_back(new Pared);
          }else if(randomNum < 301){
            obstacles.push_back(new Grada);
          }else if(randomNum < 401){
            obstacles.push_back(new FireBall);
          }
          tbase = t;
      }

    }



  }
