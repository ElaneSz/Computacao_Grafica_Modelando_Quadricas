## Computação Gráfica - Projetos 3D com OpenGL & GLUT

Este repositório contém uma coleção de modelos 3D desenvolvidos em **C** utilizando as bibliotecas **OpenGL** e **GLUT**. Os projetos exploram conceitos fundamentais de computação gráfica, como transformações geométricas (translação, rotação, escala), iluminação, teste de profundidade e renderização de primitivas.

## 🚀 Projetos Incluídos

### 1. Boneco de Neve (`bonecoNeve.c`)
Um modelo detalhado composto por esferas empilhadas, incluindo:
* **Corpo:** Três esferas brancas proporcionais.
* **Acessórios:** Cartola com faixa roxa, cachecol e nariz de cenoura (cone).
* **Detalhes:** Botões, olhos e braços feitos com linhas (`GL_LINES`).

### 2. Castelo Medieval (`castelo.c`)
Uma cena complexa que simula uma fortaleza, contendo:
* **Estrutura:** Muros fortificados e quatro torres cilíndricas com telhados cônicos.
* **Decoração:** Mastros com bandeiras vermelhas e detalhes de janelas.
* **Cenário:** Plano de fundo representando gramado e árvores geradas proceduralmente.

### 3. Robô Articulado (`robo.c`)
Um modelo humanoide focado em hierarquia de objetos e proporções:
* **Membros:** Braços, antebraços, coxas e pernas construídos com retângulos e esferas para representar articulações (ombros, joelhos, cotovelos).
* **Design:** Estética em tons de roxo e branco com foco em simetria.

---

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C
* **Graphics API:** OpenGL
* **Utility Toolkit:** GLUT (FreeGLUT)
* **Projeção:** Perspectiva (`gluPerspective`)

---

## 🎮 Controles

As janelas de visualização permitem interação com o usuário:

* **Setas do Teclado:** Rotacionam a cena nos eixos X e Y.
* **Teclas `W` / `S`:** Aproximam ou afastam a câmera (Zoom In/Out) - *Disponível nos arquivos Castelo e Robô*.

---

## ⚙️ Como Compilar e Executar

Para compilar os arquivos utilizando o **GCC** no Windows (MinGW), utilize o comando abaixo (exemplo para o robô):

```bash
gcc robo.c -o robo.exe -I"./include" -L"./bin/x64" -L"./lib-mingw-w64" -lfreeglut -lglu32 -lopengl32
