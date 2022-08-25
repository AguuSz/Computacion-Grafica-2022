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

// Inicia en negro con un grado = 1
int r = 0, g = 0, b = 0, degree = 1, tmp = 0;
// Puntos iniciales que luego iremos modificando con el mouse
point T0 = {0, 0}, T1 = {MAX_WIDTH / 2, MAX_HEIGHT}, T2 = {MAX_WIDTH, 0};

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
}

// Funcion auxiliar para encontrar el punto medio entre 2 puntos
point midPoint(point A, point B)
{
  float x = (A.x + B.x) / 2;
  float y = (A.y + B.y) / 2;

  return {x, y};
}
/*
Funcion encargada exclusivamente de dibujar un triangulo dado 3 puntos.
  empty: indica si queremos que el triangulo tenga o no color
*/
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

// Funcion recursiva encargada de la logica de Sierpinski
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

// Funcion encargada de dibujar el patron de Sierpinski
void drawSierpinski(int n)
{
  drawTriangle(T0, T1, T2, false);
  sierpinski(T0, T1, T2, n);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  drawSierpinski(degree);
  glFlush();
}

/*
Cambia el color del dibujado dependiendo de la opcion

  1: Rojo
  2: Azul
  3: Verde
  4: Negro
*/
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
    // Color verde
    r = 0;
    g = 255;
    b = 0;
    break;

  case 4:
    // Color negro
    r = 0;
    g = 0;
    b = 0;
    break;
  }
}

/*
Maneja las acciones del mouse, en este caso solo tendremos en cuenta los clicks principales.
La variable tmp esta encargada de saber cual de los 3 puntos hay que modificar
  1: T0
  2: T1
  3: T2
*/

void handleMouseAction(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
  {
    if (state == GLUT_DOWN)
    {
      switch (tmp)
      {
      case 0:
        T0.x = x;
        T0.y = abs(y - MAX_HEIGHT);
        tmp++;
        break;
      case 1:
        T2.x = x;
        T2.y = abs(y - MAX_HEIGHT);
        tmp++;
        break;
      case 2:
        T1.x = x;
        T1.y = abs(y - MAX_HEIGHT);
        tmp = 0;
        break;
      }
      draw();
    }
  }
}

/*
Controla las pulsaciones de teclas
  a: disminuye el grado
  s: aumenta el grado
  q: reseteamos al estado inicial

  r: color: rojo
  g: color: verde
  b: color: azul
*/
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

  case 113:
    // Tecla presionada: q
    T0 = {0, 0};
    T1 = {MAX_WIDTH / 2, MAX_HEIGHT};
    T2 = {MAX_WIDTH, 0};
    changeDrawingColor(4);
    break;
  }

  // Redibuja con los cambios hechos
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
  glutMouseFunc(handleMouseAction);
  glutKeyboardFunc(handleKeyboardAction);
  iniciar();
  glutMainLoop();
}
