// gcc bonecoNeve.c -o bonecoNeve.exe -I"./include" -L"./bin/x64" -L"./lib-mingw-w64" -lfreeglut -lglu32 -lopengl32

#include <GL/glut.h>
#include <stdio.h>

// Variáveis de rotação da cena (controladas pelas teclas de seta)
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
// Função que trata teclas especiais (setas do teclado)
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


    //xRot = (GLfloat)((const int)xRot % 360);
    //zRot = (GLfloat)((const int)zRot % 360);

    // Solicita redesenho da cena
    glutPostRedisplay();
}

// No topo do programa, junto com as outras variáveis
GLfloat zDist = -50.0f; 

// Crie esta nova função
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
    // Limpa a tela e o buffer de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, zDist);
    gluLookAt(10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
  
    glRotatef(yRot, 0.0f, 1.0f, 0.0f); 
    glRotatef(xRot, 1.0f, 0.0f, 0.0f); 

    // Criar o objeto quádrico
    GLUquadricObj *pObj = gluNewQuadric();
    gluQuadricDrawStyle(pObj, GLU_FILL); // Pode usar GLU_LINE para ver o wireframe

    // --- DESENHANDO UMA TORRE (Cilindro + Cone) ---
    
    // Base da Torre 1 (Cilindro)
    glPushMatrix();
        glColor3f(0.7f, 0.7f, 0.7f); // Cinza claro
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotaciona para ficar em pé no eixo Y
        // gluCylinder(objeto, raio_base, raio_topo, altura, fatias, pilhas)
        gluCylinder(pObj, 1.0, 1.0, 4.0, 32, 32); 
    glPopMatrix();

    // Telhado da Torre 1 (Cone)
    glPushMatrix();
        glColor3f(0.5f, 0.2f, 0.0f); // Marrom/Laranja
        glTranslatef(0.0f, 4.0f, 0.0f); // Move para o topo do cilindro
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        // Um cone é um cilindro com raio de topo igual a zero
        gluCylinder(pObj, 1.3, 0.0, 1.5, 32, 32); 
    glPopMatrix();
    
    //Torre 2
    glPushMatrix();
        glColor3f(0.7f, 0.7f, 0.7f); // Cinza claro
        glTranslatef(6.0f, 0.0f, 0.0f); // Move para o topo do cilindro
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotaciona para ficar em pé no eixo Y
        // gluCylinder(objeto, raio_base, raio_topo, altura, fatias, pilhas)
        gluCylinder(pObj, 1.0, 1.0, 4.0, 32, 32); 
    glPopMatrix();

    //Telhado 2
    glPushMatrix();
        glColor3f(0.5f, 0.2f, 0.0f); // Marrom/Laranja
        glTranslatef(6.0f, 4.0f, 0.0f); // Move para o topo do cilindro
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        // Um cone é um cilindro com raio de topo igual a zero
        gluCylinder(pObj, 1.3, 0.0, 1.5, 32, 32); 
    glPopMatrix();

     //Torre 3
    glPushMatrix();
        glColor3f(0.7f, 0.7f, 0.7f); // Cinza claro
        glTranslatef(0.0f, 0.0f, -6.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotaciona para ficar em pé no eixo Y
        // gluCylinder(objeto, raio_base, raio_topo, altura, fatias, pilhas)
        gluCylinder(pObj, 1.0, 1.0, 4.0, 32, 32); 
    glPopMatrix();

    // Telhado 3
    glPushMatrix();
        glColor3f(0.5f, 0.2f, 0.0f); // Marrom/Laranja
        glTranslatef(0.0f, 4.0f, -6.0f); // Move para o topo do cilindro
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        // Um cone é um cilindro com raio de topo igual a zero
        gluCylinder(pObj, 1.3, 0.0, 1.5, 32, 32); 
    glPopMatrix();

    //Torre 4
    glPushMatrix();
        glColor3f(0.7f, 0.7f, 0.7f); // Cinza claro
        glTranslatef(6.0f, 0.0f, -6.0f); // Move para o topo do cilindro
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotaciona para ficar em pé no eixo Y
        // gluCylinder(objeto, raio_base, raio_topo, altura, fatias, pilhas)
        gluCylinder(pObj, 1.0, 1.0, 4.0, 32, 32); 
    glPopMatrix();

    //Telhado 4
    glPushMatrix();
        glColor3f(0.5f, 0.2f, 0.0f); // Marrom/Laranja
        glTranslatef(6.0f, 4.0f, -6.0f); // Move para o topo do cilindro
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        // Um cone é um cilindro com raio de topo igual a zero
        gluCylinder(pObj, 1.3, 0.0, 1.5, 32, 32); 
    glPopMatrix();
    


    // --- DESENHANDO AS MURALHAS (Cubos esticados) ---
    // Como muros não são quádricas nativas da GLU, usamos as formas da GLUT

    //Muro 1
      glPushMatrix();
        glColor3f(0.6f, 0.6f, 0.6f);
        glTranslatef(3.0f, 1.5f, 0.0f); // Posiciona entre as torres
        glScalef(4.0f, 2.0f, 0.5f);     // Estica para parecer um muro
        glutSolidCube(1.5f);
    glPopMatrix();


    //Muro 3
      glPushMatrix();
        glColor3f(0.6f, 0.6f, 0.6f);
        glTranslatef(3.0f, 1.5f, -6.0f); // Posiciona entre as torres
        glScalef(4.0f, 2.0f, 0.5f);     // Estica para parecer um muro
        glutSolidCube(1.5f);
    glPopMatrix();
    

    //Muro 2
    glPushMatrix();
        glColor3f(0.6f, 0.6f, 0.6f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(3.0f, 1.5f, 0.0f); // Posiciona entre as torres
        glScalef(4.0f, 2.0f, 0.5f);     // Estica para parecer um muro
        glutSolidCube(1.5f);
    glPopMatrix();

    //Muro 4
    glPushMatrix();
        glColor3f(0.6f, 0.6f, 0.6f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(3.0f, 1.5f, 6.0f); // Posiciona entre as torres
        glScalef(4.0f, 2.0f, 0.5f);     // Estica para parecer um muro
        glutSolidCube(1.5f);
    glPopMatrix();

// Janela 1
glColor3f(0.0f, 0.0f, 0.0f); // Preto
glPushMatrix();
    glTranslatef(2.0f, 1.5f, 0.4f); // 0.51f para ficar "na pele" da parede
    glScalef(1.0f, 1.0f, 0.1f);      // Bem fino
    glutSolidCube(1.0f);
glPopMatrix();

// Janela 2
glColor3f(0.0f, 0.0f, 0.0f); // Preto
glPushMatrix();
    glTranslatef(4.0f, 1.5f, 0.4f); // 0.51f para ficar "na pele" da parede
    glScalef(1.0f, 1.0f, 0.1f);      // Bem fino
    glutSolidCube(1.0f);
glPopMatrix();

// Janela 
glColor3f(0.0f, 0.0f, 0.0f); // Preto
glPushMatrix();
    glTranslatef(6.4f, 1.5f, -2.0f); // 0.51f para ficar "na pele" da parede
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(1.0f, 1.0f, 0.1f);      // Bem fino
    glutSolidCube(1.0f);
glPopMatrix();

// Janela 
glColor3f(0.0f, 0.0f, 0.0f); // Preto
glPushMatrix();
glTranslatef(6.4f, 1.5f, -4.0f); // 0.51f para ficar "na pele" da parede
glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(1.0f, 1.0f, 0.1f);      // Bem fino
    glutSolidCube(1.0f);
glPopMatrix();

// Janela 3
glColor3f(0.0f, 0.0f, 0.0f); // Preto
glPushMatrix();
    glTranslatef(2.0f, 1.5f, -6.4f); 
    glScalef(1.0f, 1.0f, 0.1f);      // Bem fino
    glutSolidCube(1.0f);
glPopMatrix();

// Janela 4
glColor3f(0.0f, 0.0f, 0.0f); // Preto
glPushMatrix();
    glTranslatef(4.0f, 1.5f, -6.4f); 
    glScalef(1.0f, 1.0f, 0.1f);      // Bem fino
    glutSolidCube(1.0f);
glPopMatrix();

//------PORTA---------

    // Limpeza
    gluDeleteQuadric(pObj);
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

    glutCreateWindow("Castelinho- OpenGL");

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