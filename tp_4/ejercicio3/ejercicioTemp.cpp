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
float yPosition = 1;
float zPosition;
float theta = M_PI_4;
float radius = 5;
GLenum drawingStyle = GL_FILL;

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
    glEnable(GL_DEPTH_TEST);
    updateCameraRotation();
}

void handleKeyboardAction(unsigned char keyPressed, int x, int y)
{
    switch (keyPressed)
    {
    // >>>>>>>>>>>>>>> Control camara >>>>>>>>>>>>>>>
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
        yPosition += 0.1;
        break;
    case 'q':
        yPosition -= 0.1;
        break;
    }
    updateCameraRotation();
    glutPostRedisplay();
}

void drawAxis()
{
    glBegin(GL_LINES);
    // Eje X
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);

    // Eje Y
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);

    // Eje Z
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
}

void drawTesting(float offsetZ = 0)
{
    ifstream file("./files/testing3.3vn");

    int numVertices;
    file >> numVertices;

    point3D vertices[numVertices];

    // Relleno de matrices
    for (int i = 0; i < numVertices; i++)
    {
        file >> vertices[i].x >> vertices[i].y;
        vertices[i].z = offsetZ;
    }

    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; i++)
    {
        // Obtengo los vertices de la superficie
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
    drawTesting();
    drawTesting(2);

    glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("TP_4 | Ejercicio 5");
    glutDisplayFunc(draw);
    glutKeyboardFunc(handleKeyboardAction);
    iniciar();
    glutMainLoop();
}