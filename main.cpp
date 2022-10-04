#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

GLint b = 300;
float counter = 600.0;

GLfloat distance = 50;
GLfloat azimuth = 0;
GLfloat incidence = 0;
GLfloat twist = 0;
GLfloat angle, fAspect;

GLfloat rotX, rotY, rotX_ini, rotY_ini;

GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;

int x_ini, y_ini, bot;

void polarView()
{
	glTranslatef(0.0, 0.0, -distance);
	glRotatef(-twist, 0.0, 0.0, 1.0);
	glRotatef(-incidence, 1.0, 0.0, 0.0);
	glRotatef(-azimuth, 0.0, 0.0, 1.0);
}

void DefineIluminacao(void)

{

	GLfloat luzAmbiente[4] = {0.2, 0.2, 0.2, 1.0};

	GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0}; // "cor"

	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"

	GLfloat posicaoLuz[4] = {0.0, 500.0, 50.0, 1.0};

	// Capacidade de brilho do material

	GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};

	GLint especMaterial = 60;

	// Define a refletância do material

	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);

	// Define a concentração do brilho

	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);

	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}

void PosicionaObservador(void)

{

	// Especifica sistema de coordenadas do modelo

	glMatrixMode(GL_MODELVIEW);

	// Inicializa sistema de coordenadas do modelo

	glLoadIdentity();

	DefineIluminacao();

	// Posiciona e orienta o observador

	glTranslatef(-obsX, -obsY, -obsZ);

	glRotatef(rotX, 1, 0, 0);

	glRotatef(rotY, 0, 1, 0);
}

// Função usada para especificar o volume de visualização

void EspecificaParametrosVisualizacao(void)

{

	// Especifica sistema de coordenadas de projeção

	glMatrixMode(GL_PROJECTION);

	// Inicializa sistema de coordenadas de projeção

	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)

	gluPerspective(angle, fAspect, 0.5, 500);

	PosicionaObservador();
}

// Função callback para tratar eventos de teclas especiais

void TeclasEspeciais(int tecla, int x, int y)

{

	switch (tecla)

	{

	case GLUT_KEY_HOME:
		if (angle >= 10)
			angle -= 5;

		break;

	case GLUT_KEY_END:
		if (angle <= 150)
			angle += 5;

		break;
	}

	EspecificaParametrosVisualizacao();

	glutPostRedisplay();
}

// Função callback para eventos de botões do mouse

void GerenciaMouse(int button, int state, int x, int y)

{

	if (state == GLUT_DOWN)

	{

		// Salva os parâmetros atuais

		x_ini = x;

		y_ini = y;

		obsX_ini = obsX;

		obsY_ini = obsY;

		obsZ_ini = obsZ;

		rotX_ini = rotX;

		rotY_ini = rotY;

		bot = button;
	}

	else
		bot = -1;
}

// Função callback para eventos de movimento do mouse

#define SENS_ROT 5.0

#define SENS_OBS 10.0

#define SENS_TRANSL 10.0

void GerenciaMovim(int x, int y)

{

	// Botão esquerdo ?

	if (bot == GLUT_LEFT_BUTTON)

	{

		// Calcula diferenças

		int deltax = x_ini - x;

		int deltay = y_ini - y;

		// E modifica ângulos

		rotY = rotY_ini - deltax / SENS_ROT;

		rotX = rotX_ini - deltay / SENS_ROT;
	}

	// Botão direito ?

	else if (bot == GLUT_RIGHT_BUTTON)

	{

		// Calcula diferença

		int deltaz = y_ini - y;

		// E modifica distância do observador

		obsZ = obsZ_ini + deltaz / SENS_OBS;
	}

	// Botão do meio ?

	else if (bot == GLUT_MIDDLE_BUTTON)

	{

		// Calcula diferenças

		int deltax = x_ini - x;

		int deltay = y_ini - y;

		// E modifica posições

		obsX = obsX_ini + deltax / SENS_TRANSL;

		obsY = obsY_ini - deltay / SENS_TRANSL;
	}

	PosicionaObservador();

	glutPostRedisplay();
}

// Função callback chamada quando o tamanho da janela é alterado

void Reshape(GLsizei w, GLsizei h)

{

	// Para previnir uma divisão por zero

	if (h == 0)
		h = 1;

	// Especifica as dimensões da viewport

	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto

	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

void house(){
	glPushMatrix(); // comeco da casa
		glTranslatef(150, -150, -60); // lado esquerdo
		glColor3d(1, 0, 1);
		glutSolidCube(70);

		glTranslatef(0, -70, 0);
		glColor3d(1, 0, 1); // lado direito
		glutSolidCube(70);

		glTranslatef(-11, 0, -10);
		glColor3d(1, 1, 1); // porta garagem
		glutSolidCube(50);

		glTranslatef(-18, 45, 5);
		glColor3d(0, 0, 0); // janela
		glutSolidCube(15);

		glTranslatef(0, 25, -8);
		glColor3d(0, 0, 0); // porta (cima)
		glutSolidCube(15);

		glTranslatef(0, 0, -15);
		glColor3d(0, 0, 0); // porta (baixo)
		glutSolidCube(15);
	glPopMatrix(); // fim da casa
}

void tree(){

	glPushMatrix(); // comeco da Arvore

		glTranslatef(100, -30, -95); // comeco do tronco
		glRotatef(0, -1, 0, 0);
		glColor3d(0.39, 0.26, 0.13);
		glutSolidCylinder(5, 100, 100, 20); // fim do tronco

		glRotatef(90, 1, 0, 0); // comeco das folhas
		glTranslatef(0, 100, 10);
		glColor3d(0, 1, 0);
		glutSolidSphere(20, 100, 100);
		glTranslatef(0, 0, -20);
		glutSolidSphere(20, 100, 100);
		glTranslatef(10, 0, 10);
		glutSolidSphere(20, 100, 100);
		glTranslatef(-20, 0, 0);
		glutSolidSphere(20, 100, 100);
		glTranslatef(10, 20, 0);
		glutSolidSphere(20, 100, 100); // fim das folhas

	glPopMatrix(); // fim da Arvore

}

void clouds(){
	glScalef(1, 1, 1);
	glTranslatef(0, 50, 0);
	glColor3d(1, 1, 1);
	glutSolidSphere(5, 200, 10);

	glScalef(1, 1, 1);
	glTranslatef(0, 7, 0);
	glColor3d(1, 1, 1);
	glutSolidSphere(5, 200, 10);

	glScalef(1, 1, 1);
	glTranslatef(0, 7, 0);
	glColor3d(1, 1, 1);
	glutSolidSphere(5, 200, 10);

	glScalef(1, 1, 1);
	glTranslatef(0, -7, 7);
	glColor3d(1, 1, 1);
	glutSolidSphere(5, 200, 10);

	// nuvem 2 //

	glScalef(1, 1, 1);
	glTranslatef(100, 50, 0);
	glColor3d(1, 1, 1);
	glutSolidSphere(5, 200, 10);

	glScalef(1, 1, 1);
	glTranslatef(0, 7, 0);
	glColor3d(1, 1, 1);
	glutSolidSphere(5, 200, 10);

	glScalef(1, 1, 1);
	glTranslatef(0, 7, 0);
	glColor3d(1, 1, 1);
	glutSolidSphere(5, 200, 10);

	glScalef(1, 1, 1);
	glTranslatef(0, -7, 7);
	glColor3d(1, 1, 1);
	glutSolidSphere(5, 200, 10);

	// nuvem 3 //

	glScalef(1, 1, 1);
	glTranslatef(-40, 50, 0);
	glColor3d(1, 1, 1);
	glutSolidSphere(5, 200, 10);

	glScalef(1, 1, 1);
	glTranslatef(7, 0, 0);
	glColor3d(1, 1, 1);
	glutSolidSphere(5, 200, 10);

	glScalef(1, 1, 1);
	glTranslatef(7, 0, 0);
	glColor3d(1, 1, 1);
	glutSolidSphere(5, 200, 10);

	glScalef(1, 1, 1);
	glTranslatef(-7, 0, 7);
	glColor3d(1, 1, 1);
	glutSolidSphere(5, 200, 10);
}

void sun(){

	glScalef(1, 1, 1);
	glTranslatef(100, -15, 70);
	glColor3d(1, 1, 0);
	glutSolidSphere(5, 200, 10);

}

void car(){

	glPushMatrix(); // comeco do carro
		glTranslatef(0, 10, -10);
		glColor3d(1, 0, 0); // comeco da cor no meio
		glutSolidCube(30);

		glPushMatrix();			// comeco do carro
			glTranslatef(0, -7, 8); // posição do cubo azul
			glColor3d(0, 0, 1);		// cubo azul
			glutSolidCube(15);
		glPopMatrix();

		// roda esquerda //
		glPushMatrix();	
			glTranslatef(16, -13.5, 0); // posição da roda
			glRotatef(90, 0, 1, 0);
			glColor3d(0, 0, 0);
			glutSolidTorus(2, 5, 100, 100);
		glPopMatrix();

		// roda direita //
		glPushMatrix();	
			glTranslatef(-16, -13.5, -2); // posição da roda
			glRotatef(90, 0, 1, 0);
			glColor3d(0, 0, 0);
			glutSolidTorus(2, 5, 100, 100);
		glPopMatrix();
	
		// comeco da cabine
		glPushMatrix();	
			glTranslatef(0, 7, -35); // posição da cabine?
			glColor3d(0, 0, 1);		  // comeco da cor no meio
			glutSolidCube(45);		  // tamaho da cabine
		glPopMatrix();

		// roda traseira esquerda //
		glPushMatrix();
			glTranslatef(-24, -13.5, -40); // posição da roda 
			glRotatef(90, 0, 1, 0);
			glColor3d(0, 0, 0);
			glutSolidTorus(2, 5, 100, 100);
		glPopMatrix();

		// roda traseira direita //
		glPushMatrix();
			glTranslatef(24, -13.5, -40); // posição da roda
			glRotatef(90, 0, 1, 0); // angulo // altura //
			glColor3d(0, 0, 0);
			glutSolidTorus(2, 5, 100, 100);
		glPopMatrix();
	glPopMatrix();

}

// adicionar as formas a serem mostradas na cena
void display()
{
	const double a = glutGet(GLUT_ELAPSED_TIME) / 10;
	GLfloat yellow[4] = {1, 1, 0, 1};

	/* Limpa todos os pixels da tela */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DefineIluminacao();

	glPushMatrix(); // comeco do chao
		glTranslatef(0, -510, 0);
		glColor3d(0.5, 0.5, 0.5); // cor do chão
		glutSolidCube(1000);
		glPopMatrix(); // fim do chao

	polarView();

	car();

	// poste de luz //
	glPushMatrix();				// comeco do poste
	glTranslatef(-100, -7, 70); // comeco do tronco
	glRotatef(90, -1, 0, 0);
	glColor3d(0.5, 0.5, 0.5);
	glutSolidCylinder(2, 50, 100, 20); // fim do tronco

	// lampada //
	glRotatef(90, 1, 0, 0); // comeco do lugar da lampada
	glTranslatef(2.5, 50, 0);
	glScalef(1.5, 0.333, 1);
	glutSolidCube(5); // fim do lugar da lampada

	glScalef(0.75, 3, 1); // comeco da lampada
	glTranslatef(1.5, -1, 0);
	glColor3d(1, 1, 0);
	glutSolidSphere(1, 10, 10); // fim da lampada
	glPopMatrix();

	/** Boneco **/

	// cabeça //
	glScalef(1, 1, 1);
	glTranslatef(-150, 20, 50);
	glColor3d(1, 1, 1);
	glutSolidSphere(5, 200, 10);

	// corpo //
	glScalef(1, 1, 1);
	glTranslatef(0, -10, 0);
	glColor3d(0, 0, 0);
	glutSolidSphere(5, 200, 10);

	// braço direito
	glTranslatef(0, -6, 5);
	glRotatef(90, -1, 0, 0);
	glColor3d(0, 0, 0);
	glutSolidCylinder(1, 10, 10, 2);

	// braço esquerdo //
	glTranslatef(0, 10, 0);
	glRotatef(0, -1, 0, 0);
	glColor3d(0, 0, 0);
	glutSolidCylinder(1, 10, 10, 2);

	// perna esquerda //
	glTranslatef(0, -3, -11);
	glRotatef(0, -1, 0, 0);
	glColor3d(1, 0, 0);
	glutSolidCylinder(2, 16, 10, 2);

	// perna direita //
	glTranslatef(0, -4, 0);
	glRotatef(0, -1, 0, 0);
	glColor3d(1, 0, 0);
	glutSolidCylinder(2, 16, 10, 2);

	sun();

	clouds();

	tree();

	house ();

	glutSwapBuffers();
}

void wireBox(float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x / 2, 0, 0);
	glutWireCube(1);
	glScalef(x, y, z);
	glPopMatrix();
}

void myReshape(int winWidth, int winHeight) // reshape window
{
	int tam = winWidth < winHeight ? winWidth : winHeight;
	glViewport(0, 0, tam, tam); // reset the viewport
}

/*comandos especiais do teclado*/

void keySpecial(int key, int x, int y)
{
	printf("(%d, %d)\n", x, y);
	switch (key)
	{
	case GLUT_KEY_LEFT:
		printf("Left pressed\n");
		break;
	case GLUT_KEY_UP:
		printf("Up pressed\n");
		break;
	}

	if (glutGetModifiers() == GLUT_ACTIVE_ALT) // GLUT_ACTIVE_CTRL ou SHIFT
		printf("ALT pressed\n");
}

void myKeyboard(unsigned char c, int x, int y)
{
	switch(c)
    {
        case  27: exit(0);          break; // ESC

        case 'a': azimuth   -= 0.5; break;

        case 'd': azimuth   += 0.5; break;

        case 'w': incidence -= 0.5; break;

        case 's': incidence += 0.5; break;

        case 'q': twist     -= 0.5; break;

        case 'e': twist     += 0.5; break;

        case 'z': distance  -= 0.1; break;

        case 'x': distance  += 0.1; break;

    }
    glutPostRedisplay();
}

// imprimir as coordenadas com o clique do mouse

void myMouse(int b, int s, int x, int y)
{
	switch (b)
	{
	case GLUT_LEFT_BUTTON:
		printf("(%d, %d)\n", x, y);
	}
}

// função detecta movimento do mouse e salva coordenadas
void myMotion(int x, int y)
{
	printf("Motion: (%d, %d)\n", x, y);
}

void init(void)

{

	// Define a cor de fundo da janela de visualização como branca

	glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

	// Habilita a definição da cor do material a partir da cor corrente

	glEnable(GL_COLOR_MATERIAL);

	// Habilita o uso de iluminação

	glEnable(GL_LIGHTING);

	// Habilita a luz de número 0

	glEnable(GL_LIGHT0);

	// Habilita o depth-buffering

	glEnable(GL_DEPTH_TEST);

	// Habilita o modelo de colorização de Gouraud

	glShadeModel(GL_FLAT);

	// Inicializa a variável que especifica o ângulo da projeção

	// perspectiva

	angle = 45;

	// Inicializa as variáveis usadas para alterar a posição do

	// observador virtual

	rotX = 0;

	rotY = 0;

	obsX = obsY = 0;

	obsZ = 150;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	// Define o modo de operação da GLUT

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Especifica a posição inicial da janela GLUT

	glutInitWindowPosition(5, 5);

	// Especifica o tamanho inicial em pixels da janela GLUT

	glutInitWindowSize(1200, 1200);

	// Cria a janela passando como argumento o título da mesma

	glutCreateWindow("Open GL car");

	// Registra a função callback de redesenho da janela de visualização

	glutDisplayFunc(display);

	// Registra a função callback de redimensionamento da janela de visualização

	glutReshapeFunc(Reshape);

	// Registra a função callback para tratamento das teclas normais

	glutKeyboardFunc(myKeyboard);

	// Registra a função callback para tratamento das teclas especiais

	glutSpecialFunc(keySpecial);

	// Registra a função callback para eventos de botões do mouse

	glutMouseFunc(myMouse);

	// Registra a função callback para eventos de movimento do mouse

	glutMotionFunc(GerenciaMovim);

	// Chama a função responsável por fazer as inicializações

	init();

	// Inicia o processamento e aguarda interações do usuário

	glutMainLoop();

	return 0;
}
