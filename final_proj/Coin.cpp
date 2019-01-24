#include <GLUT/glut.h>
#include "Coin.h"
#include <cmath>
#include<stdlib.h>

using namespace std;

Coin::Coin(){
  isCoin = true;
}
bool Coin::checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ){
  if(this->columnIndex != playerColumn)return false;

  if(this->translationZ < 22.0)return false;
  if(status == 3){
    this->isValid = false;
    return false;
  }

  if(status == 1 && heightPlayer >= 3){
    return false;
  }
  system("afplay sounds/coin.wav &");

  return true;
}

void Coin::draw(){

  glPushMatrix();
  glColor3f(1.0f, 1.0f, 0.0f);
  switch(this->columnIndex){
    case 0:
      //left column
      glTranslatef(-6,0,this->translationZ);
      break;
    case 1:
        //center column
        glTranslatef(0,0,this->translationZ);
      break;
    case 2:
      //right column
      glTranslatef(6,0,this->translationZ);
      break;
  }
  glRotatef(actualAngle, 0,1,0);

  glBegin(GL_POLYGON);
    //circle front

    for(int i =0; i < 360; i+=12){
      glVertex3f(2*cos(i*3.141592653/180), 2*sin(i*3.141592653/180),0);
    }

  glEnd();

  glBegin(GL_POLYGON);
    //circle back
    for(int i =0; i < 360; i+=12){
      glVertex3f(2*cos(i*3.141592653/180), 2*sin(i*3.141592653/180),-1);
    }

  glEnd();

  float tempX,tempY;

  glColor3f((153.0/255.0), (153.0/255.0), 0.0f);
    //circle back
    for(int i =0; i < 360; i+=12){
      tempX = 2*cos(i*3.141592653/180);
      tempY =  2*sin(i*3.141592653/180);
      glBegin(GL_LINES);
      glVertex3f(tempX, tempY,0);
      glVertex3f(tempX, tempY,-1);

      glEnd();
    }






  glPopMatrix();

}
