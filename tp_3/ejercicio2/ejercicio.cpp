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

void drawHouse(int offsetX = 0, int offsetY = 0)
{
    Point housePoints[] = {40, 0, 40, 45, 15, 45, 15, 0, 0, 0, 0, 120, 100, 120, 75, 145, 75, 170, 90, 170, 90, 130, 50,
                           170, 0, 120, 100, 120, 100, 0, 15, 0};
    Point garagePoints[] = {100, 0, 100, 105, 170, 70, 170, 0, 100, 0, 100, 70, 170, 70};

    glBegin(GL_LINE_STRIP);
    for (Point point : housePoints)
    {
        glVertex2d(mouseOffsetX + point.x + offsetX, mouseOffsetY + point.y + offsetY);
    }
    glEnd();

    // Dibujado de la ventana casa
    glBegin(GL_LINE_STRIP);
    glVertex2d(mouseOffsetX + 60 + offsetX, mouseOffsetY + 100 + offsetY);
    glVertex2d(mouseOffsetX + 90 + offsetX, mouseOffsetY + 100 + offsetY);
    glVertex2d(mouseOffsetX + 90 + offsetX, mouseOffsetY + 80 + offsetY);
    glVertex2d(mouseOffsetX + 60 + offsetX, mouseOffsetY + 80 + offsetY);
    glVertex2d(mouseOffsetX + 60 + offsetX, mouseOffsetY + 100 + offsetY);
    glEnd();

    // Dibujado del garage
    glBegin(GL_LINE_STRIP);
    for (Point point : garagePoints)
    {
        glVertex2d(mouseOffsetX + point.x + offsetX, mouseOffsetY + point.y + offsetY);
    }
    glEnd();

    // Dibujado ventana garage
    glBegin(GL_LINE_STRIP);
    glVertex2d(mouseOffsetX + 120 + offsetX, mouseOffsetY + 55 + offsetY);
    glVertex2d(mouseOffsetX + 160 + offsetX, mouseOffsetY + 55 + offsetY);
    glVertex2d(mouseOffsetX + 160 + offsetX, mouseOffsetY + 40 + offsetY);
    glVertex2d(mouseOffsetX + 120 + offsetX, mouseOffsetY + 40 + offsetY);
    glVertex2d(mouseOffsetX + 120 + offsetX, mouseOffsetY + 55 + offsetY);
    glEnd();
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    double theta = M_PI / 3;
    glClear(GL_COLOR_BUFFER_BIT);
    drawHouse();
    //    drawHouse(32, 35);
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
