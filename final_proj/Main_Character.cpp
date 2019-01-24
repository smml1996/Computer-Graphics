#include "Main_Character.h"
#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_
#include "TextureManager.h"
#endif
#include <iostream>


#include <GLUT/glut.h>

using namespace std;


Main_Character::Main_Character(){
  actualColumn = 1;
  status =0;
  actualAngle = 0;
  score = 0;

}

Main_Character::~Main_Character(){
  for(int i =0; i < bullets.size(); i++){
    bullets[i]->~Bullet();
  }

  bullets.erase(bullets.begin(), bullets.end());
}

void Main_Character::jump(){
  this->status = 1;
  tbaseSpecialStatus = glutGet(GLUT_ELAPSED_TIME);
}

void Main_Character::deslizar(){
  this->status = 2;
  tbaseSpecialStatus = glutGet(GLUT_ELAPSED_TIME);
}


void Main_Character::protect(){
    this->status = 3;
    tbaseSpecialStatus = glutGet(GLUT_ELAPSED_TIME);

}

void Main_Character::drawBullets(const int &velocity){

  for(int i =0; i < bullets.size(); i++){
    if(bullets[i]->isValid)
      bullets[i]->move(velocity);
    else{
      bullets[i]->~Bullet();
      bullets.erase(bullets.begin() + i);
    }
  }
}

void Main_Character::throwbullet(){
  bullets.push_back(new Bullet(this->actualColumn));
}

void Main_Character::draw(const int &velocity){
  drawBullets(velocity);

  glColor3f(1.0f,1.0f,1.0f);
  t = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
  float dt = float(t -tbase)/1000.0;// delta t
  tbase = t;
   y = 0;
  sizeCharacter = 3;
  glPushMatrix();

  if(this->status == 1 ){
    float t = float(glutGet(GLUT_ELAPSED_TIME) - tbaseSpecialStatus)/1000.00;
    V_0 = 6 + (20)/4.0;
    y = V_0*t - 9*t*t;
    if(y < 0){
      this->status = 0;
      y = 0;
    }
  }else if(this->status == 2){

    float t = float(glutGet(GLUT_ELAPSED_TIME) - tbaseSpecialStatus)/1000.00;
    sizeCharacter = 3 * t;
    if(sizeCharacter  >=3 ){
      this->status =0;
    }
  }else if(this->status == 3){
    glColor3d(255,215,0);
    float t = float(glutGet(GLUT_ELAPSED_TIME) - tbaseSpecialStatus)/1000.00;
    if(t > 0.5){
      this->status = 0;
    }
  }

    switch (actualColumn) {
      case 0:
        glTranslatef(-6,y,22);
        break;
      case 1:
        glTranslatef(0,y,22);
        break;
      case 2:
        glTranslatef(6,y,22);
        break;
    }

    /*
    if(this->status == 3){
      glBindTexture(GL_TEXTURE_2D, this->textureProtected);
    }else{
      glBindTexture(GL_TEXTURE_2D, this->textureNormal);
    }*/

    glRotatef(actualAngle, -1,0,0);
    /*
      glEnable(GL_TEXTURE_2D);
      glTexCoord2f(0.0, 0.0);//coordenadas de textura
      GLUquadric* cuadratic = gluNewQuadric();
      gluQuadricTexture(cuadratic,this->textureNormal );
    */
    glutWireSphere(sizeCharacter,50, 50);
    glDisable(GL_TEXTURE_2D);

  glPopMatrix();
  actualAngle+=4.5*velocity*dt;
  if(actualAngle>360)
    actualAngle -=360;
}
