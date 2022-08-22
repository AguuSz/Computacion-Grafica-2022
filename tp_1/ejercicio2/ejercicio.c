#include <GL/glu.h>
#include <GL/glut.h>

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPointSize(10);

  // Definimos el comienzo de los vertices que definen una primitiva o un grupo de primitivas
  // Al usar GL_POINTS tratamos cada vertice como un punto individual.
  glBegin(GL_POINTS);

  glVertex2d(100, 50);
  glVertex2d(100, 130);
  glVertex2d(150, 130);

  // Fin de los vertices
  glEnd();

  glFlush();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio 2");
  glutDisplayFunc(dibujar);
  iniciar();
  glutMainLoop();
}
