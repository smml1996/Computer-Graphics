#define GLUT_DISABLE_ATEXIT_HACK
#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_
#include "TextureManager.h"
#endif
#include <iostream>
#include <GLUT/glut.h>
#include <cmath>
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
float posY = 5.0;
float posX = 0.0f;
float posZ = 20.0;
GLfloat position[] = { posX, posY, posZ, 1.0 };

bool isX = false;
bool isY = false;
bool isZ = false;
int grassTexture;
int brickTexture;
int roofTexture;
int treeTexture;

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
	glutCreateWindow("tp4");


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
	grassTexture = TextureManager::Inst()->LoadTexture("img/grass.jpg", GL_BGR_EXT, GL_RGB);
	brickTexture = TextureManager::Inst()->LoadTexture("img/brick.jpg", GL_BGR_EXT, GL_RGB);
	roofTexture = TextureManager::Inst()->LoadTexture("img/roof.jpg", GL_BGR_EXT, GL_RGB);
	treeTexture = TextureManager::Inst()->LoadTexture("img/tree2.png", GL_BGRA_EXT, GL_RGBA);
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

void ejercicio1(){

	glColor3f(0.0f, 153.0/255.0, 0.0f);

	glBegin(GL_QUADS);
	glVertex3f(-20.0f,0.0f,20.0f); //top left
	glVertex3f(-20.0, 0.0, -20.0f); // bottom left
	glVertex3f(20.0f, 0.0f, -20.0f); // bottom right
	glVertex3f(20.0f, 0.0f, 20.0f);
	glEnd();


	glColor3f(204.0/255.0, 102.0/255.0, 0.0f);
	glBegin(GL_QUADS);
	//front wall
	glVertex3f(-10.0f,10.0f,5.0f);
	glVertex3f(-10.0, 0.0, 5.0f);
	glVertex3f(10.0f, 0.0f, 5.0f);
	glVertex3f(10.0f, 10.0f, 5.0f);
	glEnd();

	glBegin(GL_QUADS);
	//back wall
	glVertex3f(-10.0f,10.0f,-5.0f);
	glVertex3f(-10.0, 0.0, -5.0f);
	glVertex3f(10.0f, 0.0f, -5.0f);
	glVertex3f(10.0f, 10.0f, -5.0f);
	glEnd();

	glBegin(GL_QUADS);
	//left wall
	glVertex3f(-10.0f, 0.0f, 5.0f);
	glVertex3f(-10.0, 10.0, 5.0f);
	glVertex3f(-10.0f, 10.0f, -5.0f);
	glVertex3f(-10.0f, 0.0f, -5.0f);
	glEnd();

	glBegin(GL_QUADS);
	//right wall
	glVertex3f(10.0f, 0.0f, 5.0f);
	glVertex3f(10.0, 10.0, 5.0f);
	glVertex3f(10.0f, 10.0f, -5.0f);
	glVertex3f(10.0f, 0.0f, -5.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(10.0f, 10.0f, 5.0f);
	glVertex3f(10.0f, 10.0f, -5.0f);
	glVertex3f(10.0f, 15.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-10.0f, 10.0f, 5.0f);
	glVertex3f(-10.0f, 10.0f, -5.0f);
	glVertex3f(-10.0f, 15.0f, 0.0f);
	glEnd();

	glColor3f(160.0/255.0, 160.0/255.0, 160.0/255.0);

	glBegin(GL_QUADS);
	//rooftop front
	glVertex3f(-10.0f, 10.0f, 5.0f);
	glVertex3f(10.0f, 10.0f, 5.0f);
	glVertex3f(10.0f, 15.0f, 0.0f);
	glVertex3f(-10.0f, 15.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	//rooftop back
	glVertex3f(-10.0f, 10.0f, -5.0f);
	glVertex3f(10.0f, 10.0f, -5.0f);
	glVertex3f(10.0f, 15.0f, 0.0f);
	glVertex3f(-10.0f, 15.0f, 0.0f);
	glEnd();


	glColor3f(0.0/255.0, 102.0/255.0, 0.0/255.0);
	glPushMatrix();
	glTranslatef(10.0, 8.0,10.0f);

	glutSolidSphere(3, 8, 8);
	glPopMatrix();

	glColor3f(102.0/255.0, 51.0/255.0, 0.0/255.0);

	glPushMatrix();

	glTranslatef(10.0,0.0,10.0f);
	glRotatef(270, 1,0,0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 5.0f, 10,10 );
	glPopMatrix();

}

GLfloat mat[] = {0.3f, 0.0f, 0.0f, 1.0f};
void changeMatValues(float r, float g, float b, float alpha){

	mat[0] = r;
	mat[1] = g;
	mat[2] = b;
	mat[3] = alpha;
}


void ejercicio2(){
		changeMatValues(0.0,0.0,0.0, 1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
		changeMatValues(0.1,0.35,0.1,1.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
		changeMatValues(0.45,0.55,0.45,1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
		float val[] = {25};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, val);

		glNormal3f(0,1,0);
		glBegin(GL_QUADS);
		glVertex3f(-20.0f,0.0f,20.0f); //top left
		glVertex3f(-20.0, 0.0, -20.0f); // bottom left
		glVertex3f(20.0f, 0.0f, -20.0f); // bottom right
		glVertex3f(20.0f, 0.0f, 20.0f);
		glEnd();

		changeMatValues(0.19125,0.0735,0.0225,1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
		changeMatValues(0.7038,0.27048,0.0828,1.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
		changeMatValues(0.256777,0.137622,0.086014,1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
		val[0] = .1;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, val);

		glNormal3f(0,0,1);
		glBegin(GL_QUADS);
		//front wall
		glVertex3f(-10.0f,10.0f,5.0f);
		glVertex3f(-10.0, 0.0, 5.0f);
		glVertex3f(10.0f, 0.0f, 5.0f);
		glVertex3f(10.0f, 10.0f, 5.0f);
		glEnd();


		glNormal3f(0,0,-1);
		glBegin(GL_QUADS);
		//back wall
		glVertex3f(-10.0f,10.0f,-5.0f);
		glVertex3f(-10.0, 0.0, -5.0f);
		glVertex3f(10.0f, 0.0f, -5.0f);
		glVertex3f(10.0f, 10.0f, -5.0f);
		glEnd();

		glNormal3f(-1,0,0);
		glBegin(GL_QUADS);
		//left wall
		glVertex3f(-10.0f, 0.0f, 5.0f);
		glVertex3f(-10.0, 10.0, 5.0f);
		glVertex3f(-10.0f, 10.0f, -5.0f);
		glVertex3f(-10.0f, 0.0f, -5.0f);
		glEnd();

		glNormal3f(1,0,0);
		glBegin(GL_QUADS);
		//right wall
		glVertex3f(10.0f, 0.0f, 5.0f);
		glVertex3f(10.0, 10.0, 5.0f);
		glVertex3f(10.0f, 10.0f, -5.0f);
		glVertex3f(10.0f, 0.0f, -5.0f);
		glEnd();



		glNormal3f(1, 0, 0);
		glBegin(GL_TRIANGLES);
		glVertex3f(10.0f, 10.0f, 5.0f);
		glVertex3f(10.0f, 10.0f, -5.0f);
		glVertex3f(10.0f, 15.0f, 0.0f);

		glEnd();

		glNormal3f(-1,0,0);
		glBegin(GL_TRIANGLES);
		glVertex3f(-10.0f, 10.0f, 5.0f);
		glVertex3f(-10.0f, 15.0f, 0.0f);
		glVertex3f(-10.0f, 10.0f, -5.0f);

		glEnd();

		changeMatValues(0.25,0.20725,0.20725,1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
		changeMatValues(1,0.829,0.829,1.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
		changeMatValues(0.296648,0.296648,0.296648,1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
		val[0] = 0.088;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, val);

		glNormal3f(0,100,100);
		glBegin(GL_QUADS);
		//rooftop front
		glVertex3f(-10.0f, 10.0f, 5.0f);
		glVertex3f(10.0f, 10.0f, 5.0f);
		glVertex3f(10.0f, 15.0f, 0.0f);
		glVertex3f(-10.0f, 15.0f, 0.0f);
		glEnd();

		glNormal3f(0,-100,-100);
		glBegin(GL_QUADS);
		//rooftop back
		glVertex3f(-10.0f, 10.0f, -5.0f);
		glVertex3f(10.0f, 10.0f, -5.0f);
		glVertex3f(10.0f, 15.0f, 0.0f);
		glVertex3f(-10.0f, 15.0f, 0.0f);
		glEnd();

		changeMatValues(0.0215,0.1745,0.0215,1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
		changeMatValues(0.07568,0.61424,0.07568,1.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
		changeMatValues(0.633,0.727811,0.633,1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
		val[0] = 0.6;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, val);
		glPushMatrix();
		glTranslatef(10.0, 8.0,10.0f);

		glutSolidSphere(3, 8, 8);
		glPopMatrix();


		changeMatValues(0.2125,0.1275,0.054,1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
		changeMatValues(0.714,0.4284,0.18144,1.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
		changeMatValues(0.393548,0.271906,0.166721,1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
		val[0] = 0.2;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, val);
		glPushMatrix();

		glTranslatef(10.0,0.0,10.0f);
		glRotatef(270, 1,0,0);
		gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 5.0f, 10,10 );
		glPopMatrix();
}


void ejercicio3(){

	/*int grassTexture;
	int brickTexture;
	int roofTexture;
	int treeTexture;*/
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, grassTexture);
	glNormal3f(0,1,0);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-20.0f,0.0f,20.0f); //top left
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(-20.0, 0.0, -20.0f); // bottom left
	glTexCoord2f(1.0, 1.0f );
	glVertex3f(20.0f, 0.0f, -20.0f); // bottom right
	glTexCoord2f(1.0, 0.0);
	glVertex3f(20.0f, 0.0f, 20.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	glNormal3f(0,0,1);
	glBindTexture(GL_TEXTURE_2D, brickTexture);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	//front wall
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-10.0f,10.0f,5.0f);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(-10.0, 0.0, 5.0f);
	glTexCoord2f(1.0, 1.0f );
	glVertex3f(10.0f, 0.0f, 5.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(10.0f, 10.0f, 5.0f);
	glEnd();

	glNormal3f(0,0,-1);
	glBegin(GL_QUADS);
	//back wall
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-10.0f,10.0f,-5.0f);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(-10.0, 0.0, -5.0f);
	glTexCoord2f(1.0, 1.0f );
	glVertex3f(10.0f, 0.0f, -5.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(10.0f, 10.0f, -5.0f);
	glEnd();

	glNormal3f(-1,0,0);
	glBegin(GL_QUADS);
	//left wall
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-10.0f, 0.0f, 5.0f);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(-10.0, 10.0, 5.0f);
	glTexCoord2f(1.0, 1.0f );
	glVertex3f(-10.0f, 10.0f, -5.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-10.0f, 0.0f, -5.0f);
	glEnd();

	glNormal3f(1,0,0);
	glBegin(GL_QUADS);
	//right wall
	glTexCoord2f(0.0, 0.0);
	glVertex3f(10.0f, 0.0f, 5.0f);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(10.0, 10.0, 5.0f);
	glTexCoord2f(1.0, 1.0f );
	glVertex3f(10.0f, 10.0f, -5.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(10.0f, 0.0f, -5.0f);
	glEnd();

	glNormal3f(1,0,0);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(10.0f, 10.0f, 5.0f);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(10.0f, 10.0f, -5.0f);
	glTexCoord2f(1.0, 0.0f );
	glVertex3f(10.0f, 15.0f, 0.0f);
	glEnd();

	glNormal3f(-1,0,0);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-10.0f, 10.0f, 5.0f);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(-10.0f, 10.0f, -5.0f);
	glTexCoord2f(1.0, 0.0f );
	glVertex3f(-10.0f, 15.0f, 0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, roofTexture);
	glEnable(GL_TEXTURE_2D);
	glNormal3f(0,100,100);
	glBegin(GL_QUADS);
	//rooftop front
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-10.0f, 10.0f, 5.0f);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(10.0f, 10.0f, 5.0f);
	glTexCoord2f(1.0, 1.0f );
	glVertex3f(10.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-10.0f, 15.0f, 0.0f);
	glEnd();

	glNormal3f(0,-100,-100);
	glBegin(GL_QUADS);
	//rooftop back
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-10.0f, 10.0f, -5.0f);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(10.0f, 10.0f, -5.0f);
	glTexCoord2f(1.0, 1.0f );
	glVertex3f(10.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-10.0f, 15.0f, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, treeTexture);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(10.0, 0.0,10.0f);
	float normal[] = {0,0,1};
	float tempX, tempY, tempZ;
		for(int i =0; i < 360; i+=12){
			glPushMatrix();
				glRotatef(i, 0, 1, 0);
				tempX = normal[0]*cos(i*PI/180) + normal[2]*sin(i*PI/180);
				tempY = normal[1];
				tempZ = -normal[0]*sin(i*PI/180) + normal[2]*cos(i*PI/180);
				glNormal3f(tempX,tempY ,tempZ);
				normal[0] = tempX;
				normal[1] = tempY;
				normal[2] = tempZ;
				glBegin(GL_QUADS);

					glTexCoord2f(0.0, 1.0);
					glVertex3f(-3.0f, 10.0f, 0.0f);
					glTexCoord2f(0.0, 0.0f );
					glVertex3f(-3.0f, 0.0f, 0.0f);
					glTexCoord2f(1.0, 0.0f);
					glVertex3f(3.0f, 0.0f, 0.0f);
					glTexCoord2f(1.0, 1.0f);
					glVertex3f(3.0f, 10.0f, 0.0f);
				glEnd();

			glPopMatrix();
		}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);



}


GLvoid window_display()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  gluPerspective(90,1,0.1,100);
  gluLookAt(0,10,30,0,0,0,0,1,0);


  glRotatef(actualAngleX, 0,1,0);


  glRotatef(actualAngleY, 1,0,0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glPushMatrix();
		glTranslatef(posX, posY, posZ);
		glColor3f(1.0f, 1.0f, 1.0f);
		glutSolidSphere(1, 10, 10);
	glPopMatrix();


	/*dibujar aqui*/

	//ejercicio1();
	//ejercicio2();
	ejercicio3();


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
