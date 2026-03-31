// gcc castelo.c -o castelo.exe -I"./include" -L"./bin/x64" -L"./lib-mingw-w64" -lfreeglut -lglu32 -lopengl32
#include <GL/glut.h>

// Variáveis de rotação da cena
static GLfloat yRot = 0.0f;   // rotação horizontal (esquerda/direita)
static GLfloat xRot = 0.0f; 

float angulo = 0;

// ------------------------------------------------------------
// Função chamada quando a janela é redimensionada
// Ajusta a área de visualização e a projeção em perspectiva
// ------------------------------------------------------------
void ChangeSize(int w, int h)
{
    GLfloat fAspect;

    // Evita divisão por zero caso a altura seja 0
    if(h == 0)
        h = 1;

    // Define o tamanho da viewport (área de renderização)
    glViewport(0,0,w,h);

    // Calcula a proporção largura/altura da janela
    fAspect = (GLfloat)w/(GLfloat)h;

    // Seleciona a matriz de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Cria uma projeção em perspectiva
    gluPerspective(35.0f,fAspect,1.0,150.0);

    // Volta para a matriz de modelagem da cena
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// ------------------------------------------------------------
// Configuração inicial da cena (iluminação, profundidade etc.)
// ------------------------------------------------------------
void SetupRC()
{
    // Luz ambiente geral
    GLfloat whiteLight[] = {0.05f,0.05f,0.05f,1.0f};

    // Intensidade da luz principal
    GLfloat sourceLight[] = {0.25f,0.25f,0.25f,1.0f};

    // Posição da luz na cena
    GLfloat lightPos[] = {-10.0f,5.0f,5.0f,1.0f};

    // Habilita teste de profundidade (objetos mais próximos escondem os distantes)
    glEnable(GL_DEPTH_TEST);

    // Define orientação dos polígonos frontais
    glFrontFace(GL_CCW);

    // Remove faces traseiras (melhora desempenho)
    glEnable(GL_CULL_FACE);

    // Habilita sistema de iluminação do OpenGL
    glEnable(GL_LIGHTING);

    // Configura a luz ambiente global
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);

    // Configura a luz 0
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

    glEnable(GL_LIGHT0);

    // Permite que glColor controle o material automaticamente
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

    // Define cor do fundo da cena
    glClearColor(0.25f,0.25f,0.50f,1.0f);
}


// ------------------------------------------------------------
// Função que trata teclas especiais
// Controla a rotação da cena
// ------------------------------------------------------------
void SpecialKeys(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT)
        yRot -= 5.0f;

    if(key == GLUT_KEY_RIGHT)
        yRot += 5.0f;

    if(key == GLUT_KEY_UP)
        xRot -= 5.0f;

    if(key == GLUT_KEY_DOWN)
        xRot += 5.0f;
        
    // Mantém os valores dentro de 0–360 graus
    if (yRot > 360.0f) yRot -= 360.0f;
    if (yRot < 0.0f)   yRot += 360.0f;

    if (xRot > 360.0f) xRot -= 360.0f;
    if (xRot < 0.0f)   xRot += 360.0f;

    // Solicita redesenho da cena
    glutPostRedisplay();
}

GLfloat zDist = -50.0f; 


void Keyboard(unsigned char key, int x, int y) {
    if (key == 'w' || key == 'W') {
        zDist += 2.0f;
    }
    if (key == 's' || key == 'S') {
        zDist -= 2.0f;
    }
    glutPostRedisplay();
}


void torre(float x, float z){

    glPushMatrix();

        glTranslatef(x,0,z);
 GLUquadricObj *pObj = gluNewQuadric(); 
        // corpo da torre
        glColor3f(0.75,0.75,0.75);
        glPushMatrix();
            glTranslatef(0,0.0,0);
            glRotatef(-90,1,0,0);
            gluCylinder(pObj, 0.5f, 0.5f,2.0f ,20,20);
        glPopMatrix();

        // telhado
        glColor3f(0.5,0.1,0.1);
        glPushMatrix();
            glTranslatef(0,2.0,0);
            glRotatef(-90,1,0,0);
            glutSolidCone(0.6,1.0,20,20);
        glPopMatrix();

    glPopMatrix();
}

void arvore(float x, float z){

    glPushMatrix();

        glTranslatef(x,0,z);
 GLUquadricObj *pObj = gluNewQuadric(); 
        // tronco
        glColor3f(0.5,0.3,0.1);
        glPushMatrix();
            glRotatef(-90,1,0,0);
            gluCylinder(pObj, 0.1f, 0.1f,0.8f ,10,10);
  
        glPopMatrix();

        // folhas
        glColor3f(0.0,0.5,0.0);
        glPushMatrix();
            glTranslatef(0,0.8,0);
            glRotatef(-90,1,0,0);
            glutSolidCone(0.5,1.0,20,20);
        glPopMatrix();

    glPopMatrix();
}

void bandeira(float x, float z){

    glPushMatrix();

        glTranslatef(x,2.8,z);
 GLUquadricObj *pObj = gluNewQuadric(); 
        // Mastro
        glColor3f(0.3,0.3,0.3);
        glPushMatrix();
            glRotatef(-90,1,0,0);
            gluCylinder(pObj, 0.05f, 0.05f,1.2f ,10,10);
        glPopMatrix();

        // Bandeira
        glColor3f(0.5,0.1,0.1);
        glPushMatrix();
            glTranslatef(0.4,1.0,0);
            glScalef(0.8,0.4,0.05);
            glutSolidCube(1);
        glPopMatrix();

    glPopMatrix();
}

void castelo(){

    glColor3f(0.8,0.8,0.8);
    // Muros da frente
    glPushMatrix();
        glTranslatef(0,0.8,0.95);
        glScalef(3.0,1.6,0.2);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0.8,-0.95);
        glScalef(3.0,1.6,0.2);
        glutSolidCube(1);
    glPopMatrix();

    // Muros laterais
    glPushMatrix();
        glTranslatef(-1.4,0.8,0.0);
        glScalef(0.2,1.6,2.5);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.4,0.8,0.0);
        glScalef(0.2,1.6,2.5);
        glutSolidCube(1);
    glPopMatrix();

    glColor3f(0,0,0);

    glPushMatrix();
        glTranslatef(0,0.25,1.05);
        glScalef(0.5,0.5,0.05);
        glutSolidCube(1);
    glPopMatrix();

    
    glColor3f(0,0,0);

    for(float i=-0.6;i<=0.6;i+=0.6){
        glPushMatrix();
            glTranslatef(i,0.8,1.05);
            glScalef(0.2,0.2,0.05);
            glutSolidCube(1);
        glPopMatrix();
    }

    for(float i=-0.6;i<=0.6;i+=0.6){
        glPushMatrix();
            glTranslatef(i,0.8,-1.05);
            glScalef(0.2,0.2,0.05);
            glutSolidCube(1);
        glPopMatrix();
    }

    glPushMatrix();
        glTranslatef(-1.5,0.8,0);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glScalef(0.5,0.2,0.05);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.5,0.8,0);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glScalef(0.5,0.2,0.05);
        glutSolidCube(1);
    glPopMatrix();

    torre(-1.5,-1);
    torre(1.5,-1);
    torre(-1.5,1);
    torre(1.5,1);

    bandeira(-1.5,-1);
    bandeira(1.5,-1);
    bandeira(-1.5,1);
    bandeira(1.5,1);
}

void renderScene(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0,-0.5,zDist);

    glRotatef(xRot,1,0,0);
    glRotatef(yRot,0,1,0);

    glRotatef(angulo,0,1,0);

    glColor3f(0.4,0.8,0.4);

    glPushMatrix();
        glTranslatef(0,0,0);
        glScalef(1000,0.1,1000);
        glutSolidCube(1);
    glPopMatrix();

    castelo();

    arvore(-5,3);
    arvore(5,-2);
    arvore(-4,-3);
    arvore(4,3);

    glutSwapBuffers();
}

void init(){

    glClearColor(0.5,0.7,1.0,1);

    glEnable(GL_DEPTH_TEST);
}


int main(int argc, char** argv){

    glutInit(&argc,argv);
   

    // modo gráfico com buffer duplo, cores RGB e profundidade
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800,600);

    glutCreateWindow("Castelo - OpenGL");

    // registra funções de callback
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutKeyboardFunc(Keyboard);

    glutDisplayFunc(renderScene);

    // configura iluminação e estado inicial
    SetupRC();

    glutMainLoop();

    return 0;
}
