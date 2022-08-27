#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

struct point
{
  float x, y;
};

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0, 0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
}

void drawDino(string fileName)
{
  ifstream file(fileName);
  string line = "";

  // Por algun motivo no anda dentro de un FOR
  getline(file, line);
  getline(file, line);
  getline(file, line); // cantidad de lineas a dibujar
  int cantidadLineas = stoi(line);

  for (int i = 0; i < cantidadLineas; i++)
  {
    getline(file, line);
    if (line[0] == '#')
    {
      i--;
      continue;
    }
    int cantidadPuntos = stoi(line);
    point previousPoint;

    for (int j = 0; j < cantidadPuntos; j++)
    {
      getline(file, line);
      point temporaryPoint;

      if (line[0] == '#')
      {
        j--;
        continue;
      }

      temporaryPoint.x = stoi(line.substr(0, line.find(' ')));
      temporaryPoint.y = stoi(line.substr(line.find(' '), line.length() - 1));

      if (j == 0)
      {
        previousPoint.x = temporaryPoint.x;
        previousPoint.y = temporaryPoint.y;
      }

      glBegin(GL_LINE_STRIP);
      glVertex2d(previousPoint.x, previousPoint.y);
      glVertex2d(temporaryPoint.x, temporaryPoint.y);
      glEnd();

      previousPoint = temporaryPoint;
    }
  }
  file.close();
}
//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  drawDino("dino.bat");
  glFlush();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio 5");
  glutDisplayFunc(draw);
  iniciar();
  glutMainLoop();
}
