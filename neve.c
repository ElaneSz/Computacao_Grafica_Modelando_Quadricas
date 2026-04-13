// Compilar com: gcc neve.c -lglut -lGL -lGLU -lm -o neve && ./neve

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define MAX_PARTICULAS 3500

typedef struct {
    float x, y, z;
    float velocidade;
    float flutter_speed; 
    float brilho;
} Particula;

Particula particulas[MAX_PARTICULAS];
static GLfloat yRot = 0.0f;
static GLfloat xRot = 0.0f;
static GLfloat zDist = 0.0f;

// --- Sistema de Neve ---

void inicializarParticula(int i) {
    particulas[i].x = (float)(rand() % 400 - 200) / 10.0f;
    particulas[i].y = (float)(rand() % 150) / 10.0f; 
    particulas[i].z = (float)(rand() % 400 - 300) / 10.0f;
    particulas[i].velocidade = (float)(rand() % 15 + 5) / 1000.0f;
    particulas[i].flutter_speed = (float)(rand() % 100) / 40.0f;
    particulas[i].brilho = (float)(rand() % 40 + 60) / 100.0f;
}

void inicializarNeve() {
    srand(time(NULL));
    for (int i = 0; i < MAX_PARTICULAS; i++) inicializarParticula(i);
}

void atualizarNeve() {
    for (int i = 0; i < MAX_PARTICULAS; i++) {
        particulas[i].y -= particulas[i].velocidade;
        particulas[i].x += sin(particulas[i].y * particulas[i].flutter_speed) * 0.003f;
        if (particulas[i].y < -1.0f) particulas[i].y = 12.0f;
    }
    glutPostRedisplay();
}

// --- Elementos do Cenário ---

void desenharArvore(float x, float z) {
    GLUquadricObj *pObj = gluNewQuadric();
    glPushMatrix();
        glTranslatef(x, -0.7f, z);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.3f, 0.15f, 0.05f);
        gluCylinder(pObj, 0.25f, 0.2f, 0.6f, 12, 1);
        glColor3f(0.0f, 0.25f, 0.05f);
        glTranslatef(0.0f, 0.0f, 0.4f);
        glutSolidCone(0.9f, 1.3f, 12, 8);
        glTranslatef(0.0f, 0.0f, 0.7f);
        glutSolidCone(0.7f, 1.1f, 12, 8);
    glPopMatrix();
    gluDeleteQuadric(pObj);
}

void desenharBoneco() {
    GLUquadricObj *pObj = gluNewQuadric();
    
    // 1. Corpo (Esferas)
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(0.6f, 30, 30); // Base
    
    glPushMatrix();
        glTranslatef(0.0f, 0.8f, 0.0f);
        glutSolidSphere(0.45f, 30, 30); // Meio
        
        // 2. Botões (Roxo)
        glColor3f(0.4f, 0.0f, 0.4f);
        for(int i=0; i<3; i++) {
            glPushMatrix();
                glTranslatef(0.0f, 0.2f - (i*0.2f), 0.42f);
                glutSolidSphere(0.05f, 10, 10);
            glPopMatrix();
        }

        glPushMatrix();
            glTranslatef(0.0f, 0.6f, 0.0f);
            glColor3f(1.0f, 1.0f, 1.0f);
            glutSolidSphere(0.3f, 30, 30); // Cabeça
            
            // 3. Olhos e Sorriso (Preto)
            glColor3f(0.0f, 0.0f, 0.0f);
            // Olhos
            glPushMatrix();
                glTranslatef(-0.12f, 0.1f, 0.25f);
                glutSolidSphere(0.03f, 10, 10);
                glTranslatef(0.24f, 0.0f, 0.0f);
                glutSolidSphere(0.03f, 10, 10);
            glPopMatrix();
            // Sorriso
            for(int i=-2; i<=2; i++) {
                glPushMatrix();
                    glTranslatef(i*0.06f, -0.1f + (i*i*0.015f), 0.28f);
                    glutSolidSphere(0.02f, 10, 10);
                glPopMatrix();
            }

            // 4. Nariz (Cenoura)
            glColor3f(1.0f, 0.5f, 0.0f);
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, 0.3f);
                glutSolidCone(0.05f, 0.3f, 20, 20);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    // 5. Cachecol (Vermelho)
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
        glTranslatef(0.0f, 1.05f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.27f, 0.27f, 0.2f, 26, 1);
    glPopMatrix();

    // 6. Chapéu (Preto)
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
        glTranslatef(0.0f, 1.65f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluDisk(pObj, 0.0f, 0.45f, 26, 1); // Aba
        gluCylinder(pObj, 0.25f, 0.25f, 0.4f, 26, 1); // Topo
        glPopMatrix();
        
        gluDeleteQuadric(pObj);
    }
    
    void RenderScene(void) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // Câmera e Navegação
        glTranslatef(0.0f, 0.1f, -10.0 + zDist);
        glRotatef(xRot, 1.0f, 0.0f, 0.0f);
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        
        // 3. Boneco de Neve
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, -4.0f);
            desenharBoneco();
        glPopMatrix();

    // ----------------------
    // CHÃO (NEVE)
    // ----------------------

    glColor3f(0.9f,0.9f,0.9f);

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
        glTranslatef(0,-0.65,-5.0);   // posiciona abaixo do boneco
        glScalef(50,0.1,50);         // cria um plano largo
        glutSolidCube(1);
        glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    // 2. Floresta
    srand(1234);
    for(int i=0; i<60; i++) {
        float tx = (rand() % 160) - 80;
        float tz = (rand() % 160) - 100;
        if(abs(tx) > 4 || abs(tz + 4) > 4) desenharArvore(tx, tz);
    }


    // 4. Neve Caindo
    // Point Sprites Config
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLfloat atten[] = {0.0f, 0.0f, 0.01f};
    //glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, atten); // Verificar no linux
    glPointSize(5.0f);
    
    glBegin(GL_POINTS);
    for (int i = 0; i < MAX_PARTICULAS; i++) {
        glColor4f(particulas[i].brilho, particulas[i].brilho, particulas[i].brilho, 0.8f);
        glVertex3f(particulas[i].x, particulas[i].y, particulas[i].z);
    }
    glEnd();
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}

// --- Configurações Iniciais ---

void SetupRC() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    glClearColor(0.5f, 0.6f, 0.8f, 1.0f); // Azul céu

    // Neblina
    GLfloat fogColor[] = {0.5f, 0.6f, 0.8f, 1.0f};
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.03f);
    glFogi(GL_FOG_MODE, GL_EXP2);

    GLfloat lightPos[] = { -10.0f, 10.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void ChangeSize(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35.0f, (GLfloat)w/(GLfloat)h, 1.0, 2000.0); // Far plane aumentado para o chão
    glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y) {
    if (key == 'w' || key == 'W') zDist += 0.5f;
    if (key == 's' || key == 'S') zDist -= 0.5f;
    if (key == 27) exit(0);
    glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) yRot -= 5.0f;
    if (key == GLUT_KEY_RIGHT) yRot += 5.0f;
    if (key == GLUT_KEY_UP) xRot -= 5.0f;
    if (key == GLUT_KEY_DOWN) xRot += 5.0f;

    // Mantém os valores dentro de 0–360 graus
    if (yRot > 360.0f) yRot -= 360.0f;
    if (yRot < 0.0f)   yRot += 360.0f;

    if (xRot > 360.0f) xRot -= 360.0f;
    if (xRot < 0.0f)   xRot += 360.0f;

    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Boneco de Neve - UDESC CCT");
    
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(RenderScene);
    glutIdleFunc(atualizarNeve);
    
    SetupRC();
    inicializarNeve();
    
    glutMainLoop();
    return 0;
}