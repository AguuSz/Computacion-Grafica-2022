#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

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
    glLineWidth(5);
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
            glutPostRedisplay();
        }
    }
}

void drawG(double theta = M_PI / 2)
{
    Point letterGPoints[] = {0, 0, 125, 0, 125, 75, 62, 75, 62, 50, 100, 50, 100, 25, 25, 25, 25, 150, 100, 150, 100,
                             125, 125, 125, 125, 175, 0, 175, 0, 0};
    double dx = 1 / tan(theta);

    if (theta == M_PI / 2)
        glColor3f(255, 0, 0);
    else
        glColor3f(0, 0, 0);

    glBegin(GL_LINE_STRIP);
    for (Point point : letterGPoints)
    {
        // x = puntoX + dx y + offsetMouse
        // y = puntoY + offsetMouse
        double x = point.x + dx * point.y + mouseOffsetX;
        double y = point.y + mouseOffsetY;
        glVertex2d(x, y);
    }
    glEnd();
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    double theta = M_PI / 3;
    glClear(GL_COLOR_BUFFER_BIT);
    drawG();      // G Comun
    drawG(theta); // G Cizalla
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
