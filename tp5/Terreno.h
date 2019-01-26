#include <vector>
#include <GLUT/glut.h>

using namespace std;



typedef struct{ // Definicion de un punto del terreo
GLfloat s, t; // Coordenadas de texturas
GLfloat nx, ny, nz; // Coordenadas de la normal
GLfloat x, y, z; // posición del vértice
} PuntoTerreno;



class Terreno {
  void getNumbers(const string &line);

  void fillIndices();
public :
// Tabla que contiene los puntos GLuint *lista_indices ;
PuntoTerreno * lista_puntos; // Tabla que contiene los indicess
Terreno();
~Terreno();
int countIndices = 0;
float lineCount;
bool load() ; // carga de un archivo de modelo digital de terreno
void display(); // Visualizacion del terreno
void computeNormals(); // calcula las normales de cada vertice
GLuint *lista_indices;
private:
int nb_pt_x, nb_pt_z; // quantidad de punto en X y Z
float dist_x, dist_z; // distancia entre dos puntos segun X y Z del terreno
};
