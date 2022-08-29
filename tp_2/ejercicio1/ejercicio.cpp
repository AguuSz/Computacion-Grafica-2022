#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
using namespace std;

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

struct point
{
    float x, y;
};

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
    glFlush();
}

void drawLine(point p0, point p1)
{
    int x;
    float y;
    float dy = p1.y - p0.y;
    float dx = p1.x - p0.x;
    float m = dy / dx;

    y = p0.y;
    glBegin(GL_POINTS);
    for (x = p0.x; x < p1.x; x++)
    {
        glVertex2d(x, round(y));
        y = y + m;
    }
    glEnd();
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
                drawLine(initialPoint, endPoint);
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
    glutCreateWindow("Ejercicio 1");
    glutDisplayFunc(draw);
    glutMouseFunc(handleMouseAction);
    iniciar();
    glutMainLoop();
}
