#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

struct Point
{
    int x;
    int y;
};

Point drawingPoints[] = {
    2, 4,
    35, 4,
    35, 37,
    43, 37,
    43, 4,
    70, 4,
    70, 27,
    78, 27,
    78, 4,
    100, 4,
    110, 0};

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLineWidth(3);
    glLoadIdentity();
    gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);

    // Seteamos la semilla para el numero random (necesario para que por cada ejecucion nueva, hayan nuevos numeros)
    srand((unsigned)time(0));
}

Point rotate(Point point, double theta)
{
    int x, y;
    x = point.x * cos(theta) - point.y * sin(theta);
    y = point.x * sin(theta) + point.y * cos(theta);

    return Point{x, y};
}

void drawSnowflake(int offsetX, int offsetY, float scaleFactor = 1)
{
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
            glVertex2d(point.x * scaleFactor + offsetX, point.y * scaleFactor + offsetY);
        }
        glEnd();

        // Dibujado de la rama espejada -> Y negativo
        glBegin(GL_LINE_STRIP);
        for (Point point : rotatedPoints)
        {
            glVertex2d(point.x * scaleFactor + offsetX, -point.y * scaleFactor + offsetY);
        }
        glEnd();
    }
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 7; i++)
    {
        int randomOffsetX = rand() % (MAX_WIDTH + 1);
        int randomOffsetY = rand() % (MAX_HEIGHT + 1);
        /* Este scaleFactor queda medio raro por la necesidad de que sea un flotante, entonces es necesario el casteo
            Valor maximo: 1.0f
            Valor minimo: 0.5f
        */
        float scaleFactor = 0.5f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.0 - 0.5)));

        drawSnowflake(randomOffsetX, randomOffsetY, scaleFactor);
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
    glutCreateWindow("TP_3 | Ejercicio 4");
    glutDisplayFunc(draw);
    iniciar();
    glutMainLoop();
}
