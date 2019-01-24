#include "Tunel.h"
#include <GLUT/glut.h>


bool Tunel::checkColision(const int &status, const int&playerColumn, const float &heightPlayer, const float &sizePlayer, const float &offsetZ){
  if(this->translationZ < 22) return false;
  if(playerColumn != this->columnIndex) return false;
  if(status == 3) return false;

  if(status == 2 && sizePlayer<=2){
    return false;
  }
  return true;
}

void Tunel::draw(){
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

    glBegin(GL_LINE_LOOP);

      glColor3f(1.0f,0.0f,0.0f);
      glVertex3f( -3.0f, 0.0f, 0.0f);          // Top Of Triangle (Front)
      glVertex3f( -2.0f, 0.0f, 0.0f);          // Top Of Triangle (Front)
      glColor3f(0.0f,1.0f,0.0f);
      glVertex3f( -2.0f, 2.0f, 0.0f);          // Top Of Triangle (Front)

      glColor3f(0.0f,0.0f,1.0f);
      glVertex3f( 2.0f, 2.0f, 0.0f);          // Top Of Triangle (Front)

      glColor3f(0.0f,0.8f,1.0f);
      glVertex3f( 2.0f, 0.0f, 0.0f);          // Top Of Triangle (Front)


      glColor3f(0.0f,0.8f,1.0f);
      glVertex3f( 3.0f, 0.0f, 0.0f);

      glColor3f(1.0f,0.8f,1.0f);
      glVertex3f( 3.0f, 3.0f, 0.0f);

      glColor3f(0.0f,1.0f,0.0f);
      glVertex3f( -3.0f, 3.0f, 0.0f);
    glEnd();


  glPopMatrix();
}
