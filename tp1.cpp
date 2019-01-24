#define GLUT_DISABLE_ATEXIT_HACK
//#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>

#define KEY_ESC 27

//dibuja un simple gizmo

void drawSquare(const float &centerX, const float &centerY, const float &arista){
  // funcion 1
  glBegin(GL_LINE_LOOP);
  glColor3d(255,0,0);
  float x = centerX - (arista/2.0);
  float y = centerY - (arista/2.0);
  glVertex2d(x, y);
  x +=arista;
  glVertex2d(x, y);
  y+=arista;
  glVertex2d(x, y);
  x-=arista;
  glVertex2d(x,y);
  glEnd();
}

void drawCircle(const float &centerX, const float &centerY, const float &radius){
  //funcion 2
  glBegin(GL_LINE_LOOP);
  glColor3d(255,0,0);
  float x,y;



  for(int i =0; i<360; i++){
    x = radius*cos(i*3.14159265/180.0) + centerX;
    y = radius*sin(i*3.14159265/180.0) + centerY;
    glVertex2d(x, y);
  }
  glEnd();
}

void drawConcentricCircles(float radius, int numCircles,
                              const float &reductionFactor){
    //funcion 3

    float newCenterX=0 , newCenterY= 0, newRadius = radius;

    for(int i=0; i < numCircles && radius > 0; i++){

      radius= newRadius;
      if(i>0)
        newRadius = newRadius - newRadius*reductionFactor;
      newCenterX = radius*cos(270*3.14159265/180.0) + newRadius ;


      newCenterY = radius*sin(270*3.14159265/180.0)+ newRadius;

      drawCircle(newCenterX, newCenterY, newRadius);

    }

}

void drawLineCircles(float centerX, float centerY, float radius, int numCircles, float reductionFactor){
  //funcion 4
  float nextRadius;
  for(int i =0; i < numCircles && radius>0; i++){
      drawCircle(centerX, centerY, radius);
      nextRadius = radius- radius*reductionFactor;
      centerX = centerX+radius + nextRadius;
      radius = nextRadius;
  }
}
void drawDiagonalOfCircles(int numCircles, float reductionFactor, float angle){
  //funcion 5
  //el angulo esta en sexadecimal
  angle = angle*3.14159265/180.0;

  float centerX = -20, centerY=-20, radius= 20;
  float tempRadius;
  drawCircle(centerX, centerY, radius);
  for(int i =1; i<numCircles && radius>0; i++){
    centerX = radius*cos(angle)+centerX;
    centerY = radius*sin(angle)+centerY;
    tempRadius = radius - radius*reductionFactor;
    centerX += tempRadius * cos(angle);
    centerY+= tempRadius * sin(angle);
    radius = tempRadius;
    drawCircle(centerX, centerY, radius);
  }
}

void displayGizmo()
{
  //test: square, ejercicio 1
    //drawSquare(0,0,50);
  // test: circle, ejercicio 2
    //drawCircle(0,0,20);
  // test: ej. 3, ejercicio 3
    //drawConcentricCircles(20,5,0.1);
  // test: ej. 4, ejercicio 4
    //drawLineCircles(-30,0,10,5, 0.1);
   //test: ej. 5, ejercicio 5
    drawDiagonalOfCircles(5,0.2, 90);
}

//
//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();


	//dibuja el gizmo
	displayGizmo();

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tama�o
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-50.0f,  50.0f,-50.0f, 50.0f, -1.0f, 1.0f);
	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	default:
		break;
	}

}
//
//el programa principal
//
int main(int argc, char** argv) {

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tama�o de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP1 OpenGL : hello_world_OpenGL"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering

	return 0;
}
