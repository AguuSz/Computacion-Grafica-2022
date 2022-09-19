#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <fstream>

#define MAX_WIDTH 1024
#define MAX_HEIGHT 576

using namespace std;

struct Point
{
    int x;
    int y;
};

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLineWidth(3);
    glLoadIdentity();
    gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
}

Point rotate(Point point, double theta)
{
    int x, y;
    x = point.x * cos(theta) - point.y * sin(theta);
    y = point.x * sin(theta) + point.y * cos(theta);

    return Point{x, y};
}

void drawDino(int offsetX, int offsetY, float scaleFactor, float theta)
{
    ifstream file("../dino.dat");
    string line;

    getline(file, line);
    getline(file, line);
    getline(file, line); // cantidad de lineas a dibujar
    int cantidadLineas = stoi(line);

    for (int i = 0; i < cantidadLineas; i++)
    {
        getline(file, line);
        if (line[0] == '#')
        {
            i--;
            continue;
        }
        int cantidadPuntos = stoi(line);
        Point previousPoint;

        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < cantidadPuntos; j++)
        {
            getline(file, line);
            Point temporaryPoint;

            if (line[0] == '#')
            {
                j--;
                continue;
            }

            temporaryPoint.x = stoi(line.substr(0, line.find(' ')));
            temporaryPoint.y = stoi(line.substr(line.find(' '), line.length() - 1));

            temporaryPoint = rotate(temporaryPoint, theta);

            glVertex2d(temporaryPoint.x * scaleFactor + offsetX, temporaryPoint.y * scaleFactor + offsetY);
        }
        glEnd();
    }
    file.close();
}

void drawCircle(bool rotated)
{
    float radius = 150.0f;
    for (int i = 0; i < 12; i++)
    {
        float theta = 2.0f * M_PI * float(i) / 12.0f;
        float x = radius * cosf(theta) + MAX_WIDTH / 2;
        float y = radius * sinf(theta) + MAX_HEIGHT / 2;
        float thetaRotation = theta - M_PI_2;

        if (!rotated)
            thetaRotation = 0;

        drawDino(x, y, 0.2, thetaRotation);
    }
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle(false);
    glFlush();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("TP_3 | Ejercicio 5");
    glutDisplayFunc(draw);
    iniciar();
    glutMainLoop();
}
