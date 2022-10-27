//
// Created by agus on 04/10/22.
//
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <fstream>

#define MAX_WIDTH 1280
#define MAX_HEIGHT 720

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
    gluPerspective(45, (float)16 / 9, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
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

void drawFromFile(string fileName)
{
    ifstream file(fileName);

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
            glVertex3d(vertices[puntoADibujar].x, vertices[puntoADibujar].y, vertices[puntoADibujar].z);
        }
        glEnd();
        // Obtengo los vertices de la normal de una superficie
        for (int j = 0; j < numVerticesSuperficie; j++)
        {
            int normalIndex;
            file >> normalIndex;
        }
    }
}

void drawComposition()
{
    glColor3f(0.609804, 0.609804, 0.304314);
    drawFromFile("files/piso.3vn");
    glColor3f(0.409804, 0.409804, 0.244314);
    drawFromFile("files/pared_1.3vn");
    glColor3f(0.209804, 0.209804, 0.134314);
    drawFromFile("files/pared_2.3vn");
    glColor3f(0.137255, 0.137255, 0.556863);
    drawFromFile("files/mesa.3vn");
    glColor3f(0.137255, 0.556863, 0.137255);
    drawFromFile("files/silla.3vn");
    glColor3f(0.309804, 0.184314, 0.184314);
    drawFromFile("files/pelota.3vn");
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(xPosition, yPosition, zPosition, 0, 0, 0, 0, 1, 0);
    glPolygonMode(GL_FRONT_AND_BACK, drawingStyle);

    drawComposition();

    glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("TP_5 | Ejercicio 1");
    glutDisplayFunc(draw);
    glutKeyboardFunc(handleKeyboardAction);
    iniciar();
    glutMainLoop();
}