#include "Caja.h"
#include <GLUT/glut.h>
#include<stdlib.h>
#ifndef GLOBAL_VARIABLES_CPP_
#define GLOBAL_VARIABLES_CPP_
#include "globalVariables.h"
#endif

Caja::Caja(){
  this->isCaja = true;
}

bool Caja::checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ){
  if(this->columnIndex != playerColumn)return false;

  if(this->translationZ < offsetZ)return false;
  if(status == 3){
    this->isValid = false;
    return false;
  }

  if(status == 1 && heightPlayer >= 3){
    return false;
  }
  system("afplay sounds/broken.wav &");
  return true;
}


void Caja::draw(){
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
  glColor3f(1.0f,1.0f,1.0f);          // Set The Color To Green
  glBindTexture(GL_TEXTURE_2D, boxTexture);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f( 3.0f, 3.0f,-3.0f);          // Top Right Of The Quad (Top)
  glTexCoord2f(0.0, 1.0f);
  glVertex3f(-3.0f, 3.0f,-3.0f);          // Top Left Of The Quad (Top)
  glTexCoord2f(1.0, 1.0f );
  glVertex3f(-3.0f, 3.0f, 3.0f);          // Bottom Left Of The Quad (Top)
  glTexCoord2f(1.0, 0.0);
  glVertex3f( 3.0f, 3.0f, 3.0f);          // Bottom Right Of The Quad (Top)
  glEnd();


  //glColor3f(3.0f,0.5f,0.0f);          // Set The Color To Orange
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f( 3.0f,-3.0f, 3.0f);          // Top Right Of The Quad (Bottom)
  glTexCoord2f(0.0, 1.0f);
  glVertex3f(-3.0f,-3.0f, 3.0f);          // Top Left Of The Quad (Bottom)
  glTexCoord2f(1.0, 1.0f );
  glVertex3f(-3.0f,-3.0f,-3.0f);          // Bottom Left Of The Quad (Bottom)
  glTexCoord2f(1.0, 0.0);
  glVertex3f( 3.0f,-3.0f,-3.0f);          // Bottom Right Of The Quad (Bottom)
  glEnd();

  //glColor3f(3.0f,0.0f,0.0f);          // Set The Color To Red
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f( 3.0f, 3.0f, 3.0f);          // Top Right Of The Quad (Front)
  glTexCoord2f(0.0, 1.0f);
  glVertex3f(-3.0f, 3.0f, 3.0f);          // Top Left Of The Quad (Front)
  glTexCoord2f(1.0, 1.0f );
  glVertex3f(-3.0f,-3.0f, 3.0f);          // Bottom Left Of The Quad (Front)
  glTexCoord2f(1.0, 0.0);
  glVertex3f( 3.0f,-3.0f, 3.0f);          // Bottom Right Of The Quad (Front)
  glEnd();


  glBegin(GL_QUADS);
  //glColor3f(3.0f,3.0f,0.0f);          // Set The Color To Yellow
  glTexCoord2f(0.0, 0.0);
  glVertex3f( 3.0f,-3.0f,-3.0f);          // Bottom Left Of The Quad (Back)
  glTexCoord2f(0.0, 1.0f);
  glVertex3f(-3.0f,-3.0f,-3.0f);          // Bottom Right Of The Quad (Back)
  glTexCoord2f(1.0, 1.0f );

  glVertex3f(-3.0f, 3.0f,-3.0f);          // Top Right Of The Quad (Back)
  glTexCoord2f(1.0, 0.0);
  glVertex3f( 3.0f, 3.0f,-3.0f);          // Top Left Of The Quad (Back)
  glEnd();


  glBegin(GL_QUADS);
  //glColor3f(0.0f,0.0f,3.0f);          // Set The Color To Blue
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-3.0f, 3.0f, 3.0f);          // Top Right Of The Quad (Left)
  glTexCoord2f(0.0, 1.0f);
  glVertex3f(-3.0f, 3.0f,-3.0f);          // Top Left Of The Quad (Left)
  glVertex3f(-3.0f,-3.0f,-3.0f);          // Bottom Left Of The Quad (Left)
  glVertex3f(-3.0f,-3.0f, 3.0f);          // Bottom Right Of The Quad (Left)
  glEnd();

  //glColor3f(3.0f,0.0f,3.0f);          // Set The Color To Violet
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f( 3.0f, 3.0f,-3.0f);          // Top Right Of The Quad (Right)
  glTexCoord2f(0.0, 1.0f);
  glVertex3f( 3.0f, 3.0f, 3.0f);          // Top Left Of The Quad (Right)
  glVertex3f( 3.0f,-3.0f, 3.0f);          // Bottom Left Of The Quad (Right)
  glVertex3f( 3.0f,-3.0f,-3.0f);          // Bottom Right Of The Quad (Right)
  glEnd();

  glDisable(GL_TEXTURE_2D);
                       // Done Drawing The Quad

 glPopMatrix();

}
