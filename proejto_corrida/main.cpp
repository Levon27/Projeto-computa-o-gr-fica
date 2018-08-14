
#include <windows.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
void DesenhaObstaculo(float ,float ,float , float , float ,float , float , float);
void DesenhaTexto(char *texto, float x, float y, float r, float g, float b);
void cubo(float,float,float);
void eixos(float);
static void resize (int,int);
void face();
void faceCubo(float);

float rot = 0.0;
float rot2 = 0.0;
float ang = 0.0;
float ang2 = 0.0; //angulo em relacao ao eixo X
float p[3] = {0.0, 0.0, 4.0}; //posicao da camera
float dir[3] = {1.0, 0.0, 0.0}; //direcao da camera ---
char texto[30];
float zoom = 1.0;
float comp = 100.0; // comprimento da pista e chao
float larg = 20.0;

static void display(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);

    /* VISTA ORTGRAFICA */

    //glOrtho(-70.0/zoom, 70.0/zoom, -50.0/zoom, 70.0/zoom, -100.0, 100.0);

    /* VISTA PERSPECTIVA */
    gluPerspective(90.0,1.0,1.0,1000.0);
    gluLookAt(0, 0, 0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0); //pos inicial do jogador


    /* posição  da camera para debug */
    //gluLookAt(1*cos(rot)*sin(rot2), 1*sin(rot)*sin(rot2),1*cos(rot2), 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    //glRotatef(ang,0.0,0.0,1.0);  //gira a camera do jogador

    ang2 += ang;
    ang = 0.0;

    dir[0]= cos(-ang2*M_PI/180); //x
    dir[1]= sin(-ang2*M_PI/180); //y

    //criando eixos
    glPushMatrix();
        glRotatef(ang2,0,0,1.0);
        glTranslatef(-p[0],-p[1],-p[2]);
        eixos(80);
    glPopMatrix();

    /* CHAO */
    glPushMatrix();
        glRotatef(ang2,0,0,1.0);
        glTranslatef(-p[0],-p[1],-p[2]);
        glColor3f(0.2,0.7,0.0);
        glTranslatef(comp/2,0,0);     //        translada por comp/2 p/ que o inicio
        glScalef(comp,80.0,1.0);      //        da pista coincida com a origem do eixo X
        face();
    glPopMatrix();

    /* PISTA */
    glPushMatrix();
        glRotatef(ang2,0,0,1.0);
        glTranslatef(-p[0],-p[1],-p[2]);
        glColor3b(83, 81, 85);
        glTranslatef(comp/2,0.0,0.01); //    pista deslocada 0.01 pra cima p/ aparecer
        glScalef(comp,larg,1.0);
        face();
    glPopMatrix();
    //*/
    /* TESTE CUBO */
    glPushMatrix();
        //glTranslatef(5.0,3.0,5.0);
        glScalef(10,10,10);
        cubo(30,0,3);
    glPopMatrix();
    /*
    glPushMatrix();
        DesenhaObstaculo(100.0,100.0,10.0,10.0,10.0,10.0,10.0,10.0);
    glPopMatrix();
    */
    glPushMatrix();
        sprintf(texto,"%f %f",dir[0],dir[1]);
        DesenhaTexto(texto,500,200,1,1,1);
    glPopMatrix();

    /* volta a pos do jogador caso ele saia da pista */

    if (p[1]> larg/2)
        p[1] = larg/2-0.1;
    if (p[1]< -larg/2)
        p[1] = -larg/2+0.1;

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
            zoom += 0.01;
            break;

        case '-':
            zoom -= 0.01;
            break;

        case 's':
        p[0] -= 1.0*dir[0]; //anda para tras
        if (p[1]<larg/2 && p[1]>-larg/2)
            p[1] -= 1.0*dir[1];
            break;

        case 'w':
        p[0] += 1.0*dir[0]; //anda para frente
        if (p[1]<larg/2 && p[1]>-larg/2)
            p[1] += 1.0*dir[1];
            break;

        case 'a':
        ang -= 1.2;
            break;

        case 'd':
        ang += 1.2;
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

    glutCreateWindow("Corrida");

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

void DesenhaObstaculo(float x1,float y1,float x2, float y2, float x3,float y3, float x4, float y4){
    float h = 100.0;
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
        glVertex3f(x1,y1,0);
        glVertex3f(x2,y2,0);
        glVertex3f(x2,y2,h);
        glVertex3f(x1,y1,h);
    glEnd();
}

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
void DesenhaTexto(char *texto, float x, float y, float r, float g, float b)
{
    glDisable(GL_LIGHTING);    // se estiver usando a iluminação
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 640, 0, 480, -1.0, 1.0); // usar o mesmo tamanho da janela

    /*
    // background do texto
    // fazer isso antes de desenhar o texto
    int w = glutBitmapLength(GLUT_BITMAP_HELVETICA_18,(unsigned char*)texto); // largura do texto em px
    float borda = 2; // folga pata borda
    float h = 18; // altura da fonte
    float d = h/4; // descendente para letras como "g", "j", "p", "q" e "y"

    glColor3f(1-r,1-g,1-b); // escolher a cor
    glBegin(GL_QUADS);
        glVertex3f(x-borda,   y+borda+h, -0.5);
        glVertex3f(x-borda,   y-borda-d , -0.5);
        glVertex3f(x+borda+w, y-borda-d, -0.5);
        glVertex3f(x+borda+w, y+borda+h, -0.5);
    glEnd();
    */

    glColor3f(r,g,b);
    glRasterPos2f(x, y);       // define a posição do texto
    while(*texto)               // Exibe caracter a caracter
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*texto++);
    }

    glPopMatrix();
    glEnable(GL_LIGHTING);     // se estiver usando a iluminação
}
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
void cubo(float x,float y,float tamanho)
{
    float t = tamanho;
    glLoadIdentity();
    //face de cima
    glRotatef(ang2,0,0,1.0);
    glTranslatef(-p[0],-p[1],-p[2]);

    glTranslatef(x,y,1);
    glColor3f(1,1,1);
    glScalef(t,t,t);
    faceCubo(t);

    //face da frente
    glRotatef(90,-1,0,0);
    faceCubo(t);

    //face de tras
    glRotatef(180,-1,0,0);
    faceCubo(t);

    glLoadIdentity();
    //face esquerda
    glRotatef(ang2,0,0,1.0);
    glTranslatef(-p[0],-p[1],-p[2]);

    glTranslatef(x,y,1);

    glColor3f(1,1,1);
    glRotatef(90,0,1,0);
    glScalef(t,t,t);
    faceCubo(t);

    glRotatef(180,0,1,0);
    faceCubo(t);

}
void faceCubo(float tam)
{
    float i,j;
    float n=15;
    glBegin(GL_QUADS);

    for(j=0; j<n; j++)
    {
        for (i=0; i<n; i++)
        {
            //glScalef(tam,tam,tam);
            glNormal3f(0,0,1.0f);
            glVertex3f(-0.5+i/n,0.5-j/n,0.5);
            glVertex3f(-0.5+i/n,0.5-(j+1)/n,0.5);
            glVertex3f(-0.5+(i+1)/n,0.5-(j+1)/n,0.5);
            glVertex3f(-0.5+(i+1)/n,0.5-(j)/n,0.5);
        }
    }
    glEnd();
}
