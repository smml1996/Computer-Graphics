#include "FireBall.h"
#include <GLUT/glut.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#define PI 3.14159265359

using namespace std;


bool FireBall::checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ){
  if(this->translationZ < 22) return false;

  if(status == 3) return false;

  if(status ==1 && heightPlayer > 3.00) return false;

  if(playerColumn == 0 && offsetX > -3) return false;

  if(playerColumn == 2 && offsetX < 3) return false;

  if(playerColumn == 1 && (offsetX < -3 || offsetX > 3)) return false;

  return true;
}


void FireBall::getRandomColor(){


    int color  = rand()% 7;
    if(color == 0){
      glColor3f(1.0f, 0, 0);
    }else if(color == 1){
      glColor3f(255/255.0, 255/255.0, 51/255.0);

    }else if(color == 2){
      glColor3f(255/255.0, 128/255.0, 0/255.0);

    }else if(color == 3){
      glColor3f(255/255.0, 178/255.0, 102/255.0);
    }else if(color == 4){
      glColor3f(255/255.0, 255/255.0, 53/255.0);
    }else{
      glColor3f(1.0f, 153/255.0, 51/255.0);
    }

}


void FireBall::draw(){
  glPushMatrix();
  glTranslatef(offsetX,0,this->translationZ);
  if(this->moveRight){
    offsetX+= 20*dt;
    if(offsetX> 9){
      this->moveRight = false;
    }
  }else{
    offsetX-=20*dt;

    if(offsetX < -9){
      this->moveRight = true;
    }
  }
  float x,y;


  for(int i =0; i <360; i+=1){
    glPushMatrix();
    glRotatef(i,0,1,0);

    glBegin(GL_LINE_LOOP);

    getRandomColor();
    for(int j =0; j < 360; j+=6){


      x = cos(j*PI/180);
      y = sin(j*PI/180);
      glVertex3d(x, y, 0);
    }
    glEnd();
    glPopMatrix();

  }
  glPopMatrix();
}
