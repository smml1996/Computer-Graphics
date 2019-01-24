#include "Grada.h"
#include <GLUT/glut.h>
#include <iostream>

using namespace std;

bool Grada::checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ){

  if(this->translationZ < 22) return false;
  if(status == 3 && heightPlayer >= 2.5) return false;

  if(status == 1 && heightPlayer >= 2.5) return false;
  return true;
}


void Grada::draw(){
  glPushMatrix();

  glTranslatef(0,0,this->translationZ);
  glBegin(GL_POLYGON);
  glColor3f(1.0f,0.0f,0.0f);          // Set The Color To Red
  glVertex3f(9.0f, 3.0f, 0.0f);          // Top Right Of The Quad (Front)
  glColor3f(0.0f,1.0f,0.0f);          // Set The Color To Red

  glVertex3f(-9.0f, 3.0f, 0.0f);          // Top Left Of The Quad (Front)
  glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Red

  glVertex3f(-9.0f,0.0f, 0.0f);          // Bottom Left Of The Quad (Front)
  glColor3f(1.0f,0.0f,1.0f);          // Set The Color To Red

  glVertex3f( 9.0f,0.0f, 0.0f);          // Bottom Right Of The Quad (Front)
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0f,0.0f,0.0f);
  glVertex3f( 9.0f, 3.0f, 0.0f);
  glColor3f(0.0f,1.0f,0.0f);
  glVertex3f(-9.0f, 3.0f, 0.0f);
  glColor3f(0.0f,0.0f, 0.0f);
  glVertex3f(-9.0f, 3.0f, -10.0f);
  glVertex3f(9.0f, 3.0f, -10.0f);
  glEnd();
  glPopMatrix();
}
