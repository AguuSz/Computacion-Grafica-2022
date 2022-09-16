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
Point housePoints[] = {0, 0,
                       100, 0,
                       100, 0,
                       100, 120,
                       100, 120,
                       0, 120,
                       0, 120,
                       0, 0,
                       0, 120,
                       50, 170,
                       50, 170,
                       100, 120,
                       100, 120,
                       0, 120,
                       75, 148,
                       75, 170,
                       75, 170,
                       90, 170,
                       90, 170,
                       90, 130,
                       90, 130,
                       75, 148,
                       60, 100,
                       90, 100,
                       90, 100,
                       90, 80,
                       90, 80,
                       60, 80,
                       60, 80,
                       60, 100,
                       15, 0,
                       15, 45,
                       15, 45,
                       40, 45,
                       40, 45,
                       40, 0,
                       100, 70,
                       170, 70,
                       170, 70,
                       170, 0,
                       170, 0,
                       100, 0,
                       170, 70,
                       100, 105,
                       100, 105,
                       100, 70,
                       100, 70,
                       170, 70,
                       120, 55,
                       160, 55,
                       160, 55,
                       160, 40,
                       160, 40,
                       120, 40,
                       120, 40,
                       120, 55};

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

void handleMouseAction(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseOffsetX = x;
            mouseOffsetY = abs(y - MAX_HEIGHT);

            //            cout << "X: " << x << " | Y: " << abs(y - MAX_HEIGHT) << endl;

            glutPostRedisplay();
        }
    }
}

Point rotate(Point point, double theta)
{
    int x, y;
    x = point.x * cos(theta) - point.y * sin(theta);
    y = point.x * sin(theta) + point.y * cos(theta);

    return Point{x, y};
}

void drawHouse(int offsetX = 0, int offsetY = 0, double theta = 0)
{
    glBegin(GL_LINES);
    for (Point point : housePoints)
    {
        if (theta != 0)
            point = rotate(point, theta);
        glVertex2d(mouseOffsetX + point.x + offsetX, mouseOffsetY + point.y + offsetY);
    }
    glEnd();
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawHouse();
    drawHouse(200, 200, -M_PI / 6);
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
    glutMouseFunc(handleMouseAction);
    iniciar();
    glutMainLoop();
}
