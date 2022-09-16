#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

using namespace std;

struct Point
{
    int x;
    int y;
};

int mouseOffsetX = 0, mouseOffsetY = 0;
Point drawingPoints[] = {
    0, 0,
    70, 0,
    70, 70,
    80, 70,
    80, 0,
    140, 0,
    140, 50,
    150, 50,
    150, 0,
    200, 0};

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLineWidth(4);
    glLoadIdentity();
    gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
}

void handleKeyboardAction(unsigned char keyPressed, int x, int y)
{
    switch (keyPressed)
    {
    case 97:
        // Tecla presionada: a
        break;
    case 115:
        // Tecla presionada: s
        break;

    case 100:
        // Tecla presionada: d
        break;
    case 113:
        // Tecla presionada: q
        break;
    }
    glutPostRedisplay();
}

Point rotate(Point point, double theta)
{
    int x, y;
    x = point.x * cos(theta) - point.y * sin(theta);
    y = point.x * sin(theta) + point.y * cos(theta);

    return Point{x, y};
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    double theta = M_PI / 4;
    double dx = 1 / tan(theta);

    glBegin(GL_LINE_STRIP);
    for (Point point : drawingPoints)
    {
        glVertex2d(point.x + 50 + dx * point.y, point.y + 200);
    }
    glVertex2d(drawingPoints[9].x + 55, drawingPoints[9].y + 195);
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (Point point : drawingPoints)
    {
        glVertex2d(point.x + 50 + dx * point.y, -point.y + 190);
    }
    glVertex2d(drawingPoints[9].x + 55, drawingPoints[9].y + 195);
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
    glutCreateWindow("TP_3 | Ejercicio 1");
    glutDisplayFunc(draw);
    glutKeyboardFunc(handleKeyboardAction);
    iniciar();
    glutMainLoop();
}
