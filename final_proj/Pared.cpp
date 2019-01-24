#include "Pared.h"
#include <GLUT/glut.h>
#ifndef GLOBAL_VARIABLES_CPP_
#define GLOBAL_VARIABLES_CPP_
#include "globalVariables.h"
#endif

bool Pared::checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ){

  if(this->translationZ < 22) return false;
  if(status == 3) return false;

  if(this->columnIndex != playerColumn) return false;

  return true;
}

void Pared::draw(){
    glPushMatrix();

      switch (this->columnIndex) {
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
      glBindTexture(GL_TEXTURE_2D, wallTexture);
      glEnable(GL_TEXTURE_2D);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);
      glVertex3f( 3.0f, 0.0f,0.0f);          // Top Right Of The Quad (Top)
      glTexCoord2f(0.0, 1.0f);
      glVertex3f(3.0f, 9.0f,0.0f);          // Top Left Of The Quad (Top)
      glTexCoord2f(1.0, 1.0f );
      glVertex3f(-3.0f, 9.0f, 0.0f);          // Bottom Left Of The Quad (Top)
      glTexCoord2f(1.0, 0.0);
      glVertex3f( -3.0f, 0.0f, 0.0f);          // Bottom Right Of The Quad (Top)
      glEnd();
      glDisable(GL_TEXTURE_2D);


    glPopMatrix();
}
