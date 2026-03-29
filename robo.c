// gcc robo.c -o robo.exe -I"./include" -L"./bin/x64" -L"./lib-mingw-w64" -lfreeglut -lglu32 -lopengl32

#include <GL/glut.h>
#include <stdio.h>

// Variáveis de rotação da cena
static GLfloat yRot = 0.0f;   // rotação horizontal (esquerda/direita)
static GLfloat xRot = 0.0f; 


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


// ------------------------------------------------------------
// Função principal de renderização
// Desenha todos os objetos da cena
// ------------------------------------------------------------
void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0,-0.5,zDist);

    glRotatef(xRot,1,0,0);
    glRotatef(yRot,0,1,0);

    glRotatef(0,0,1,0);

    glColor3f(0.4,0.8,0.4);

    glPushMatrix();
        glTranslatef(0,0,0);
        glScalef(1000,0.1,1000);
        glutSolidCube(1);
    glPopMatrix();

    // Cabeca
    glColor3f(0.9f,0.9f,0.9f); // Branco

    glPushMatrix();
        glTranslatef(1.9f,15.8f,-0.70f);
        glutSolidSphere(0.85f,40,40);
    glPopMatrix();

    // Articulacao ombro
    glColor3f(0.9f,0.9f,0.9f); // Branco

    glPushMatrix();
        glTranslatef(-0.5f,14.65f,-0.70f);
        glutSolidSphere(0.6f,40,40);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4.1f,14.65f,-0.70f);
        glutSolidSphere(0.6f,40,40);
    glPopMatrix();

    // Braco
    glColor3f(0.4f, 0.0f, 0.4f); // Roxo
    glPushMatrix(); 
        glTranslatef(-0.5f,12.85f,-0.70f);
        glScalef(0.7f,2.67f,0.9f);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(4.1f,12.85f,-0.70f);
        glScalef(0.7f,2.67f,0.9f);
        glutSolidCube(1);
    glPopMatrix();

    // Articulacao antebraco
    glColor3f(0.9f,0.9f,0.9f); // Branco

    glPushMatrix();
        glTranslatef(-0.5f,11.65f,-0.70f);
        glutSolidSphere(0.6f,40,40);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4.1f,11.65f,-0.70f);
        glutSolidSphere(0.6f,40,40);
    glPopMatrix();

    // Antebraco
    glColor3f(0.4f, 0.0f, 0.4f); // Roxo

    glPushMatrix();
        glTranslatef(-0.5f,10.75f,0.5f);
        glScalef(1.05f,1.05f,3.2f);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4.1f,10.75f,0.5f);
        glScalef(1.05f,1.05f,3.2f);
        glutSolidCube(1);
    glPopMatrix();

    // Mao
    glColor3f(0.9f,0.9f,0.9f); // Branco

    glPushMatrix();
        glTranslatef(-0.5f,10.75f,2.0f);
        glScalef(0.55f,0.55f,0.55f);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4.1f,10.75f,2.0f);
        glScalef(0.55f,0.55f,0.55f);
        glutSolidCube(1);
    glPopMatrix();

    // Tronco
    glColor3f(0.4f, 0.0f, 0.4f); // Roxo


    glPushMatrix();
        glTranslatef(1.80f,12.65f,-0.70f);
        glScalef(3.80f,5.05f,1.9f);
        glutSolidCube(1);
    glPopMatrix();

    // Cintura
    glColor3f(0.4f, 0.0f, 0.4f); // Roxo

    glPushMatrix();
        glTranslatef(1.80f,9.65f,-0.70f);
        glScalef(3.80f,1.05f,0.9f);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.85f,8.65f,-0.70f);
        glScalef(1.75f,1.05f,0.9f);
        glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.9f,0.9f,0.9f); // Branco
    // Articulacao quadril

    glPushMatrix();
        glTranslatef(0.35f,8.55f,-0.70f);
        glutSolidSphere(0.6f,40,40);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(3.35f,8.55f,-0.70f);
        glutSolidSphere(0.6f,40,40);
    glPopMatrix();

    // Coxa
    glColor3f(0.4f, 0.0f, 0.4f); // Roxo

    glPushMatrix(); 
        glTranslatef(0.35f,6.20f,-0.70f);
        glScalef(0.9f,4.05f,0.9f);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(3.35f,6.20f,-0.70f);
        glScalef(0.9f,4.05f,0.9f);
        glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.9f,0.9f,0.9f); // Branco
    // Articulacao do joelho

    glPushMatrix();
        glTranslatef(0.35f,4.0f,-0.70f);
        glutSolidSphere(0.6f,40,40);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(3.35f,4.0f,-0.70f);
        glutSolidSphere(0.6f,40,40);
    glPopMatrix();

    // Antes do pe
    glColor3f(0.4f, 0.0f, 0.4f); // Roxo

    glPushMatrix();
        glTranslatef(0.35f,2.0f,-0.70f);
        glScalef(1.05f,4.05f,1.55f);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(3.35f,2.0f,-0.70f);
        glScalef(1.05f,4.05f,1.55f);
        glutSolidCube(1);
    glPopMatrix();

    // Pe
    glColor3f(0.9f,0.9f,0.9f); // Branco

    glPushMatrix();
        glTranslatef(0.35f,0.32f,0.05f);
        glScalef(1.05f,0.55f,2.05f);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(3.35f,0.32f,0.05f);
        glScalef(1.05f,0.55f,2.05f);
        glutSolidCube(1);
    glPopMatrix();

    glutSwapBuffers();
}


// ------------------------------------------------------------
// Função principal
// Inicializa o GLUT e registra callbacks
// ------------------------------------------------------------
int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
   

    // modo gráfico com buffer duplo, cores RGB e profundidade
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800,600);

    glutCreateWindow("Robo- OpenGL");

    // registra funções de callback
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(RenderScene);

    // configura iluminação e estado inicial
    SetupRC();

    // inicia loop principal do GLUT
    glutMainLoop();

    return 0;
}
