//
// Created by agus on 04/10/22.
//
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <fstream>

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

using namespace std;

struct point3D
{
    float x;
    float y;
    float z;
};

float xPosition;
float yPosition = 2;
float zPosition;
float theta = M_PI_4;
float radius = 10;
GLenum drawingStyle = GL_LINE;

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>

void updateCameraRotation()
{
    xPosition = radius * sin(theta);
    zPosition = radius * cos(theta);
}

void iniciar(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    gluPerspective(45, (float)16 / 9, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    updateCameraRotation();
}

void handleKeyboardAction(unsigned char keyPressed, int x, int y)
{
    switch (keyPressed)
    {
    case 'f':
        if (drawingStyle == GL_LINE)
            drawingStyle = GL_FILL;
        else
            drawingStyle = GL_LINE;
        break;
    case 's':
        radius++;
        break;
    case 'w':
        radius--;
        break;
    case 'd':
        theta += 0.0872665; // +5 grados
        break;
    case 'a':
        theta -= 0.0872665; // -5 grados
        break;
    case 'e':
        yPosition += 0.2;
        break;
    case 'q':
        yPosition -= 0.2;
    }
    updateCameraRotation();
    glutPostRedisplay();
}

point3D rotateY(point3D point, float theta)
{
    float x, y, z;
    x = point.x * cos(theta) - point.z * sin(theta);
    y = point.y;
    z = point.z * cos(theta) + point.x * sin(theta);

    return point3D{x, y, z};
}

void drawAxis()
{
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    // Eje X
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);

    // Eje Y
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 50.0, 0.0);

    // Eje Z
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 50.0);
    glColor3f(0.0, 0.0, 0.0);
    glEnd();
}

void drawMahal(float offset = 0)
{
    ifstream file("./files/mahal.dat");

    int numVertices;
    file >> numVertices;

    int slices = 17;
    point3D vertices[numVertices * slices];

    // Relleno de matrices
    for (int i = 0; i < numVertices; i++)
    {
        file >> vertices[i].x >> vertices[i].y;
        vertices[i].z = offset;
    }

    // Relleno de matriz con los puntos restantes
    for (int j = 0; j < slices; j++)
    {
        for (int i = 0; i < numVertices; i++)
        {
            point3D tempPoint = rotateY(vertices[i], (M_PI / 8) * j);
            vertices[i + numVertices * j].x = tempPoint.x;
            vertices[i + numVertices * j].y = tempPoint.y;
            vertices[i + numVertices * j].z = tempPoint.z;
        }
    }

    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices * (slices - 1); i++)
    {
        // Obtengo los vertices de la superficie
        glVertex3d(vertices[i].x, vertices[i].y, vertices[i].z);
        glVertex3d(vertices[i + numVertices].x, vertices[i + numVertices].y, vertices[i + numVertices].z);
        glVertex3d(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(xPosition, yPosition, zPosition, 0, yPosition, 0, 0, 1, 0);
    glPolygonMode(GL_FRONT_AND_BACK, drawingStyle);

    drawAxis();
    drawMahal();

    glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("TP_4 | Ejercicio 4");
    glutDisplayFunc(draw);
    glutKeyboardFunc(handleKeyboardAction);
    iniciar();
    glutMainLoop();
}