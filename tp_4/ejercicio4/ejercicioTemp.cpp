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
float theta = 0;
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
        yPosition++;
        break;
    case 'q':
        yPosition--;
    }
    updateCameraRotation();
    glutPostRedisplay();
}

void drawAxis()
{
    glBegin(GL_LINES);
    // Eje X
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);

    // Eje Y
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 50.0, 0.0);

    // Eje Z
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 50.0);
    glEnd();
}

void drawMahal()
{
    ifstream file("mahal.dat");

    int numVertices;
    file >> numVertices;

    point3D vertices[numVertices];

    // Relleno de matrices
    for (int i = 0; i < numVertices; i++)
    {
        file >> vertices[i].x >> vertices[i].y;
        vertices[i].z = 0;
    }

    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; i++)
    {
        // Obtengo los vertices de la superficie
        glVertex3d(vertices[i].x * 2, vertices[i].y * 2, vertices[i].z * 2);
    }

    glEnd();
}

void drawStuff()
{
    for (int i = 0; i < 360; i += 1)
    {
        glRotated(i, 0, 1, 0);
        drawMahal();
    }
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(xPosition, yPosition, zPosition, 0, yPosition, 0, 0, 1, 0);
    glPolygonMode(GL_FRONT_AND_BACK, drawingStyle);

    drawAxis();
    drawStuff();

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