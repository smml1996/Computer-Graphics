#ifndef COMPOSITE_OBSTACLE_H_
#define COMPOSITE_OBSTACLE_H_
#include "CompositeObstacle.h"
#endif

#include <iostream>
#include <vector>

#ifndef OBSTACLE_H_
#define OBSTACLE_H_
#include "Obstacle.h"
#endif
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* t */

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
using namespace std;

bool CompositeObstacle::checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ){

  for(int i =0; i < unitObstacles.size(); i++){
      if(unitObstacles[i]->checkColision(status, playerColumn, heightPlayer, sizePlayer, offsetZ)) return true;
  }

  return false;
}

pair<int, int> CompositeObstacle::getColumns(){
  pair<int, int> answer;
  answer.first = rand()%3;

  int tempRandomNumber = rand()% 4;

  if(answer.first == 1){
    if(tempRandomNumber%4 == 0){
      answer.second = 0;
    }else{
      answer.first = 2;
    }
  }else if(answer.first == 0){
    if(tempRandomNumber%4 == 0){
      answer.second = 1;
    }else{
      answer.first = 2;
    }
  }else{
    if(tempRandomNumber%4 == 0){
      answer.second = 0;
    }else{
      answer.first = 1;
    }
  }

  return answer;
}

void CompositeObstacle::createComposite(int type, int velocity){

  int randomNumber = 100;
  int numberOfObstacles = 3;
  this->velocity = velocity;
  if(type != PARED){

    if(this->level == 1){

        if(randomNumber >20){
          numberOfObstacles = 2;
        }
    }else if(this->level ==2){
      if(randomNumber > 30){
        numberOfObstacles = 2;
      }
    }else{

      if(randomNumber > 70){
          numberOfObstacles = 2;
      }
    }
  }else{
    numberOfObstacles = 2;
  }


  if(numberOfObstacles == 3){
      if(type == TRIANGLE){
        for(int i =0; i<3; i++){
          unitObstacles.push_back(new Triangle);
          unitObstacles[i]->setColumnIndex(i);
        }
      }else if(type == HUECO){
        for(int i =0; i<3; i++){
          unitObstacles.push_back(new Hueco);
          unitObstacles[i]->setColumnIndex(i);
        }
      }else if(type == TUNEL){
        for(int i =0; i<3; i++){
          unitObstacles.push_back(new Tunel);
          unitObstacles[i]->setColumnIndex(i);
        }
      }else if(type == CAJA){
        this->isCaja = true;
        for(int i =0; i<3; i++){
          unitObstacles.push_back(new Caja);
          unitObstacles[i]->setColumnIndex(i);
        }
      }else if(type == COIN){
        for(int i =0; i<3; i++){
          unitObstacles.push_back(new Coin);
          unitObstacles[i]->setColumnIndex(i);
        }
      }
  }else{
    pair<int, int > columns = getColumns();
    if(type == TRIANGLE){

      unitObstacles.push_back(new Triangle);
      unitObstacles[unitObstacles.size()-1]->setColumnIndex(columns.first);

      unitObstacles.push_back(new Triangle);
      unitObstacles[unitObstacles.size()-1]->setColumnIndex(columns.second);

    }else if(type == HUECO){

      unitObstacles.push_back(new Hueco);
      unitObstacles[unitObstacles.size()-1]->setColumnIndex(columns.first);
      unitObstacles.push_back(new Hueco);
      unitObstacles[unitObstacles.size()-1]->setColumnIndex(columns.second);

    }else if(type == TUNEL){

      unitObstacles.push_back(new Tunel);
      unitObstacles[unitObstacles.size()-1]->setColumnIndex(columns.first);
      unitObstacles.push_back(new Tunel);
      unitObstacles[unitObstacles.size()-1]->setColumnIndex(columns.second);

    }else if(type == CAJA){
      this->isCaja = true;

      unitObstacles.push_back(new Caja);
      unitObstacles[unitObstacles.size()-1]->setColumnIndex(columns.first);
      unitObstacles.push_back(new Caja);
      unitObstacles[unitObstacles.size()-1]->setColumnIndex(columns.second);

    }else if(type == PARED){

        unitObstacles.push_back(new Pared);
        unitObstacles[unitObstacles.size()-1]->setColumnIndex(columns.first);
        unitObstacles.push_back(new Pared);
        unitObstacles[unitObstacles.size()-1]->setColumnIndex(columns.second);
    }else if(type == COIN){
      for(int i =0; i<2; i++){
        unitObstacles.push_back(new Coin);
        unitObstacles[unitObstacles.size()-1]->setColumnIndex(columns.first);
        unitObstacles.push_back(new Coin);
        unitObstacles[unitObstacles.size()-1]->setColumnIndex(columns.second);
      }
    }
  }
}


void CompositeObstacle::draw(){
  for(int i =0; i<unitObstacles.size();i++){
      unitObstacles[i]->move(this->velocity);
  }
}
