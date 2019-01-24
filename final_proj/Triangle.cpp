#include "Triangle.h"
#include <GLUT/glut.h>
#include <iostream>

using namespace std;


bool Triangle::checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ){

  if(this->columnIndex != playerColumn)return false;

  if(this->translationZ < 22.0)return false;
  if(status == 3){
    this->isValid = false;
    return false;
  }

  if(status == 1 && heightPlayer >= 2.5){
    return false;
  }
  return true;
}

void Triangle::draw(){
  glPushMatrix();
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
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f,0.0f,0.0f);          // Red
  glVertex3f( 0.0f, 3.0f, 0.0f);          // Top Of Triangle (Front)
  glColor3f(0.0f,1.0f,0.0f);          // Green
  glVertex3f(-3.0f,-3.0f, 3.0f);          // Left Of Triangle (Front)
  glColor3f(0.0f,0.0f,1.0f);          // Blue
  glVertex3f( 3.0f,-3.0f, 3.0f);          // Right Of Triangle (Front)
  glColor3f(1.0f,0.0f,0.0f);          // Red
  glVertex3f( 0.0f, 3.0f, 0.0f);          // Top Of Triangle (Right)
  glColor3f(0.0f,0.0f,1.0f);          // Blue
  glVertex3f( 3.0f,-3.0f, 3.0f);          // Left Of Triangle (Right)
  glColor3f(0.0f,1.0f,0.0f);          // Green
  glVertex3f( 3.0f,-3.0f, -3.0f);         // Right Of Triangle (Right)
  glColor3f(1.0f,0.0f,0.0f);          // Red
  glVertex3f( 0.0f, 3.0f, 0.0f);          // Top Of Triangle (Back)
  glColor3f(0.0f,1.0f,0.0f);          // Green
  glVertex3f( 3.0f,-3.0f, -3.0f);         // Left Of Triangle (Back)
  glColor3f(0.0f,0.0f,1.0f);          // Blue
  glVertex3f(-3.0f,-3.0f, -3.0f);         // Right Of Triangle (Back)
  glColor3f(1.0f,0.0f,0.0f);          // Red
  glVertex3f( 0.0f, 3.0f, 0.0f);          // Top Of Triangle (Left)
  glColor3f(0.0f,0.0f,1.0f);          // Blue
  glVertex3f(-3.0f,-3.0f,-3.0f);          // Left Of Triangle (Left)
  glColor3f(0.0f,1.0f,0.0f);          // Green
  glVertex3f(-3.0f,-3.0f, 3.0f);          // Right Of Triangle (Left)
  glEnd();                        // Done Drawing The Pyramid
  glPopMatrix();
}
