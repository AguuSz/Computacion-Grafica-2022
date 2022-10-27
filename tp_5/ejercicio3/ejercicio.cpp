//
// Created by agus on 21/10/22.
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
float theta = M_PI_4;
float radius = 5;
GLenum drawingStyle = GL_FILL;

int state = 0;

//<<<<<<<<<<<<< Colores >>>>>>>>>>>>>
float BLACK[] = {0.0f, 0.0f, 0.0f, 1.0f};
float RED_LOW[] = {0.5f, 0.0f, 0.0f};
float WHITE[] = {1.0f, 1.0f, 1.0f};
//<<<<<<<<<<<<< Fin colores >>>>>>>>>

//<<<<<<<<<<<<< Variables de transformacion >>>>>>>>>>>>>
float scaleFactor = 1;

float offsetX = 0, offsetY = 0, offsetZ = 0;

float targetXAxis = 0, targetYAxis = 0, targetZAxis = 0, thetaForRotation = 0;

//<<<<<<<<<<<<< Fin variables de transformacion >>>>>>>>>

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>

void initLight()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);

    float position[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float direction[] = {-1.0, 0.0, -1.0};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);

    // El 30.0 este indica el angulo que va a tener nuestra luz
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
}

void updateCameraRotation()
{
    xPosition = radius * sin(theta);
    zPosition = radius * cos(theta);
}

void iniciar(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluPerspective(45, (float)16 / 9, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel(GL_SMOOTH);
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
    case 'x':
        state++;
        if (state == 3)
            state = 0;
        break;
    }
    updateCameraRotation();
    glutPostRedisplay();
}

void handleMouseAction(int button, int mouseState, int x, int y)
{
    if (mouseState == GLUT_UP)
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
        // Obtengo los vertices de la normal de una superficie
        for (int j = 0; j < numVerticesSuperficie; j++)
        {
            int normalIndex;
            file >> normalIndex;
            glNormal3d(normales[normalIndex].x, normales[normalIndex].y, normales[normalIndex].z);
        }
        glEnd();
    }
}

void loadTransformations()
{
    // Escalado
    glScaled(scaleFactor, scaleFactor, scaleFactor);
    // Rotacion
    glRotated(thetaForRotation, targetXAxis, targetYAxis, targetZAxis);
    // Traslacion
    glTranslated(offsetX, offsetY, offsetZ);
}

void drawAxis()
{
    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);
    glColor3d(1, 0, 0);
    glVertex3d(-10, 0, 0);
    glVertex3d(10, 0, 0);

    glColor3d(0, 1, 0);
    glVertex3d(0, -10, 0);
    glVertex3d(0, 10, 0);

    glColor3d(0, 0, 1);
    glVertex3d(0, 0, -10);
    glVertex3d(0, 0, 10);
    glEnd();

    glEnable(GL_LIGHTING);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(xPosition, yPosition, zPosition, 0, 1, 0, 0, 1, 0);
    glPolygonMode(GL_FRONT_AND_BACK, drawingStyle);

    initLight();
    drawAxis();

    // Dibujo la esfera que actua como punto en el plano, para indicar donde va a estar la luz
    glMaterialfv(GL_FRONT, GL_EMISSION, WHITE);
    glTranslated(1.0, 1.0, 1.0);
    glutSolidSphere(0.05, 20, 20);
    glTranslated(-1.0, -1.0, -1.0);

    loadTransformations();
    glMaterialfv(GL_FRONT, GL_EMISSION, BLACK);
    switch (state)
    {
    case 0:
        drawFromFile("files/wineglas.3vn");
        break;
    case 1:
        glutSolidTeapot(1);
        break;
    case 2:
        glutSolidOctahedron();
        break;
    }

    glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("TP_5 | Ejercicio 3");
    glutDisplayFunc(draw);
    glutKeyboardFunc(handleKeyboardAction);
    glutMouseFunc(handleMouseAction);
    iniciar();
    glutMainLoop();
}