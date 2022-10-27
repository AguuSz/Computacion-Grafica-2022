//
// Created by agus on 27/10/22.
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
int lightState = 0;

//<<<<<<<<<<<<< Variables de transformacion >>>>>>>>>>>>>
float scaleFactor = 1;

float offsetX = 0, offsetY = 0, offsetZ = 0;

float targetXAxis = 0, targetYAxis = 0, targetZAxis = 0, thetaForRotation = 0;

//<<<<<<<<<<<<< Fin variables de transformacion >>>>>>>>>

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>

void initLight()
{
    GLfloat light_position[] = {1.0, 0.5, 1.0, 1.0};
    glShadeModel(GL_SMOOTH);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void setMaterial()
{
    GLfloat mat_ambient[4];
    GLfloat mat_diffuse[4];
    GLfloat mat_specular[4];
    GLfloat mat_shininess[1];

    switch (lightState)
    {
    case 0:
        mat_ambient[0] = 0.0;
        mat_ambient[1] = 0.0;
        mat_ambient[2] = 0.0;
        mat_ambient[3] = 1.0;

        mat_diffuse[0] = 0.01;
        mat_diffuse[1] = 0.01;
        mat_diffuse[2] = 0.01;
        mat_diffuse[3] = 1.0;

        mat_specular[0] = 0.5;
        mat_specular[1] = 0.5;
        mat_specular[2] = 0.5;
        mat_specular[3] = 1.0;

        mat_shininess[0] = 32.0;
        break;
    case 1:
        // Brass
        mat_ambient[0] = 0.329412;
        mat_ambient[1] = 0.223529;
        mat_ambient[2] = 0.027451;
        mat_ambient[3] = 1.0;

        mat_diffuse[0] = 0.780392;
        mat_diffuse[1] = 0.568627;
        mat_diffuse[2] = 0.113725;
        mat_diffuse[3] = 1.0;

        mat_specular[0] = 0.992157;
        mat_specular[1] = 0.941176;
        mat_specular[2] = 0.807843;
        mat_specular[3] = 1.0;

        mat_shininess[0] = 27.8974;
        break;
    case 2:
        // Bronze
        mat_ambient[0] = 0.2125;
        mat_ambient[1] = 0.1275;
        mat_ambient[2] = 0.393548;
        mat_ambient[3] = 1.0;

        mat_diffuse[0] = 0.714;
        mat_diffuse[1] = 0.4284;
        mat_diffuse[2] = 0.271906;
        mat_diffuse[3] = 1.0;

        mat_specular[0] = 0.393548;
        mat_specular[1] = 0.18144;
        mat_specular[2] = 0.166721;
        mat_specular[3] = 1.0;

        mat_shininess[0] = 25.6;
        break;

    case 3:
        // Chrome
        mat_ambient[0] = 0.25;
        mat_ambient[1] = 0.25;
        mat_ambient[2] = 0.25;
        mat_ambient[3] = 1.0;

        mat_diffuse[0] = 0.4;
        mat_diffuse[1] = 0.4;
        mat_diffuse[2] = 0.4;
        mat_diffuse[3] = 1.0;

        mat_specular[0] = 0.774597;
        mat_specular[1] = 0.774597;
        mat_specular[2] = 0.774597;
        mat_specular[3] = 1.0;

        mat_shininess[0] = 76.8;
        break;

    case 4:
        // Copper
        mat_ambient[0] = 0.19125;
        mat_ambient[1] = 0.0735;
        mat_ambient[2] = 0.0225;
        mat_ambient[3] = 1.0;

        mat_diffuse[0] = 0.7038;
        mat_diffuse[1] = 0.27048;
        mat_diffuse[2] = 0.0828;
        mat_diffuse[3] = 1.0;

        mat_specular[0] = 0.256777;
        mat_specular[1] = 0.137622;
        mat_specular[2] = 0.086014;
        mat_specular[3] = 1.0;

        mat_shininess[0] = 12.8;
        break;

    case 5:
        // Gold
        mat_ambient[0] = 0.24725;
        mat_ambient[1] = 0.1995;
        mat_ambient[2] = 0.0745;
        mat_ambient[3] = 1.0;

        mat_diffuse[0] = 0.75164;
        mat_diffuse[1] = 0.60648;
        mat_diffuse[2] = 0.22648;
        mat_diffuse[3] = 1.0;

        mat_specular[0] = 0.628281;
        mat_specular[1] = 0.555802;
        mat_specular[2] = 0.366065;
        mat_specular[3] = 1.0;

        mat_shininess[0] = 51.2;
        break;

    case 6:
        // Pewter
        mat_ambient[0] = 0.10588;
        mat_ambient[1] = 0.058824;
        mat_ambient[2] = 0.113725;
        mat_ambient[3] = 1.0;

        mat_diffuse[0] = 0.427451;
        mat_diffuse[1] = 0.470588;
        mat_diffuse[2] = 0.541176;
        mat_diffuse[3] = 1.0;

        mat_specular[0] = 0.3333;
        mat_specular[1] = 0.3333;
        mat_specular[2] = 0.521559;
        mat_specular[3] = 1.0;

        mat_shininess[0] = 9.84615;
        break;

    case 7:
        // Silver
        mat_ambient[0] = 0.19225;
        mat_ambient[1] = 0.19225;
        mat_ambient[2] = 0.19225;
        mat_ambient[3] = 1.0;

        mat_diffuse[0] = 0.50754;
        mat_diffuse[1] = 0.50754;
        mat_diffuse[2] = 0.50754;
        mat_diffuse[3] = 1.0;

        mat_specular[0] = 0.508273;
        mat_specular[1] = 0.508273;
        mat_specular[2] = 0.508273;
        mat_specular[3] = 1.0;

        mat_shininess[0] = 51.2;
        break;

    case 8:
        // Polished silver
        mat_ambient[0] = 0.23125;
        mat_ambient[1] = 0.23125;
        mat_ambient[2] = 0.23125;
        mat_ambient[3] = 1.0;

        mat_diffuse[0] = 0.2775;
        mat_diffuse[1] = 0.2775;
        mat_diffuse[2] = 0.2775;
        mat_diffuse[3] = 1.0;

        mat_specular[0] = 0.773911;
        mat_specular[1] = 0.773911;
        mat_specular[2] = 0.773911;
        mat_specular[3] = 1.0;

        mat_shininess[0] = 89.6;
        break;
    default:
        break;
    }

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
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

    case 't':
        cout << "Lightstate: " << lightState << endl;
        if (lightState < 8)
            lightState++;
        else
            lightState = 0;
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
    setMaterial();
    drawAxis();

    loadTransformations();
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
    glutCreateWindow("TP_5 | Ejercicio 4");
    glutDisplayFunc(draw);
    glutKeyboardFunc(handleKeyboardAction);
    glutMouseFunc(handleMouseAction);
    iniciar();
    glutMainLoop();
}
