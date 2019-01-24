#ifndef OBSTACLE_H_
#define OBSTACLE_H_
#include "Obstacle.h"
#endif
#include <stdlib.h>
#include <GLUT/glut.h>
#include <iostream>

using namespace std;

int Obstacle::level = 1;
Obstacle::Obstacle(){
  columnIndex =rand() % 3;
  isValid = true;
  translationZ = -75;
  t =glutGet(GLUT_ELAPSED_TIME);
  tbase = glutGet(GLUT_ELAPSED_TIME);
  level = 1;
  actualAngle = 0;
  actualAngleHueco = 0;
  isCoin = false;
  isCaja = false;
}

void Obstacle::setColumnIndex(const int &column){
  this->columnIndex = column;
}

void Obstacle::move(int velocity){
  t = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
  dt = float(t -tbase)/1000.0;// delta t
  tbase = t;
  translationZ+=velocity*dt;
  if(translationZ >= 25.0){
    this->isValid = false;
  }
  actualAngle+=4.5*velocity*dt;
  actualAngleHueco+=4.5*velocity*dt;
  draw();

  if(actualAngle > 360)
    actualAngle-=360;
    if(actualAngleHueco > 360)
      actualAngle-=360;
}
