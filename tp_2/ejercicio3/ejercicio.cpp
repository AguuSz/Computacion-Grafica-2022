#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

struct Point
{
    int x;
    int y;
};

int mouseX, mouseY, mouseStatus;
bool isFirstVertexDrew = false;
Point P, Q;

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
}

void drawLine(int x1, int y1, int x2, int y2)
{
    GLfloat M, p, dx, dy, x, y, t;

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

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnd();
    glFlush();
}

void drawRectangle(Point P, Point Q)
{
    // Primer linea
    drawLine(P.x, P.y, P.x, Q.y);

    // Segunda linea
    drawLine(P.x, Q.y, Q.x, Q.y);

    // Tercer linea
    drawLine(P.x, P.y, Q.x, P.y);

    // Cuarta linea y final
    drawLine(Q.x, P.y, Q.x, Q.y);
}

void handlePassiveMotion(int x, int y)
{
    if (isFirstVertexDrew)
    {
        mouseX = x;
        mouseY = abs(y - MAX_HEIGHT);
        Point temporalPoint = {mouseX, mouseY};

        glClear(GL_COLOR_BUFFER_BIT);
        drawRectangle(P, temporalPoint);
    }
}

void drawPoint(Point point)
{
    glBegin(GL_POINTS);
    glVertex2d(point.x, point.y);
    glEnd();
    glFlush();
}

void handleMouseAction(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            // Cuando haga click
            if (mouseStatus == 0)
            {
                // Significa que tiene que hacer el punto P
                P.x = x;
                P.y = abs(y - MAX_HEIGHT);
                drawPoint(P);
                isFirstVertexDrew = true;
                mouseStatus = 1;
            }
            else
            {
                // Significa que tiene que hacer el punto Q
                Q.x = x;
                Q.y = abs(y - MAX_HEIGHT);
                drawRectangle(P, Q);
                isFirstVertexDrew = false;
                mouseStatus = 0;
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
    glutCreateWindow("Ejercicio 3");
    glutDisplayFunc(draw);
    glutMouseFunc(handleMouseAction);
    glutPassiveMotionFunc(handlePassiveMotion);
    iniciar();
    glutMainLoop();
}
