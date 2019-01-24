#define GLUT_DISABLE_ATEXIT_HACK
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

#include <GLUT/glut.h>
using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

float t=0;
float timebase=0;
float dt;
float vs = 20.0;
float vt = 3.0*vs;
float vl = 1.5*vs;
float vrt = 8.0;
float vrl = 2.0 * vrt;
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

//function called on each frame
GLvoid window_idle();
void sistema_solar();


float posCameraX = 0;
float posCameraY = 0;
float posCameraZ = 0;

float lastPosMouseX = 0;
float lastPosMouseY = 0;
float deltaX = 0.0;
float deltaY = 0.0;
float angleRotate = 0.0;
bool isDown = false;
float actualAngleX = 0;
float actualAngleY = 0;

///////////////////////////////////////////////////////////////////////////////
//(1)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
    posCameraZ+=1;

		glutPostRedisplay();			// et on demande le r�affichage.

		break;

	case GLUT_KEY_DOWN:
    posCameraZ-=1;
		glutPostRedisplay();			// et on demande le r�affichage.
		break;

	case GLUT_KEY_LEFT:
    posCameraX-=1;
		glutPostRedisplay();			// et on demande le r�affichage.
		break;

	case GLUT_KEY_RIGHT:
    posCameraX+=1;

		glutPostRedisplay();			// et on demande le r�affichage.
		break;
	}

}



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


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 2 : Transformaciones");


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

	glutMainLoop();

	return 1;
}



GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

	//enable light : try without it
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
	glEnable(GL_LIGHT0);

	//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	//enable material : try without it
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(RED, GREEN, BLUE, ALPHA);
}

float a = 0;

bool tempBool = false;
float posX = 4.0;
float angleSun = 0;
float angleEarth = 0;
float angleSelfEarth = 0;
float angleMoon = 0;
float angleSelfMoon = 0;


void ejercicio1(){
    glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
    glColor3f(1.0, 1.0, 1.0);
    a+= 6 * dt;
    glTranslatef(4.0*cos(a), 4.0*sin(a),0.0);

    glutSolidTeapot(2);
}

void ejercicio2(){
  gluPerspective(90,1,0.1,100);
  glTranslatef(0.0, 0.0,-30.0);

  sistema_solar();
}

void ejercicio3(){

  gluPerspective(90,1,0.1,100);
  gluLookAt(0,10,30,10*cos(3.14*angleEarth/180),0,0,0,1,0);
  sistema_solar();

}

void ejercicio4(){
  gluPerspective(90,1,0.1,100);
  gluLookAt(0,10,30,0,0,0,0,1,0);


    glRotatef(actualAngleX, 0,1,0);


    glRotatef(actualAngleY, 1,0,0);


  glTranslatef(posCameraX, posCameraY, posCameraZ);


}

void sistema_solar(){


    /* begin sol */
    glPushMatrix();
      glColor3f(222, 189, 0);
      angleSun+=vs*dt;
      glRotatef(angleSun,0,1,0);
      glutSolidSphere(4, 8,8);
    glPopMatrix();
    /* end sol */


    glPushMatrix();
      glColor3f(0, 0,1);
      angleEarth +=vrt*dt;
      glRotatef(angleEarth,0,1,0);

      glTranslatef(10, 0.0,0.0);
      angleSelfEarth+= vt*dt;
      glRotatef(angleSelfEarth,0,1,0);
      glutSolidSphere(2, 8,8);
    glPopMatrix();

    glPushMatrix();
      glColor3f(1, 1,1);
      glRotatef(angleEarth,0,1,0);
      glTranslatef(10, 0.0,0.0);

      angleMoon+= vrl*dt;
      angleSelfMoon+= vl*dt;

      glRotatef(angleMoon,0,1,0);

      glTranslatef(2.5, 0.0,0.0);
      glRotatef(angleSelfMoon,0,1,0);

      glutSolidSphere(1, 8,8);
    glPopMatrix();

    glPushMatrix();
      glColor3f(1, 0,0);
      glRotatef(angleEarth,0,1,0);
      glTranslatef(18, 0.0,0.0);


      glRotatef(angleSun,0,1,0);

      glutSolidSphere(1.5, 8,8);
    glPopMatrix();

}

GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);


	/*dibujar aqui*/


  /* dibujando el plano */


  /* fin plano */
  t = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
  dt = float(t -timebase)/1000.0;// delta time
  timebase = t;

   //ejercicio1();
   //ejercicio2();
   //ejercicio3();
   ejercicio4();


     glLineWidth(1.5);
     glColor3f(1.0, 0.0, 0.0);
     glBegin(GL_LINES);
     glVertex3f(-30, 0.0, 0.0);
     glVertex3f(30, 0, 0);
     glEnd();

     glLineWidth(1.5);
     glColor3f(0.0, 1.0, 0.0);
     glBegin(GL_LINES);
     glVertex3f(0.0, -30, 0.0);
     glVertex3f(0, 30, 0);
     glEnd();

     glLineWidth(1.5);
     glColor3f(0.0, 0.0, 1.0);
     glBegin(GL_LINES);
     glVertex3f(0.0, 0.0, -30);
     glVertex3f(0, 0, 30);
     glEnd();


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
