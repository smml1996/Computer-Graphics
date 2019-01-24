#include "Hueco.h"
#include <GLUT/glut.h>
#ifndef GLOBAL_VARIABLES_CPP_
#define GLOBAL_VARIABLES_CPP_
#include "globalVariables.h"
#endif
#include <iostream>

using namespace std;

bool Hueco::checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ){
  if(this->translationZ < 22) return false;

  if(this->columnIndex != playerColumn) return false;

  if(status == 1 && heightPlayer >0.0) return false;


  return true;
}

void Hueco::draw(){
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

  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glRotatef(actualAngleHueco, 0,1,0);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, huecoTexture);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f( -3.0f, 0.0f,0.0f);          // Top Right Of The Quad (Top)
  glTexCoord2f(0.0, 1.0f);
  glVertex3f(3.0f, 0.0f,0.0f);          // Top Left Of The Quad (Top)
  glTexCoord2f(1.0, 1.0f );
  glVertex3f(3.0f, 0.0f, -3.0f);          // Bottom Left Of The Quad (Top)
  glTexCoord2f(1.0, 0.0);
  glVertex3f( -3.0f, 0.0f, -3.0f);          // Bottom Right Of The Quad (Top)
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);

  glPopMatrix();
}
