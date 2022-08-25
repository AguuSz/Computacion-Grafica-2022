#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

struct point
{
  float x, y;
};

// Inicia en negro
int r = 0, g = 0, b = 0, degree = 1;
point T0 = {0, 0}, T1 = {200, 350}, T2 = {350, 100};

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
}

point midPoint(point A, point B)
{
  float x = (A.x + B.x) / 2;
  float y = (A.y + B.y) / 2;

  return {x, y};
}

void drawTriangle(point A, point B, point C, bool empty)
{
  // Con este if chequeamos si pintar o no el triangulo. Esto con el proposito de hacer el triangulo vacio del medio
  if (empty)
  {
    glColor3f(1, 1, 1);
  }
  else
  {
    glColor3f(r, g, b);
  }

  glBegin(GL_TRIANGLES);
  glVertex2d(A.x, A.y);
  glVertex2d(B.x, B.y);
  glVertex2d(C.x, C.y);
  glEnd();
}

void sierpinski(point A, point B, point C, int n)
{
  if (n == 0)
  {
    return;
  }

  point MAB = midPoint(A, B);
  point MAC = midPoint(A, C);
  point MBC = midPoint(B, C);

  drawTriangle(MAB, MAC, MBC, true);
  sierpinski(A, MAB, MAC, n - 1);
  sierpinski(MAB, B, MBC, n - 1);
  sierpinski(MAC, MBC, C, n - 1);
}

void drawSierpinski(int n)
{
  float l = MAX_WIDTH - 100;
  point A = T0;
  point B = {l / 2, (sqrt(3) / 2) * l};
  point C = {l, T0.y};

  drawTriangle(A, B, C, false);
  sierpinski(A, B, C, n);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  drawSierpinski(degree);
  glFlush();
}

void changeDrawingColor(int option)
{
  switch (option)
  {
  case 1:
    // Color rojo
    r = 255;
    g = 0;
    b = 0;
    break;

  case 2:
    // Color azul
    r = 0;
    g = 0;
    b = 255;
    break;

  case 3:
    r = 0;
    g = 255;
    b = 0;

  default:
    break;
  }
}

void handleKeyboardAction(unsigned char keyPressed, int x, int y)
{
  switch (keyPressed)
  {
  case 97:
    // Tecla presionada: a
    if (degree > 0)
    {
      degree--;
    }
    break;
  case 115:
    // Tecla presionada: s
    if (degree < 8)
    {
      degree++;
    }
    break;

  case 114:
    // Tecla presionada: r
    changeDrawingColor(1);
    break;

  case 103:
    // Tecla presionada: g
    changeDrawingColor(2);
    break;

  case 98:
    // Tecla presionada: b
    changeDrawingColor(3);
    break;

  default:
    break;
  }

  draw();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio 3");
  glutDisplayFunc(draw);
  glutKeyboardFunc(handleKeyboardAction);
  iniciar();
  glutMainLoop();
}
