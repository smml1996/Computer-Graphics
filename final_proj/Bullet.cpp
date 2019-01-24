#include <GLUT/glut.h>
#include "Bullet.h"
#include <iostream>

using namespace std;

Bullet::Bullet(const int & column){
  this->column = column;
  t = 0;
  tbase = glutGet(GLUT_ELAPSED_TIME);

  this->isValid = true;
  this->offsetZ = 18;
  switch (column) {
    case 0:
      this->offsetX = -6;
      break;
    case 1:
    this->offsetX = 0;
      break;
    case 2:
      this->offsetX = 6;
      break;
  }

}

Bullet::~Bullet(){

}

void Bullet::move(const int &velocity){
  glColor3d(255, 0, 255);

  t = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
  float dt = float(t -tbase)/1000.0;// delta t
  tbase = t;
  this->offsetZ-= dt*velocity;
  if(this->offsetZ < -70){
    isValid = false;
    return;
  }
  glPushMatrix();


  glTranslatef(offsetX, 0, offsetZ);

  glutSolidSphere(1, 20, 20);

  glPopMatrix();

}
