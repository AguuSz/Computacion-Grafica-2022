//
// Created by agus on 03/10/22.
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
GLenum drawingStyle = GL_LINE;

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
}

void handleKeyboardAction(unsigned char keyPressed, int x, int y)
{
    switch (keyPressed)
    {
    case 97:
        // Tecla presionada: a
        if (drawingStyle == GL_LINE)
            drawingStyle = GL_FILL;
        else
            drawingStyle = GL_LINE;
        break;
    }
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
    glVertex3f(2.0, 0.0, 0.0);

    // Eje Y
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 2.0, 0.0);

    // Eje Z
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 2.0);
    glEnd();
}

void drawPrism()
{
    ifstream file("/home/agus/CLionProjects/untitled/prism.3vn");

    int numVertices, numNormales, numSuperficies;
    file >> numVertices >> numNormales >> numSuperficies;

    point3D vertices[numVertices], normales[numNormales];

    // Relleno de matrices
    for (int i = 0; i < numVertices; i++)
    {
        file >> vertices[i].x >> vertices[i].y >> vertices[i].z;
    }
    for (int i = 0; i < numNormales; i++)
    {
        file >> normales[i].x >> normales[i].y >> normales[i].z;
    }

    // TODO: Falta el calculo de la normal
    // Creacion de superficies en base a los vertices ya creados
    for (int i = 0; i < numSuperficies; i++)
    {
        int numVerticesSuperficie;
        file >> numVerticesSuperficie;

        // Obtengo los vertices de la superficie
        glBegin(GL_POLYGON);
        for (int j = 0; j < numVerticesSuperficie; j++)
        {
            int puntoADibujar;
            file >> puntoADibujar;
            glVertex3d(vertices[puntoADibujar].x / 4, vertices[puntoADibujar].y / 2, vertices[puntoADibujar].z / 4);
        }
        glEnd();
        // Obtengo los vertices de la normal de una superficie
        // En este ejercicio se ignoran las normales
        for (int j = 0; j < numVerticesSuperficie; j++)
        {
            int normalIndex;
            file >> normalIndex;
        }
    }
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(heightAngle, 1, 0, 0); // Controla el alto
    glRotatef(widthAngle, 0, 1, 0);  // Controla lo horizontal
    glPolygonMode(GL_FRONT_AND_BACK, drawingStyle);

    drawAxis();
    drawPrism();

    glFlush();
    glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("TP_4 | Ejercicio 2");
    glutDisplayFunc(draw);
    glutKeyboardFunc(handleKeyboardAction);
    glutSpecialFunc(handleWindowSpecial);
    iniciar();
    glutMainLoop();
}
