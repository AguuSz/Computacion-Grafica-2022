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

  // Al usar GL_TRIANGLES definimos 3 puntos, y cada uno de ellos va a ser un vertice.
  // Se dibujaran puntos/3 triangulos
  glBegin(GL_TRIANGLES);
  glVertex2d(120, 300);
  glVertex2d(50, 150);
  glVertex2d(200, 150);
  glEnd();

  glBegin(GL_TRIANGLES);
  glVertex2d(470, 300);
  glVertex2d(400, 150);
  glVertex2d(550, 150);
  glEnd();

  // Para el caso de las lineas se trabaja distinto, aca seteamos 2 vertices que van a ser punto inicial y final
  // El conjunto este de lineas va a formar un triangulo pero hueco en su interior
  glBegin(GL_LINES);
  glVertex2d(MAX_WIDTH / 2 - 25, MAX_HEIGHT / 2 + 50);
  glVertex2d(MAX_WIDTH / 2 + 50, MAX_HEIGHT / 2 - 50);
  glEnd();

  glBegin(GL_LINES);
  glVertex2d(MAX_WIDTH / 2 + 50, MAX_HEIGHT / 2 - 50);
  glVertex2d(MAX_WIDTH / 2 - 100, MAX_HEIGHT / 2 - 50);
  glEnd();

  glBegin(GL_LINES);
  glVertex2d(MAX_WIDTH / 2 - 100, MAX_HEIGHT / 2 - 50);
  glVertex2d(MAX_WIDTH / 2 - 25, MAX_HEIGHT / 2 + 50);
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
