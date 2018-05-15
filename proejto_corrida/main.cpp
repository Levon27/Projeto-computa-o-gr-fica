/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <windows.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static int slices = 16;
static int stacks = 16;
float rot = 0.0;
float rot2 = 0.0;
void eixos(float T)
{

    glBegin(GL_LINES);

    glColor3f(1,0,0);

    glVertex3f(0,0,0);
    glVertex3f(T,0,0);

    glColor3f(0,1,0);

    glVertex3f(0,0,0);
    glVertex3f(0,T,0);

    glColor3f(0,0,1);

    glVertex3f(0,0,0);
    glVertex3f(0,0,T);

    glEnd();

};

void face()
{
    float i,j;
    float n=15;
    glBegin(GL_QUADS);

    for(j=0; j<n; j++)
    {
        for (i=0; i<n; i++)
        {
            glNormal3f(0,0,1.0f);
            glVertex3f(-0.5+i/n,0.5-j/n,0.0);
            glVertex3f(-0.5+i/n,0.5-(j+1)/n,0.0);
            glVertex3f(-0.5+(i+1)/n,0.5-(j+1)/n,0.0);
            glVertex3f(-0.5+(i+1)/n,0.5-(j)/n,0.0);
        }
    }

    glEnd();
}

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
float zoom = 1.0;
static void display(void)
{


    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* VISTA ORTGRAFICA */

    //glOrtho(-70.0/zoom, 70.0/zoom, -50.0/zoom, 70.0/zoom, -100.0, 100.0);

    /* VISTA PERSPECTIVA */
    glFrustum(-7.0/zoom, 7.0/zoom, -5.0/zoom, 7.0/zoom, -100.0, 100.0);



    /* posição  da camera para debug */
    //gluLookAt(1*cos(rot)*sin(rot2), 1*sin(rot)*sin(rot2), 5.0*cos(rot2), 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    //glRotatef(10.0*cos(rot),0.0,1.0,0.0);
    //glTranslatef(0.0,0.0,rot2);





    gluLookAt(2*cos(rot)*sin(rot2), 1*sin(rot)*sin(rot2), 5.0*cos(rot2), 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);


    glMatrixMode(GL_MODELVIEW);

    //criando eixos
    glPushMatrix();
        eixos(80);
    glPopMatrix();



    float comp = 100.0; // comprimento da pista + chao

    /* CHAO */
    glPushMatrix();
        glColor3f(0.2,0.7,0.0);
        glTranslatef(comp/2,0,0); //    translada por comp/2 p/ que o inicio
        glScalef(comp,80.0,1.0);  //    da pista coincida com a origem do eixo X
        face();
    glPopMatrix();


    /* PISTA */
    glPushMatrix();
        glColor3b(83, 81, 85);
        glTranslatef(comp/2,0.0,0.1); //    pista deslocada 0.1 pra cima p/ aparecer
        glScalef(comp,20.0,1.0);
        face();
    glPopMatrix();



    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
        case 'a':
        rot -= 0.05f;
        break;

        case 'd':
        rot += 0.05f;
        break;

        case 's':
        rot2 -= 0.05f;
        break;

        case 'w':
        rot2 += 0.05f;
        break;
    }

    glutPostRedisplay();
}



static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
