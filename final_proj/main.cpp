#define GLUT_DISABLE_ATEXIT_HACK
#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_
#include "TextureManager.h"
#endif
#include <math.h>
#include <iostream>
#include <cmath>
#include <GLUT/glut.h>
#include <string>
#include <thread>
#ifndef MAIN_CHARACTER_H_
#define MAIN_CHARACTER_H_
#include "Main_Character.h"
#endif

#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_
#include "globalVariables.h"
#endif

#ifndef OBSTACLE_GENERATOR_H_
#define OBSTACLE_GENERATOR_H_
#include "ObstacleGenerator.h"
#endif


using namespace std;


#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

Main_Character *mc = new Main_Character;

int score = 0;
int moneyVal = 10;
int velocity = 20;
//function called on each frame
GLvoid window_idle();
int t=0;
float lastPosMouseX = 0;
float lastPosMouseY = 0;
float deltaX = 0.0;
float deltaY = 0.0;
float angleRotate = 0.0;
bool isDown = false;
float actualAngleX = 0;
float actualAngleY = 0;
float tempt;
int tbase=0;
GLuint texture;
int timebaseMusic =0;
int timeMusic=0;
float tempMusic;

ObstacleGenerator obsGen(velocity, mc);

float inc = 0.0;

void renderFloor(){

	inc += 0.000001;



	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0 - inc);//coordenadas de textura
	glVertex3d(-50, -10, -50);

	glTexCoord2f(0.0, 1.0f - inc);
	glVertex3d(-50, -10, 50);

	glTexCoord2f(1.0, 1.0f - inc);
	glVertex3d(50, -10, 50);

	glTexCoord2f(1.0, 0.0 - inc);
	glVertex3d(50, -10, -50);
	glEnd();

	GLuint * texturePointer = &texture;

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0 - inc);//coordenadas de textura
	glVertex3d(-50, -10, -50);

	glTexCoord2f(0.0, 1.0f - inc);
	glVertex3d(-50, -10, 50);

	glTexCoord2f(1.0, 1.0f - inc);
	glVertex3d(-50, 75, 50);

	glTexCoord2f(1.0, 0.0 - inc);
	glVertex3d(-50, 75, -50);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0 - inc);//coordenadas de textura
	glVertex3d(50, -10, -50);

	glTexCoord2f(0.0, 1.0f - inc);
	glVertex3d(50, -10, 50);

	glTexCoord2f(1.0, 1.0f - inc);
	glVertex3d(50, 75, 50);

	glTexCoord2f(1.0, 0.0 - inc);
	glVertex3d(50, 75, -50);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0 - inc);//coordenadas de textura
	glVertex3d(50, 50, -50);

	glTexCoord2f(0.0, 1.0f - inc);
	glVertex3d(-50, 50, -50);

	glTexCoord2f(1.0, 1.0f - inc);
	glVertex3d(-50, -50, -50);

	glTexCoord2f(1.0, 0.0 - inc);
	glVertex3d(50, -50, -50);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}
void displayScore(){
	string txt= "SCORE: " + to_string(mc->score);
	char *c;
	glPushMatrix();
	glTranslatef(-18.5f, 20.5f,5.0f);
	glScalef(0.01f,0.01f,0.01f);

	glColor3f(1.0f,1.0f,1.0f);

	for (int c = 0; c < txt.size(); c++){
		glutStrokeCharacter(GLUT_STROKE_ROMAN , txt[c]);
	}
	 glPopMatrix();
}

void diplayGameOver(){
	string txt= "Game Over";
	char *c;
	glPushMatrix();
	glTranslatef(-7.5f, 5.0f,10.0f);
	glScalef(0.02f,0.02f,0.02f);

	glColor3f(1.0f,1.0f,1.0f);

	for (int c = 0; c < txt.size(); c++){
		glutStrokeCharacter(GLUT_STROKE_ROMAN , txt[c]);
	}
	 glPopMatrix();

	 txt= "SCORE: " + to_string(mc->score);
	 glPushMatrix();
	 glTranslatef(-4.5f, 1.0f,10.0f);
	 glScalef(0.01f,0.01f,0.01f);

	 glColor3f(1.0f,1.0f,1.0f);

	 for (int c = 0; c < txt.size(); c++){
		 glutStrokeCharacter(GLUT_STROKE_ROMAN , txt[c]);
	 }
		glPopMatrix();
}




void displayLevel(){
	string actualLevel = "I";
	if(obsGen.level == 2){
		actualLevel = "II";
	}else if(obsGen.level == 3){
		actualLevel = "III";
	}
	string txt= "LEVEL " + actualLevel;
	char *c;
	glPushMatrix();
	glTranslatef(10.5f, 20.5f,5.0f);
	glScalef(0.01f,0.01f,0.0f);


	glColor3f(1.0f,1.0f,1.0f);


	for (int c = 0; c < txt.size(); c++){


		glutStrokeCharacter(GLUT_STROKE_ROMAN , txt[c]);
	}
	 glPopMatrix();
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


GLvoid keyboard_up(unsigned char key, int x, int y){
		switch (key) {
			case ' ':
				system("afplay -v 0.15 sounds/shoot.wav &");
				mc->throwbullet();
				break;
			case 'w':
				system("afplay -v 0.15 sounds/protect.flac &");

				mc->protect();
				break;
			case 'q':
				system("killall afplay");
				exit(0);
				break;
		}
}

// begin on keyboard press
GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
    // jump
		system("afplay -v 0.5 sounds/bounce.wav &");

    mc->jump();
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
    // deslizar
		system("afplay sounds/deslizar.wav &");

    mc->deslizar();
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
    //move left
    if(mc->actualColumn > 0){
			system("afplay sounds/move.wav &");

      mc->actualColumn--;
    }
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
    // move right
    if(mc->actualColumn < 2){
			system("afplay sounds/move.wav &");

      mc->actualColumn++;
    }
		glutPostRedisplay();
		break;

	}

}

void playBackgroundMusic(){

	system("afplay sounds/theme2.mp3 &");

}

void stopMusic(){
	while(true){

		if(obsGen.isGameOver){

			system("killall afplay");

			system("afplay sounds/themeGameOver.mp3 &");

			return;
		}

	}

}
int main(int argc, char **argv)
{

	playBackgroundMusic();
	thread stopmusicThread(stopMusic);
	glutInit(&argc, argv);


	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Proyecto Final");


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
	texture = TextureManager::Inst()->LoadTexture("img/milkyway2.webp", GL_BGR_EXT, GL_RGB);
	//mc->textureNormal = TextureManager::Inst()->LoadTexture("img/normal.jpg", GL_BGR_EXT, GL_RGB);
	//mc->textureProtected = TextureManager::Inst()->LoadTexture("img/protect.jpg", GL_BGR_EXT, GL_RGB);
	boxTexture = TextureManager::Inst()->LoadTexture("img/box.jpg", GL_BGR_EXT, GL_RGB);
	huecoTexture = TextureManager::Inst()->LoadTexture("img/hueco3.png", GL_BGRA_EXT, GL_RGBA);

	wallTexture = TextureManager::Inst()->LoadTexture("img/wall.jpg", GL_BGR_EXT, GL_RGB);
	glutMainLoop();

	stopmusicThread.join();


	return 1;
}


// Lighting values
float ambientLight[4] = {0.1, 0.1, 0.1, 1.0};
float Lt0amb[4] = {0.3, 0.3, 0.3, 1.0};
float Lt0diff[4] = {1.0, 1.0, 1.0, 1.0};
float Lt0spec[4] = {1.0, 1.0, 1.0, 1.0};

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
	//glEnable(GL_TEXTURE_2D);
	glClearColor(RED, GREEN, BLUE, ALPHA);

	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

//	glLightfv(GL_LIGHT0, GL_AMBIENT, Lt0amb);
//glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
//glLightfv(GL_LIGHT0, GL_SPECULAR, Lt0spec);
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


	/*dibujar aqui*/
	renderFloor();

	if(obsGen.isGameOver){


		diplayGameOver();

	}else{

	displayScore();
	displayLevel();
	if(obsGen.level < 3){
		t = glutGet(GLUT_ELAPSED_TIME);

		tempt = float(t - tbase) / 1000.0;
		tempMusic = float(t - timebaseMusic)/1000.0;
		if(tempMusic/60.0 > 5.29){
			timebaseMusic = t;
			system("afplay sounds/theme2.mp3");
		}
		if(tempt >=30.0){
				system("afplay sounds/levelup.mp3 &");

				obsGen.levelUp();
				if(obsGen.level == 2){
					obsGen.velocity = 30;
				}else{
					obsGen.velocity = 40;
				}
				tbase = t;
		}
	}



  mc->draw(velocity);
	obsGen.moveObstacles();

	}


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
