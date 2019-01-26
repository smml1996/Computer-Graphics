#define GLUT_DISABLE_ATEXIT_HACK
#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_
#include "TextureManager.h"
#endif
#include <iostream>
#include <GLUT/glut.h>
#include <cmath>
#include "Terreno.h"
#ifndef GLOBAL_H_
#define GLOBAL_H_
#include "global.h"
#endif
using namespace std;


#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1
#define PI 3.14159265359

#define ECHAP 27

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

//function called on each frame
GLvoid window_idle();
float lastPosMouseX = 0;
float lastPosMouseY = 0;
float deltaX = 0.0;
float deltaY = 0.0;
float angleRotate = 0.0;
bool isDown = false;
float actualAngleX = 0;
float actualAngleY = 0;
float posY = 200.0;
float posX = 0.0f;
float posZ = 0.0;
GLfloat position[] = { posX, posY, posZ, 1.0 };

bool isX = false;
bool isY = false;
bool isZ = false;
Terreno t;
///////////////////////////////////////////////////////////////////////////////
//(2)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
    lastPosMouseX = x;
    lastPosMouseY = y;
    isDown = true;


	}else if(state == GLUT_UP && button == GLUT_LEFT_BUTTON){
      deltaX = 0;
      deltaY = 0;
      isDown = false;

  }
}

///////////////////////////////////////////////////////////////////////////////
//(3)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{
  if(isDown){
    deltaX = x - lastPosMouseX;
    deltaY = y - lastPosMouseY;
    lastPosMouseX = x;
    lastPosMouseY = y;

    actualAngleX+= deltaX;

    actualAngleY += deltaY;

  }
	glutPostRedisplay();
}


GLvoid keyboard_up(unsigned char key, int x, int y){
		switch (key) {
			case 'x':
				isX = false;
				break;
			case 'y':
				isY = false;
				break;
			case 'z':
				isZ = false;
				break;
		}
}

GLvoid keyboard_down(unsigned char key, int x, int y){
		switch (key) {
			case 'x':
				isX = true;
				break;
			case 'y':
				isY = true;
				break;
			case 'z':
				isZ = true;
				break;
		}
}

// begin on keyboard press
GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:

		if(isX) posX+=1;
		else if(isY) posY+=1;
		else if(isZ) posZ+=1;
		position[0] = posX;
		position[1] = posY;
		position[2] = posZ;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		if(isX) posX-=1;
		else if(isY) posY-=1;
		else if(isZ) posZ-=1;
		position[0] = posX;
		position[1] = posY;
		position[2] = posZ;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		glutPostRedisplay();
		break;
	}

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);


	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("tp5");


	initGL();

	init_scene();

	glutDisplayFunc(&window_display);

	glutReshapeFunc(&window_reshape);

	glutKeyboardFunc(&window_key);

	//function called on each frame
	glutIdleFunc(&window_idle);

  glutSpecialFunc(&callback_special);
  glutMouseFunc(&callback_mouse);
  glutMotionFunc(&callback_motion);
	glutKeyboardUpFunc(&keyboard_up);
	texture = TextureManager::Inst()->LoadTexture("fontvieille.tga", GL_BGR_EXT, GL_RGB);
	t.load();
	glutMainLoop();

	return 1;
}

GLvoid initGL()
{


	//enable light : try without it
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
	glEnable(GL_LIGHT0);

	//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE); //no trata las caras escondidas
	glEnable(GL_DEPTH_TEST); // Activa el Z-Buffer
	glDepthFunc(GL_LEQUAL); //Modo de funcionamiento del Z-Buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Activa la corrección de perspectiva
	glClearColor(RED, GREEN, BLUE, ALPHA);
}

GLvoid window_display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  gluPerspective(90,1,0.1,10000);
  gluLookAt(2000,2000,-2500,2500,0,-2500,0,1,0);

  glRotatef(actualAngleX, 0,1,0);


  glRotatef(actualAngleY, 1,0,0);


	/*dibujar aqui*/

	t.display();

	glutSwapBuffers();

	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

	glMatrixMode(GL_MODELVIEW);
}



void init_scene()
{

}

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		exit(1);
		break;
	case 'x':
		isX = true;
		break;
	case 'y':
		isY = true;
		break;
	case 'z':
		isZ = true;
		break;


	default:
		printf("La touche %d non active.\n", key);
		break;
	}
}


//function called on each frame
GLvoid window_idle()
{


	glutPostRedisplay();
}
