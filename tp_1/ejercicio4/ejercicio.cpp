#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

float f(float x)
{
  return (exp(-x) * cos(2 * M_PI * x));
}

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  // Dibujamos la linea del medio para simular el eje X
  glBegin(GL_LINE_STRIP);
  glVertex2d(0, MAX_HEIGHT / 2);
  glVertex2d(MAX_WIDTH, MAX_HEIGHT / 2);
  glEnd();

  // Graficado de la funcion
  glPointSize(3);
  glBegin(GL_POINTS);

  for (float x = 0; x <= 4; x += 0.005)
  {
    glVertex2d(x * (MAX_WIDTH / 4), f(x) * (MAX_HEIGHT / 2) + MAX_HEIGHT / 2);
  }

  glEnd();
  glFlush();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio 4");
  glutDisplayFunc(draw);
  iniciar();
  glutMainLoop();
}
