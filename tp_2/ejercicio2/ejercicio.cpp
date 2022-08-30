#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

struct point
{
    float x, y;
};

// Inicia en negro con un grado = 1
bool isFirstVertexDrew = false;
point initialPoint = {0, 0};
point endPoint = {0, 0};

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0, 0, 0);
    glPointSize(3);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);
    glVertex2d(168, 325);
    glVertex2d(419, 161);
    glEnd();
    glFlush();
}

void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    GLfloat M, p, dx, dy, x, y, t;
    glClear(GL_COLOR_BUFFER_BIT);

    if ((x2 - x1) == 0)
        M = (y2 - y1);
    else
        M = (y2 - y1) / (x2 - x1);

    if (fabs(M) < 1)
    {
        if (x1 > x2)
        {
            t = x1;
            x1 = x2;
            x2 = t;

            t = y1;
            y1 = y2;
            y2 = t;
        }

        dx = fabs(x2 - x1);
        dy = fabs(y2 - y1);

        p = 2 * dy - dx;

        x = x1;
        y = y1;

        glBegin(GL_POINTS);
        while (x <= x2)
        {
            glVertex2f(x, y);
            x = x + 1;

            if (p >= 0)
            {
                if (M < 1)
                    y = y + 1;
                else
                    y = y - 1;
                p = p + 2 * dy - 2 * dx;
            }
            else
            {
                y = y;
                p = p + 2 * dy;
            }
        }
        glEnd();
    }

    if (fabs(M) >= 1)
    {
        if (y1 > y2)
        {
            t = x1;
            x1 = x2;
            x2 = t;

            t = y1;
            y1 = y2;
            y2 = t;
        }

        dx = fabs(x2 - x1);
        dy = fabs(y2 - y1);

        p = 2 * dx - dy;

        x = x1;
        y = y1;

        glBegin(GL_POINTS);
        while (y <= y2)
        {
            glVertex2f(x, y);
            y = y + 1;

            if (p >= 0)
            {
                if (M >= 1)
                    x = x + 1;
                else
                    x = x - 1;
                p = p + 2 * dx - 2 * dy;
            }
            else
            {
                x = x;
                p = p + 2 * dx;
            }
        }
        glEnd();
    }

    glFlush();
}

void handleMouseAction(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            if (!isFirstVertexDrew)
            {
                initialPoint.x = x;
                initialPoint.y = abs(y - MAX_HEIGHT);
                isFirstVertexDrew = true;
            }
            else
            {
                endPoint.x = x;
                endPoint.y = abs(y - MAX_HEIGHT);
                drawLine(initialPoint.x, initialPoint.y, endPoint.x, endPoint.y);
                isFirstVertexDrew = false;
            }
        }
    }
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Ejercicio 2");
    glutDisplayFunc(draw);
    glutMouseFunc(handleMouseAction);
    iniciar();
    glutMainLoop();
}
