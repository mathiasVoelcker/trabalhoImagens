#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings
#include<math.h>
#ifdef WIN32
#include <windows.h>    // Apenas para Windows
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>     // Funções da OpenGL
#include <GL/glu.h>    // Funções da GLU
#include <GL/glut.h>   // Funções da FreeGLUT
#endif

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

// Um pixel RGB (24 bits)
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem RGB
typedef struct {
    int width, height;
    RGB* img;
} Img;

// Protótipos
void load(char* name, Img* pic);
void valida();

// Funções da interface gráfica e OpenGL
void init();
void draw();
void keyboard(unsigned char key, int x, int y);

// Largura e altura da janela
int width, height;

// Identificadores de textura
GLuint tex[3];

// As 3 imagens
Img pic[3];

// Imagem selecionada (0,1,2)
int sel;

// Carrega uma imagem para a struct Img
void load(char* name, Img* pic)
{
    int chan;
    pic->img = (RGB*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

int main(int argc, char** argv)
{
    if(argc < 2) {
        printf("transition [origem] [destino]\n");
        printf("Origem e' a fonte das cores, destino e' a imagem desejada\n");
        exit(1);
    }
	glutInit(&argc,argv);

	// Define do modo de operacao da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// pic[0] -> imagem com as cores
	// pic[1] -> imagem desejada
	// pic[2] -> resultado do algoritmo

	// Carrega as duas imagens
    load(argv[1], &pic[0]);
    load(argv[2], &pic[1]);

    // A largura e altura da janela são calculadas de acordo com a maior
    // dimensão de cada imagem
    width = pic[0].width > pic[1].width ? pic[0].width : pic[1].width;
    height = pic[0].height > pic[1].height ? pic[0].height : pic[1].height;

    // A largura e altura da imagem de saída são iguais às da imagem desejada (1)
    pic[2].width  = pic[1].width;
    pic[2].height = pic[1].height;

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(width, height);

	// Cria a janela passando como argumento o titulo da mesma
	glutCreateWindow("Quebra-Cabeca digital");

	// Registra a funcao callback de redesenho da janela de visualizacao
	glutDisplayFunc(draw);

	// Registra a funcao callback para tratamento das teclas ASCII
	glutKeyboardFunc (keyboard);

	// Cria texturas em memória a partir dos pixels das imagens
    tex[0] = SOIL_create_OGL_texture((unsigned char*) pic[0].img, pic[0].width, pic[0].height, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
    tex[1] = SOIL_create_OGL_texture((unsigned char*) pic[1].img, pic[1].width, pic[1].height, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

    // Exibe as dimensões na tela, para conferência
    printf("Origem  : %s %d x %d\n", argv[1], pic[0].width, pic[0].height);
    printf("Destino : %s %d x %d\n", argv[2], pic[1].width, pic[0].height);
    sel = 0; // pic1

	// Define a janela de visualizacao 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,width,height,0.0);
	glMatrixMode(GL_MODELVIEW);

	// Aplica o algoritmo e gera a saida em pic[2].img...
	// ...
	// ...
// Comente a linha abaixo para testar o seu algoritmo
// (Caso contrário, o programa tenta ler o resultado como um TERCEIRO parâmetro)
//#define DEMO
//#ifdef DEMO


	load(argv[3], &pic[2]);
    //createPic2(&pic[0], &pic[1], &pic[2]);
    int size = pic[1].width*pic[1].height;
    int length;
    printf("size: %i\n", size);
    for(int i = 0; i < size; i++){//cria pic[2] (imagem da resposta) para ser uma imagem toda vermelha, para testarmos
       pic[2].img[i].r = 'f';
       pic[2].img[i].b = '0';
       pic[2].img[i].g = '0';
    }
    RGB pixelsFirstPic[size];

    for(int i = 0; i < size; i++)//cria um vetor com todos os pixels da pic[0], esses pixels iram compor a pic[2]
        pixelsFirstPic[i] = pic[0].img[i];
    }
    int dist;
    int aux;
    for(int n = 0; n < 1000; n++){//itera por cada pixel da imagem, para que seja atribuido um pixel por vez em pic[2]. O correto eh n < size, mas a execucao demora muito tempo, entao para testes fica melhor n < 1000
        dist = 10000; //valor inicial da distancia, deve ser qualquer valor grande que garanta a atribuicao de valor no primeira iteracao do for abaixo
        for(int i = 0; i < size; i++){ //encontra a cor dentro de pixelsFirstPic mais proxima de pic[1].img[n]
            if(dist > distanciaPixels(&pixelsFirstPic[i], &pic[1].img[n])){
                dist = distanciaPixels(&pixelsFirstPic[i], &pic[1].img[n]);
                aux = i;You must add an explicit argument:


            }
        }
        pic[2].img[n] = pixelsFirstPic[aux]; //atribui cor mais proxima a pic[2]

        /*length = sizeof(pixelsFirstPic);
        for(int j = aux; j < length; j++){ remove a cor de pixelsFirstPic, nao esta funcionando, acredito que o sizeof nao seja o ideal para conseguir tamanho de vetor
            pixelsFirstPic[j] = pixelsFirstPic[j+1];
        }*/
        // eh importante remover a cor de pixelFirstPic, para que o mesmo pixel de pic[0] nao seja atribuido mais de uma vez em pic[2]


        //acredito que, da forma que esta, o algoritmo ja cria uma terceira imagem muito parecida com a segunda imagem, o que falta eh fazer com que cada pixel da imagem 1 soh seja utilizado uma vez. Fora isso, talvez soh questao de eficiencia do algoritmo.
    }

//#else
    // Para valer, só aloca memória para a imagem de saída
//	pic[2].img = malloc(pic[1].width * pic[1].height * 3); // W x H x 3 bytes (RGB)
//#endif // DEMO

    // Cria textura para a imagem de saída
	tex[2] = SOIL_create_OGL_texture((unsigned char*) pic[2].img, pic[2].width, pic[2].height, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

	// Entra no loop de eventos, não retorna
    glutMainLoop();
}
/*
void createPic2(Img* img1, Img* img2, Img* img3){
    int size = pic[1].width*pic[1].height;
    int dist = 10000;
    int aux;
    for(int i = 0; i < 8; i++){
       if(dist > distanciaPixels(&img1[i], &img2[0])){
            dist = distanciaPixels(&img1[i], &img2[0]);
            aux = i;
        }
        img3.img[i] = img1.img[i];
    }
}*/

int distanciaPixels(const void* img1, const void* img2){ //retorna distancia entre 2 cores, acredito que esta funcionando perfeitamente
    RGB* ptr1 = (RGB*) img1;
    RGB* ptr2 = (RGB*) img2;
    int r1 = ptr1->r;
    int r2 = ptr2->r;
    int g1 = ptr1->g;
    int g2 = ptr2->g;
    int b1 = ptr1->b;
    int b2 = ptr2->b;
    int rSquare = (r1 - r2)*(r1 - r2);
    int gSquare = (g1 - g2)*(g1 - g2);
    int bSquare = (b1 - b2)*(b1 - b2);
    //printf("diferenca %i\n", sqrt(rSquare + gSquare + bSquare));
    return sqrt(rSquare + gSquare + bSquare);
}
// Funcao de comparacao para qsort: ordena por R, G, B (desempate nessa ordem)
int cmp(const void* elem1, const void* elem2)
{
    RGB* ptr1 = (RGB*) elem1;
    RGB* ptr2 = (RGB*) elem2;
    unsigned char r1 = ptr1->r;
    unsigned char r2 = ptr2->r;
    unsigned char g1 = ptr1->g;
    unsigned char g2 = ptr2->g;
    unsigned char b1 = ptr1->b;
    unsigned char b2 = ptr2->b;
    int r = 0;
    if(r1 < r2) r = -1;
    else if(r1 > r2) r = 1;
    else if(g1 < g2) r = -1;
    else if(g1 > g2) r = 1;
    else if(b1 < b2) r = -1;
    else if(b1 > b2) r = 1;
    return r;
}

// Verifica se o algoritmo foi aplicado corretamente:
// Ordena os pixels da imagem origem e de saída por R, G e B;
// depois compara uma com a outra: devem ser iguais
void valida()
{
    int ok = 1;
    int size = width * height;
    // Aloca memória para os dois arrays
    RGB* aux1 = malloc(size*3);
    RGB* aux2 = malloc(size*3);
    // Copia os pixels originais
    memcpy(aux1, pic[0].img, size*3);
    memcpy(aux2, pic[2].img, size*3);
    // Mostra primeiros 8 pixels de ambas as imagens
    // antes de ordenar (teste)
    for(int i=0; i<8; i++)
        printf("[%02X %02X %02X] ", aux1[i].r, aux1[i].g, aux1[i].b);
    printf("\n");
    for(int i=0; i<8; i++)
        printf("[%02X %02X %02X] ", aux2[i].r, aux2[i].g, aux2[i].b);
    printf("\n");
    printf("Validando...\n");
    // Ordena ambos os arrays
    qsort(aux1, size, sizeof(RGB), cmp);
    qsort(aux2, size, sizeof(RGB), cmp);
    // Mostra primeiros 8 pixels de ambas as imagens
    // depois de ordenar
    for(int i=0; i<8; i++)
        printf("[%02X %02X %02X] ", aux1[i].r, aux1[i].g, aux1[i].b);
    printf("\n");
    for(int i=0; i<8; i++)
        printf("[%02X %02X %02X] ", aux2[i].r, aux2[i].g, aux2[i].b);
    printf("\n");
    for(int i=0; i<size; i++) {
        if(aux1[i].r != aux2[i].r ||
           aux1[i].g != aux2[i].g ||
           aux1[i].b != aux2[i].b) {
            // Se pelo menos um dos pixels for diferente, o algoritmo foi aplicado incorretamente
            printf("*** INVALIDO na posicao %d ***: %02X %02X %02X -> %02X %02X %02X\n",
                    i, aux1[i].r, aux1[i].g, aux1[i].b, aux2[i].r, aux2[i].g, aux2[i].b);
            ok = 0;
            break;
        }
    }
    // Libera memória dos arrays ordenados
    free(aux1);
    free(aux2);
    if(ok)
        printf(">>>> TRANSFORMACAO VALIDA <<<<<\n");
}

// Gerencia eventos de teclado
void keyboard(unsigned char key, int x, int y)
{
    if(key==27) {
      // ESC: libera memória e finaliza
      free(pic[0].img);
      free(pic[1].img);
      free(pic[2].img);
      exit(1);
    }
    if(key >= '1' && key <= '3')
        // 1-3: seleciona a imagem correspondente (origem, destino e resultado)
        sel = key - '1';
    // V para validar a solução
    if(key == 'v')
        valida();
    glutPostRedisplay();
}

// Callback de redesenho da tela
void draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Preto
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // Para outras cores, veja exemplos em /etc/X11/rgb.txt

    glColor3ub(255, 255, 255);  // branco

    // Ativa a textura corresponde à imagem desejada
    glBindTexture(GL_TEXTURE_2D, tex[sel]);
    // E desenha um retângulo que ocupa toda a tela
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    glTexCoord2f(0,0);
    glVertex2f(0,0);

    glTexCoord2f(1,0);
    glVertex2f(pic[sel].width,0);

    glTexCoord2f(1,1);
    glVertex2f(pic[sel].width, pic[sel].height);

    glTexCoord2f(0,1);
    glVertex2f(0,pic[sel].height);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Exibe a imagem
    glutSwapBuffers();
}
