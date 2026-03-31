// gcc bonecoNeve.c -o bonecoNeve.exe -I"./include" -L"./bin/x64" -L"./lib-mingw-w64" -lfreeglut -lglu32 -lopengl32

#include <GL/glut.h>

// Variáveis de rotação da cena (controladas pelas teclas de seta)
static GLfloat yRot = 0.0f;   // rotação horizontal (esquerda/direita)
static GLfloat xRot = 0.0f;   // rotação vertical (cima/baixo)


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
    gluPerspective(35.0f,fAspect,1.0,40.0);

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
    yRot = (GLfloat)((const int)yRot % 360);
    xRot = (GLfloat)((const int)xRot % 360);

    // Solicita redesenho da cena
    glutPostRedisplay();
}
GLfloat zDist = 0.0f; 

void Keyboard(unsigned char key, int x, int y) {
    if (key == 'w' || key == 'W') {
        zDist += 1.0f;
    }
    if (key == 's' || key == 'S') {
        zDist -= 1.0f;
    }
    glutPostRedisplay();
}

// ------------------------------------------------------------
// Função principal de renderização
// Desenha todos os objetos da cena
// ------------------------------------------------------------
void RenderScene(void)
{
    // Limpa tela e buffer de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Salva estado atual da matriz
    glPushMatrix();

    // Move a cena para frente da câmera
    glTranslatef(0.0f,-1.0f,-7.0f);

    glTranslatef(0,0,zDist);

    // Aplica rotações controladas pelo teclado
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);


    // ----------------------
    // CHÃO (NEVE)
    // ----------------------

    glColor3f(0.9f,0.9f,0.9f);

    glPushMatrix();
        glTranslatef(0,-0.65,0);   // posiciona abaixo do boneco
        glScalef(6,0.1,6);         // cria um plano largo
        glutSolidCube(1);
    glPopMatrix();


    // ----------------------
    // CORPO DO BONECO
    // 3 esferas empilhadas
    // ----------------------

    glColor3f(1.0f,1.0f,1.0f);

    // esfera inferior
    glPushMatrix();
        glutSolidSphere(0.6f,30,30);
    glPopMatrix();

    // esfera do meio
    glPushMatrix();
        glTranslatef(0.0f,0.8f,0.0f);
        glutSolidSphere(0.45f,30,30);
    glPopMatrix();

    // cabeça
    glPushMatrix();
        glTranslatef(0.0f,1.4f,0.0f);
        glutSolidSphere(0.3f,30,30);
    glPopMatrix();


    // ----------------------
    // NARIZ (CENOURA)
    // ----------------------

    glColor3f(1.0f,0.5f,0.0f);

    glPushMatrix();
        glTranslatef(0.0f,1.4f,0.3f);
        glutSolidCone(0.05f,0.3f,20,20);
    glPopMatrix();


    // ----------------------
    // OLHOS
    // ----------------------

    glColor3f(0.0f,0.0f,0.0f);

    glPushMatrix();
        glTranslatef(-0.1f,1.5f,0.25f);
        glutSolidSphere(0.03f,20,20);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.1f,1.5f,0.25f);
        glutSolidSphere(0.03f,20,20);
    glPopMatrix();


    // ----------------------
    // BOCA (várias pequenas esferas)
    // ----------------------

    for(int i=-2;i<=2;i++)
    {
        glPushMatrix();
            glTranslatef(i*0.05f, 1.30f + (i*i*0.01f), 0.27f);
            glutSolidSphere(0.02f,10,10);
        glPopMatrix();
    }


    // ----------------------
    // BOTÕES DO CORPO
    // ----------------------

    glColor3f(0.4f, 0.0f, 0.4f);

    for(int i=0;i<3;i++)
    {
        glPushMatrix();
            glTranslatef(0.0f,1.0f-(i*0.20f),0.46f);
            glutSolidSphere(0.05f,20,20);
        glPopMatrix();
    }


    // ----------------------
    // BRAÇOS (galhos)
    // ----------------------
    glColor3f(0.2f,0.1f,0.0f); // marrom escuro

    glLineWidth(3);

    glBegin(GL_LINES);

    // braço principal
    glVertex3f(-0.35f,0.95f,0.0f);
    glVertex3f(-0.8f,1.05f,0.0f);

    // galho 1
    glVertex3f(-0.7f,1.02f,0.0f);
    glVertex3f(-0.75f,1.15f,0.0f);

    // galho 2
    glVertex3f(-0.7f,1.02f,0.0f);
    glVertex3f(-0.75f,0.9f,0.0f);

    glEnd();

    glBegin(GL_LINES);

    // braço principal
    glVertex3f(0.35f,0.95f,0.0f);
    glVertex3f(0.8f,1.05f,0.0f);

    // galho 1
    glVertex3f(0.7f,1.02f,0.0f);
    glVertex3f(0.75f,1.15f,0.0f);

    // galho 2
    glVertex3f(0.7f,1.02f,0.0f);
    glVertex3f(0.75f,0.9f,0.0f);

    glEnd();

    /// início chapéu
    GLUquadricObj *pObj = gluNewQuadric(); 
    glColor3f(0.0f, 0.0f, 0.0f); // Preto

    glPushMatrix();
        glTranslatef(0.0f, 1.65f, 0.0f); // Subindo para o topo da cabeça
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotaciona para o chapéu ficar "em pé"

        glDisable(GL_CULL_FACE); //para poder ver a aba 
        //aba
        gluDisk(pObj, 0.0f, 0.38f, 26, 13);   // O raio externo (0.5) deve ser maior que o do cilindro (0.25)
        //tubo
        gluCylinder(pObj, 0.2f, 0.2f, 0.4f, 26, 13); 
        //topo
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.4f); // Sobe até o topo do cilindro
            gluDisk(pObj, 0.0f, 0.2f, 26, 13);
        glPopMatrix();
    glPopMatrix();

        //faixa chapeu
        glColor3f(1.0f, 0.0f, 0.0f); //vermelho

    glPushMatrix();
        glTranslatef(0.0f, 1.65f, 0.0f); // Subindo para o topo da cabeça
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotaciona para o chapéu ficar "em pé"
        //pescoço
        gluCylinder(pObj, 0.21f, 0.21f, 0.1f, 26, 13);
    glPopMatrix();
        // --- REATIVE O CULLING ---
        glEnable(GL_CULL_FACE);

  
    gluDeleteQuadric(pObj);
    // fim do chapéu

    //início cachecol
    GLUquadricObj *ppObj = gluNewQuadric();
    glColor3f(1.0f, 0.0f, 0.0f); //vermelho

    glPushMatrix();
        glTranslatef(0.0f, 1.05f, 0.0f); // Subindo para o topo da cabeça
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotaciona para o chapéu ficar "em pé"
        //pescoço
        gluCylinder(pObj, 0.25f, 0.25f, 0.25f, 26, 13);

    glPopMatrix();
    gluDeleteQuadric(pObj);



    // Restaura matriz original
    glPopMatrix();

    // Troca buffers (double buffering)
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

    glutCreateWindow("Boneco de Neve - OpenGL");

    // registra funções de callback
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    glutKeyboardFunc(Keyboard);

    // configura iluminação e estado inicial
    SetupRC();

    // inicia loop principal do GLUT
    glutMainLoop();

    return 0;
}
