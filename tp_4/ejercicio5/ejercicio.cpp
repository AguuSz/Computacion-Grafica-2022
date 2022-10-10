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

//<<<<<<<<<<<<< Variables de transformacion >>>>>>>>>>>>>
float scaleFactor = 1;

float offsetX = 0, offsetY = 0, offsetZ = 0;

float targetXAxis = 0, targetYAxis = 0, targetZAxis = 0, thetaForRotation = 0;

//<<<<<<<<<<<<< Fin variables de transformacion >>>>>>>>>

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

void resetRotatingTargets()
{
    thetaForRotation = 0;
    targetXAxis = 0;
    targetYAxis = 0;
    targetZAxis = 0;
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

        // >>>>>>>>>>>>>>> Control transformaciones >>>>>>>>>>>>>>>
    case 'b': // Activamos la rotacion en el eje X
        resetRotatingTargets();
        targetXAxis = 1;
        break;
    case 'n': // Activamos la rotacion en el eje Y
        resetRotatingTargets();
        targetYAxis = 1;
        break;
    case 'm': // Activamos la rotacion en el eje Z
        resetRotatingTargets();
        targetZAxis = 1;
        break;

    case 'u':
        offsetX++;
        break;
    case 'i':
        offsetY++;
        break;
    case 'o':
        offsetZ++;
        break;
    case 'j':
        offsetX--;
        break;
    case 'k':
        offsetY--;
        break;
    case 'l':
        offsetZ--;
        break;
    }
    updateCameraRotation();
    glutPostRedisplay();
}

void handleMouseAction(int button, int state, int x, int y)
{
    if (state == GLUT_UP)
        return; // Para evitar la redundancia
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        thetaForRotation += 10;
        break;
    case GLUT_RIGHT_BUTTON:
        thetaForRotation -= 10;
        break;
    case 3:
        // Scrolleo hacia arriba
        scaleFactor += 0.1;
        break;
    case 4:
        // Scrolleo hacia abajo
        scaleFactor -= 0.1;
        break;
    default:
        return;
    }
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
        // En este ejercicio se ignoran las normales
        for (int j = 0; j < numVerticesSuperficie; j++)
        {
            int normalIndex;
            file >> normalIndex;
        }
    }
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

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(xPosition, yPosition, zPosition, 0, yPosition, 0, 0, 1, 0);
    glPolygonMode(GL_FRONT_AND_BACK, drawingStyle);

    drawAxis();

    // Escalado
    glScaled(scaleFactor, scaleFactor, scaleFactor);
    // Rotacion
    glRotated(thetaForRotation, targetXAxis, targetYAxis, targetZAxis);
    // Traslacion
    glTranslated(offsetX, offsetY, offsetZ);

    drawFromFile("files/wineglas.3vn");

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
    glutMouseFunc(handleMouseAction);
    iniciar();
    glutMainLoop();
}