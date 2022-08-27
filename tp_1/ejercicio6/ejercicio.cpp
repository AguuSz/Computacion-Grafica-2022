#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

struct point
{
  float x, y;
};

// Seteo los parametros iniciales
bool isFirstVertexDrew = false;
int mode = 0;
int drawingSize = 5;

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar()
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0, 0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
}

// Funcion auxiliar para mostrar un texto por pantalla
void displayText(string textToDisplay, int x, int y)
{
  glColor3f(0, 0, 0);
  glRasterPos2d(x, y);

  for (char character : textToDisplay)
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, character);
  }
}

// Funcion que se encarga de mostrar todos los controles en la esquina superior izquierda
void showControls()
{
  displayText("Controles", 10, MAX_HEIGHT - 20);

  displayText("Color rojo:  a", 20, MAX_HEIGHT - 40);
  displayText("Color azul: s", 20, MAX_HEIGHT - 60);
  displayText("Color verde:  d", 20, MAX_HEIGHT - 80);

  displayText("Modo linea:  l", 20, MAX_HEIGHT - 100);
  displayText("Modo punto:  b", 20, MAX_HEIGHT - 120);

  displayText("Limpiar pantalla: r", 20, MAX_HEIGHT - 140);
}

// Funcion que obtiene el size para terminar mostrandolo abajo a la izquierda
// Es necesario que este aparte, debido a que se va a llamar en cada actualizacion del size
void showDrawingSize()
{
  string displaySize = "Size: " + to_string(drawingSize);
  displayText(displaySize, 20, 10);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  showControls();
  showDrawingSize();
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
    glColor3f(255, 0, 0);
    break;

  case 2:
    // Color azul
    glColor3f(0, 0, 255);
    break;

  case 3:
    // Color verde
    glColor3f(0, 255, 0);
    break;

  case 4:
    // Color negro
    glColor3f(0, 0, 0);
    break;
  }
}

/*
Maneja las acciones del mouse, en este caso solo tendremos en cuenta los clicks principales.
La variable tmp esta encargada de saber cual de los 3 puntos hay que modificar
*/

void handleMouseAction(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
  {
    if (state == GLUT_DOWN)
    {
      switch (mode)
      {
      case 0:
        // Modo punto
        if (!isFirstVertexDrew)
        {
          glLineWidth(drawingSize);
          glBegin(GL_LINE_STRIP);
          glVertex2d(x, abs(y - MAX_HEIGHT));
          isFirstVertexDrew = true;
        }
        else
        {
          glVertex2d(x, abs(y - MAX_HEIGHT));
          glEnd();
          glFlush();
          isFirstVertexDrew = false;
        }
        break;
      case 1:
        // Modo dibujo de puntos
        glPointSize(drawingSize);
        glBegin(GL_POINTS);
        glVertex2d(x, abs(y - MAX_HEIGHT));
        glEnd();
        glFlush();
        break;
      default:
        break;
      }
    }
  }
}

void handleKeyboardAction(unsigned char keyPressed, int x, int y)
{
  switch (keyPressed)
  {
  case 97:
    // Tecla presionada: a
    changeDrawingColor(1);
    break;
  case 115:
    // Tecla presionada: s
    changeDrawingColor(2);
    break;

  case 100:
    // Tecla presionada: d
    changeDrawingColor(3);
    break;

  case 113:
    // Tecla presionada: q
    changeDrawingColor(4);
    break;

  case 114:
    // Tecla presionada: r
    draw();
    break;

  case 108:
    // Tecla presionada: l
    mode = 0;
    isFirstVertexDrew = false;
    break;

  case 98:
    // Tecla presionada: b
    mode = 1;
    isFirstVertexDrew = false;
    break;

  case 110:
    // Tecla presionada: n
    // Esta condicion es para que evitar que se haga muy chico el dibujo y no se vea. Minimo 2
    if (drawingSize > 2)
    {
      drawingSize--;
      glScissor(0, 0, 80, 30);
      glEnable(GL_SCISSOR_TEST);
      glClear(GL_COLOR_BUFFER_BIT);
      glDisable(GL_SCISSOR_TEST);
      showDrawingSize();
      glFlush();
    }
    break;
  case 109:
    // Tecla presionada: n
    drawingSize++;
    glScissor(0, 0, 80, 30);
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    showDrawingSize();
    glFlush();
    break;
  }
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio 6");
  glutDisplayFunc(draw);
  glutMouseFunc(handleMouseAction);
  glutKeyboardFunc(handleKeyboardAction);
  iniciar();
  glutMainLoop();
}
