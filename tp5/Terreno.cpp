
#include "Terreno.h"
#include <GLUT/glut.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "TextureManager.h"
#ifndef GLOBAL_H_
#define GLOBAL_H_
#include "global.h"
#endif
using namespace std;



void Terreno::display() {

  glColor3f(1.0f,1.0f, 1.0f);
  /*  ejercicio 1 - 2 */

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glInterleavedArrays(GL_T2F_N3F_V3F, sizeof(PuntoTerreno), &lista_puntos[0].s);
  glDrawElements(GL_TRIANGLES, 60000, GL_UNSIGNED_INT, (void*)lista_indices);


  /* ejercicio 3 */

  computeNormals();
/*
  float x,y,z,s,t;
  //glBindTexture(GL_TEXTURE_2D, texture);
//  glEnable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLES);
    for(int i = 0; i < 60000; i++){

      s = lista_puntos[lista_indices[i]].s;
      t = lista_puntos[lista_indices[i]].t;
      x = lista_puntos[lista_indices[i]].x;
      y = lista_puntos[lista_indices[i]].y;
      z = lista_puntos[lista_indices[i]].z;
    //  glTexCoord2f(s, t);
      glVertex3d(x,y,z);

    }
  glEnd();
  //glDisable(GL_TEXTURE_2D);*/
}

Terreno::Terreno(){
  nb_pt_x = 101;
  nb_pt_z = 101;
  dist_x = 50;
  dist_z = -50;

}

Terreno::~Terreno(){
  /*
  for(int i =0; i < lista_puntos.size(); i++){
    delete lista_puntos[i];
  }*/


}

void Terreno::computeNormals(){

  float ax,bx,ay,by,az,bz;

  vector< vector<float> > triangleNormals;

  vector<float> temp;

  for(int i =0; i < 60000; i+=3){
    temp.clear();
    ax = lista_puntos[lista_indices[i]].x - lista_puntos[lista_indices[i+1]].x;
    ay = lista_puntos[lista_indices[i]].y - lista_puntos[lista_indices[i+1]].y;
    az = lista_puntos[lista_indices[i]].z - lista_puntos[lista_indices[i+1]].z;
    bx = lista_puntos[lista_indices[i]].x - lista_puntos[lista_indices[i+2]].x;
    by = lista_puntos[lista_indices[i]].y - lista_puntos[lista_indices[i+2]].y;
    bz = lista_puntos[lista_indices[i]].z - lista_puntos[lista_indices[i+2]].z;
    temp.push_back(ay*bz - by*az);
    temp.push_back(ax*bz - bx*az);
    temp.push_back(az*by - ay*bx);
    triangleNormals.push_back(temp);
  }

  vector<int> count(101*101, 0);

  int index;
  for(int i =0; i < 60000; i++){
      index = lista_indices[i];
      count[index]++;
      lista_puntos[index].nx+= triangleNormals[i/3][0];
      lista_puntos[index].ny+=triangleNormals[i/3][1];
      lista_puntos[index].nz+=triangleNormals[i/3][2];
  }

  for(int i =0; i < count.size(); i++){
    lista_puntos[i].nx/=float(count[i]);
    lista_puntos[i].ny/=float(count[i]);
    lista_puntos[i].nz/=float(count[i]);
  }

  for(int i =0; i < count.size(); i++){
    glNormal3f(lista_puntos[i].nx, lista_puntos[i].ny, lista_puntos[i].nz);
  }
}

void Terreno::fillIndices(){

  lista_indices = new GLuint[60000];
  int count = 0;

  for(int i =0; i < 100; i++){
    for(int j =0; j < 100; j++){

      lista_indices[count] =(i*101) + j;
      count ++;
      lista_indices[count] =(i+1)*101 + j;
      count++;
      lista_indices[count] =(i*101) + (j+1);
      count++;
      lista_indices[count] =(i*101)+ (j+1);
      count++;
      lista_indices[count] =(i+1)*101 + j;
      count++;
      lista_indices[count] =(i+1)*101 + (j+1);
      count++;
    }
  }


}

void Terreno::getNumbers(const string &line){


  string temp;

  float count = 0;
  PuntoTerreno * pt;

  for(int i =0; i < line.size(); i++){

      if(line[i] != ' '){
        temp+=line[i];
      }else{
        if(temp!= ""){
          pt = new PuntoTerreno;
          pt->x = count*50.0;
          pt->y = stof(temp);
          pt->z = lineCount*(-50.0);
          pt->s = float(count)/101.0;
          pt->t = float(lineCount)/101.0;
          pt->nx =0;
          pt->ny = 0;
          pt->nz = 0;
          lista_puntos[int((lineCount)*101 + count)] = *pt;
          count ++;
        }
        temp = "";
      }
  }


}

bool Terreno::load(){
  lista_puntos = new PuntoTerreno[101*101];
  string line;
  lineCount = 0;
  ifstream myfile ("fontvieille.txt");
  vector<int> points;
  if (myfile.is_open()){
    getline(myfile, line);
    while ( getline (myfile,line) ){
        getNumbers(line);
        lineCount++;
    }
    myfile.close();


    fillIndices();
  }

  else cout << "Unable to open file";

}
