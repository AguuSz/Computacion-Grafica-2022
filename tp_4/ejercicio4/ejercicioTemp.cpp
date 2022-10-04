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

int theta;
int widthAngle = -45, heightAngle = 45;
float xPosition = 5, yPosition = 1, zPosition = 5;
GLenum drawingStyle = GL_LINE;

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    gluPerspective(45, (float)16 / 9, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void handleKeyboardAction(unsigned char keyPressed, int x, int y)
{
    switch (keyPressed)
    {
    case 'f':
        // Tecla presionada: a
        if (drawingStyle == GL_LINE)
            drawingStyle = GL_FILL;
        else
            drawingStyle = GL_LINE;
        break;
    case 's':
        xPosition += 0.2;
        zPosition += 0.2;
        break;
    case 'w':
        xPosition -= 0.2;
        zPosition -= 0.2;
        break;
    case 'd':
        yPosition += 0.2;
        break;
    case 'a':
        yPosition -= 0.2;
        break;
    }

    cout << xPosition << " " << yPosition << " " << zPosition << endl;
    glutPostRedisplay();
}

// Funcion encargada de controlar las acciones cuando se pulsa una flecha del teclado
void handleWindowSpecial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        widthAngle += 5;
        break;
    case GLUT_KEY_LEFT:
        widthAngle -= 5;
        break;
    case GLUT_KEY_UP:
        heightAngle += 5;
        break;
    case GLUT_KEY_DOWN:
        heightAngle -= 5;
        break;
    }

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
    //    glLoadIdentity();
    for (int i = 0; i < 360; i += 1)
    {
        drawMahal();
        glRotated(i, 0, 1, 0);
    }
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(xPosition, yPosition, zPosition, 0, yPosition, 0, 0, 1, 0);
    //    glRotatef(heightAngle, 1, 0, 0); // Controla el alto
    //    glRotatef(widthAngle, 0, 1, 0); // Controla lo horizontal
    glPolygonMode(GL_FRONT_AND_BACK, drawingStyle);

    drawAxis();
    drawStuff();

    //    glFlush();
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
    glutSpecialFunc(handleWindowSpecial);
    iniciar();
    glutMainLoop();
}