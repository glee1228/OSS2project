
#include <stdlib.h>  
#include <glut.h> 
#include <iostream> 
#include <math.h>  
#include <time.h>  
#include <string.h>  
#define pi 3.14 
//���: ����, �׸�, �� 
int board[3][3];   // board for gameplay   
int turn;         // current move  
int result;         // Result of the game   
bool over;         // Is the game Over?   

int kind1; //player1�� ��(����, �׸�, ��)�� ��Ÿ���� ���� ����=1, �׸�=2, ��=3  
int kind2; //player2�� �� (����, �׸�, ��)�� ��Ÿ���� ���� ����=1, �׸�=2, ��=3 
const GLfloat size = 2.0;
void DrawString(void *font, const char s[], float x, float y) // string �Լ� 
{
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i<strlen(s); i++)
	{
		glutBitmapCharacter(font, s[i]);
	}
}
void Triangle(int x, int y, int r) // �ﰢ�� ����� �Լ� x��ǥ, y��ǥ, ũ�⸦ ��Ÿ�� r 
{
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.5, 0.0);
	glVertex2f(x, y + r + size);
	glVertex2f(x + r*cos(330 * pi / 180) - size, y + r*sin(330 * pi / 180) - size);
	glVertex2f(x + r*cos(210 * pi / 180) + size, y + r*sin(210 * pi / 180) - size);
	glEnd();
}
void Rectangular(int x, int y, int r) // �簢�� ����� �Լ� 
{
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.5, 0.0);
	glVertex2f(x + r, y + r);
	glVertex2f(x - r, y + r);
	glVertex2f(x - r, y - r);
	glVertex2f(x + r, y - r);
	glEnd();
}

void Circle(float cx, float cy, float r, int num_segments)  //�� ����� �Լ� 
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle  ������ angle ���       
		float x = r * cosf(theta);//calculate the x component  ���� angle���� x��ǥ ���ϱ�      
		float y = r * sinf(theta);//calculate the y component  ���� angle���� y��ǥ ���ϱ�      
		glVertex2f(x + cx, y + cy);//output vertex    
	}
	glEnd();
}
void SetKinkByMouse(int button, int state, int x, int y)//���콺�Լ� �̿��ؼ� ���� ������ x��ǥ�� 0~100�̸� ����, 101~200�̸� �׸�, 201~300�̸� ������
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (x>0 && x<101 && y < 150 && kind2 != 1) //���� �������� ���      
			kind1 = 1;
		else if (x>100 && x<201 && y<150 && kind2 != 1)//�׸� �������� ��� 
			kind1 = 2;
		else if (x>200 && x<300 && y<150 && kind2 != 1)//�� �������� ���  
			kind1 = 3;

	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if ((x>0 && x<101 && y<150) && kind1 != 1) //���� �������� ���     
			kind2 = 1;//kind�� 1�� ����      
		else if ((x>100 && x<201 && y<150) && kind1 != 2)//�׸� �������� ���      
			kind2 = 2;//kind�� 2�� ����       
		else if ((x>200 && x<300 && y<150) && kind1 != 3)//�� �������� ���         
			kind2 = 3;//kind�� 3���� ����     

	}
}
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);
	DrawString(GLUT_BITMAP_HELVETICA_18, "CHOOSE", 100, 30);
	Triangle(50, 100, 30);
	Rectangular(150, 100, 30);
	Circle(250, 100, 30, 15);
	DrawString(GLUT_BITMAP_HELVETICA_18, "PLAYER1", 45, 180);
	DrawString(GLUT_BITMAP_HELVETICA_18, "PLAYER2", 200, 180);
	glFlush();
	switch (kind1)
	{
	case 1:
		Triangle(50, 230, 30);
		break;
	case 2:
		Rectangular(50, 230, 30);
		break;
	case 3:
		Circle(50, 230, 30, 15);
		break;
	}
	switch (kind2)
	{
	case 1:
		Triangle(250, 230, 30);
		break;
	case 2:
		Rectangular(250, 230, 30);
		break;
	case 3:
		Circle(250, 230, 30, 15);
		break;
	}
	glutSwapBuffers();
}

void Reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(300, 350); //������ ������� x=300, y=350    
	glutCreateWindow("Tic Tac Toe"); //������ ��    
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMouseFunc(SetKinkByMouse);
	glutIdleFunc(Display);
	glutMainLoop();
	return 0;
}