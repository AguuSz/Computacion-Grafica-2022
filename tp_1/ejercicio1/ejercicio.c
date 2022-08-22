
#include <GL/glu.h>
#include <GL/glut.h>

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0); // Linea encargada de establecer el color de fondo
  glColor3f(0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 640.0, 0.0, 480.0); // Permite la proyeccion en 2D
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glFlush();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // GLUT_SINGLE nos configura un solo BUFER, y GLUT_RGB nos configura que se trabaje con RGB.
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio 1");
  glutDisplayFunc(dibujar);
  iniciar();
  glutMainLoop();
}
