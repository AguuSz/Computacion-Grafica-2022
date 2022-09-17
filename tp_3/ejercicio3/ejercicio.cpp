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

Point drawingPoints[] = {
    5, 5,
    70, 5,
    70, 75,
    80, 75,
    80, 5,
    140, 5,
    140, 55,
    150, 55,
    150, 5,
    200, 5,
    210, 0};

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
        for (int i = 0; i < 11; i++)
        {
            drawingPoints[i].x *= 1.2;
            drawingPoints[i].y *= 1.2;
        }
        break;
    case 115:
        // Tecla presionada: s
        for (int i = 0; i < 11; i++)
        {
            drawingPoints[i].x *= 0.8;
            drawingPoints[i].y *= 0.8;
        }
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

    double dx = 1 / tan(M_PI / 4); // Angulo para la cizalla: 45 grados
    double theta = M_PI / 3;       // Angulo para la rotacion: 30 grados
    Point rotatedPoints[11];
    Point cizallaPoints[11];
    Point temporalPoint;

    for (int i = 1; i < 7; i++)
    {

        // Aplicamos cizalla para luego rotar cada uno de los puntos
        for (int j = 0; j < 11; j++)
        {
            temporalPoint = drawingPoints[j];
            temporalPoint.x += dx * temporalPoint.y;
            cizallaPoints[j] = temporalPoint;
            rotatedPoints[j] = rotate(cizallaPoints[j], theta * i);
        }

        // Dibujamos los puntos una vez rotados
        glBegin(GL_LINE_STRIP);
        for (Point point : rotatedPoints)
        {
            glVertex2d(point.x + MAX_WIDTH / 2, point.y + MAX_HEIGHT / 2);
        }
        glEnd();

        // Dibujado de la rama espejada -> Y negativo
        glBegin(GL_LINE_STRIP);
        for (Point point : rotatedPoints)
        {
            glVertex2d(point.x + MAX_WIDTH / 2, -point.y + MAX_HEIGHT / 2);
        }
        glEnd();
    }

    glFlush();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("TP_3 | Ejercicio 3");
    glutDisplayFunc(draw);
    glutKeyboardFunc(handleKeyboardAction);
    iniciar();
    glutMainLoop();
}
