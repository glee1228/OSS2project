/*
���ϸ� : TicTaeToe.cpp
�ۼ��� : ������, ABHISHEK BIND(��������)
���� : 2�ο� ������ ��������� ���� �ϱ� ���� ���α׷��� �������.
����� : START��ư�� ���� �� ������ ���� �ϸ� �ȴ�.
������� : �ش� ���� ����
���ѻ��� : �ش� ���� ����
����ó�� : Visual Studio ���� ���� �Ҷ� ���и�ũ����� �ƴϿ�� ������ �־�� �Ѵ�.
�̷»��� : 2015-12-1 : ABHISHEK BIND - ���� �ۼ�
2017-04-26 ~ 2017-05-07 : �� ���� - ����ȭ��,����ȭ�� �߰�
2017-05-31 ~ 2017-06-02 : �� ���� - ����ȭ�鿡 �����ø޴�(������ �ۼ�),��Ģ ����޴� �κ��� ��ħ
*/

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <glut.h>
#define PI 3.141592 //PI�� 3.141592�� �����ص�

int stage = 1;		// ����ȭ��(1), ����ȭ��(2), ����ȭ��(3)���� ����, ù ȭ���� ����ȭ���̹Ƿ� 1�� �ʱ�ȭ
int board[3][3];	// ���� ������
int turn;			// ������ ��(player1 or player2)
int result;			// ������ ���
bool over;			// ���� ���� ����  
bool finish1 = false; //player1�� ������ �����°��� �˸��� ����  
bool finish2 = false; //player2�� �� ������ �����°��� �˸��� ����  
int kind1; //player1�� ���� ��Ÿ���� ����  
int kind2; //player2�� ���� ��Ÿ���� ���� 
const GLfloat size = 2.0;

void DrawCircle(float cx, float cy, float r, int num_segments); //�� ���� �޴��� �� �Լ��� ���� ���� �̸� �Լ� ������ ������
void DrawCross(float cx, float cy);//�� ���� �޴��� �� �Լ��� ���� ���� �̸� �Լ� ������ ������

								   /*
								   �������� �ʱ�ȭ �ϴ� �Լ�
								   */
void Intialize()
{
	turn = 1;
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
			board[i][j] = 0;
	}
}

/*
START ��ư
*/
void StartButton()
{
	glColor3f(1, 1, 1);
	glLineWidth(10);
	//S ��Ÿ����
	glBegin(GL_LINES);
	glVertex2f(15 * 1.5, 20 * 1.5);
	glVertex2f(60 * 1.5, 20 * 1.5);

	glVertex2f(15 * 1.5, 20 * 1.5);
	glVertex2f(15 * 1.5, 90 * 1.5);

	glVertex2f(15 * 1.5, 90 * 1.5);
	glVertex2f(60 * 1.5, 90 * 1.5);

	glVertex2f(60 * 1.5, 90 * 1.5);
	glVertex2f(60 * 1.5, 160 * 1.5);

	glVertex2f(60 * 1.5, 160 * 1.5);
	glVertex2f(15 * 1.5, 160 * 1.5);
	glEnd();
	//T ��Ÿ����
	glBegin(GL_LINES);
	glVertex2f(70 * 1.5, 20 * 1.5);
	glVertex2f(120 * 1.5, 20 * 1.5);

	glVertex2f(95 * 1.5, 20 * 1.5);
	glVertex2f(95 * 1.5, 160 * 1.5);
	glEnd();
	//A ��Ÿ����
	glBegin(GL_LINES);
	glVertex2f(130 * 1.5, 20 * 1.5);
	glVertex2f(130 * 1.5, 160 * 1.5);

	glVertex2f(130 * 1.5, 20 * 1.5);
	glVertex2f(175 * 1.5, 20 * 1.5);

	glVertex2f(175 * 1.5, 20 * 1.5);
	glVertex2f(175 * 1.5, 160 * 1.5);

	glVertex2f(130 * 1.5, 90 * 1.5);
	glVertex2f(175 * 1.5, 90 * 1.5);
	glEnd();
	//R ��Ÿ����
	glBegin(GL_LINES);
	glVertex2f(185 * 1.5, 20 * 1.5);
	glVertex2f(185 * 1.5, 160 * 1.5);

	glVertex2f(185 * 1.5, 20 * 1.5);
	glVertex2f(230 * 1.5, 20 * 1.5);

	glVertex2f(185 * 1.5, 90 * 1.5);
	glVertex2f(230 * 1.5, 90 * 1.5);

	glVertex2f(230 * 1.5, 20 * 1.5);
	glVertex2f(230 * 1.5, 90 * 1.5);

	glVertex2f(185 * 1.5, 90 * 1.5);
	glVertex2f(230 * 1.5, 160 * 1.5);
	glEnd();
	//T ��Ÿ����
	glBegin(GL_LINES);
	glVertex2f(240 * 1.5, 20 * 1.5);
	glVertex2f(290 * 1.5, 20 * 1.5);

	glVertex2f(265 * 1.5, 20 * 1.5);
	glVertex2f(265 * 1.5, 160 * 1.5);
	glEnd();
}

/*
������ �޴� �κ� �ڸ�
*/
void Select(int x, int y, int r)
{
	glBegin(GL_LINES);
	glColor3f(0.5*1.5, 0.7*1.5, 0.4*1.5);
	//�簢�� �����
	glVertex2f(10 * 1.5, 340 * 1.5);
	glVertex2f(10 * 1.5, 190 * 1.5);

	glVertex2f(10 * 1.5, 190 * 1.5);
	glVertex2f(140 * 1.5, 190 * 1.5);

	glVertex2f(140 * 1.5, 190 * 1.5);
	glVertex2f(140 * 1.5, 340 * 1.5);

	glVertex2f(140 * 1.5, 340 * 1.5);
	glVertex2f(10 * 1.5, 340 * 1.5);

	glVertex2f(10 * 1.5, 340 * 1.5);
	glVertex2f(140 * 1.5, 190 * 1.5);
	glEnd();
	DrawCircle(45 * 1.5, 240 * 1.5, 25 * 1.5, 15 * 1.5);
	DrawCross(105 * 1.5, 300 * 1.5);
}

/*
��Ģ���� �޴� �κ� �ڸ�
*/
void Rule(int x, int y)
{
	glBegin(GL_LINES);
	glColor3f(0.5, 0.7, 0.4);
	//�簢�� �����
	glVertex2f(160 * 1.5, 340 * 1.5);
	glVertex2f(160 * 1.5, 190 * 1.5);

	glVertex2f(160 * 1.5, 190 * 1.5);
	glVertex2f(290 * 1.5, 190 * 1.5);

	glVertex2f(290 * 1.5, 190 * 1.5);
	glVertex2f(290 * 1.5, 340 * 1.5);

	glVertex2f(290 * 1.5, 340 * 1.5);
	glVertex2f(160 * 1.5, 340 * 1.5);

	//R ��Ÿ����
	glVertex2f(170 * 1.5, 245 * 1.5);
	glVertex2f(190 * 1.5, 245 * 1.5);

	glVertex2f(170 * 1.5, 245 * 1.5);
	glVertex2f(170 * 1.5, 265 * 1.5);

	glVertex2f(170 * 1.5, 265 * 1.5);
	glVertex2f(190 * 1.5, 265 * 1.5);

	glVertex2f(190 * 1.5, 265 * 1.5);
	glVertex2f(190 * 1.5, 245 * 1.5);

	glVertex2f(170 * 1.5, 265 * 1.5);
	glVertex2f(190 * 1.5, 285 * 1.5);

	glVertex2f(170 * 1.5, 265 * 1.5);
	glVertex2f(170 * 1.5, 285 * 1.5);

	//U ��Ÿ����
	glVertex2f(200 * 1.5, 245 * 1.5);
	glVertex2f(200 * 1.5, 285 * 1.5);

	glVertex2f(200 * 1.5, 285 * 1.5);
	glVertex2f(220 * 1.5, 285 * 1.5);

	glVertex2f(220 * 1.5, 285 * 1.5);
	glVertex2f(220 * 1.5, 245 * 1.5);

	//L ��Ÿ����
	glVertex2f(230 * 1.5, 245 * 1.5);
	glVertex2f(230 * 1.5, 285 * 1.5);

	glVertex2f(250 * 1.5, 285 * 1.5);
	glVertex2f(230 * 1.5, 285 * 1.5);

	//E ��Ÿ����
	glVertex2f(260 * 1.5, 245 * 1.5);
	glVertex2f(280 * 1.5, 245 * 1.5);

	glVertex2f(260 * 1.5, 245 * 1.5);
	glVertex2f(260 * 1.5, 285 * 1.5);

	glVertex2f(260 * 1.5, 265 * 1.5);
	glVertex2f(280 * 1.5, 265 * 1.5);

	glVertex2f(260 * 1.5, 285 * 1.5);
	glVertex2f(280 * 1.5, 285 * 1.5);
	glEnd();
}

/*
Ű�����Լ� : y�� ������ ���� �ٽ� ����, n�� ������ ���� ����, �ٸ� ��ư ������ ���� ����
*/
void OnKeyPress(unsigned char key, int x, int y)
{
	//'o'Ű�� ������ Player1�� ���� ������
	if (stage == 4 && key == 'o')
	{
		finish1 = true;
	}

	switch (key)
	{
	case 'y':
		if (over == true)
		{
			over = false;
			Intialize();
			stage = 2;
		}
		break;
	case 'n':
		if (over == true)
		{
			exit(0);
		}
		break;

	}
}

/*
���콺�Լ� : stage�� 1�϶� start��ư�� ������ ���� �������� stage�� 2�� �Ѿ
stage�� 2�϶� player�� ���� �ڸ��� �ƹ� ���� ���� ���� ������ �ڽ��� ���� ���� turn�� �Ѱ���
stage�� 4�϶� ������ �� CLOSE ��ư�� ������ stage1�� �Ѿ
stage�� 5�϶� ��Ģ ���� �޴��� CLOSE ��ư�� ������ stage1�� �Ѿ
*/
void OnMouseClick(int button, int state, int x, int y)
{
	if (stage == 1)
	{
		//START��ư�� ������ ���� ȭ������ �Ѿ
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x>10 && x<290 && y>20 && y<160)
		{
			stage = 2;
			glutPostRedisplay();
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x>10 && x< 140 && y>190 && y<340)
		{
			stage = 4;
			glutPostRedisplay();
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x>160 && x< 290 && y>190 && y<340)
		{
			stage = 5;
			glutPostRedisplay();
		}
	}
	else if (stage == 2)
	{
		if (over == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (turn == 1)
			{
				if (board[(y - 50) / 100][x / 100] == 0)
				{
					board[(y - 50) / 100][x / 100] = 1;
					turn = 2;
				}
			}
			else if (turn == 2)
			{
				if (board[(y - 50) / 100][x / 100] == 0)
				{
					board[(y - 50) / 100][x / 100] = 2;
					turn = 1;
				}
			}
		}
	}
	else if (stage == 4)
	{
		//Player1�� ������
		if (finish1 == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (x>22.3 && x<81.7 && y>75 && y < 122)
				kind1 = 1;
			else if (x>90 && x<150 && y>70 && y<150)
				kind1 = 2;
			else if (x>165 && x<215 && y>75 && y<125)
				kind1 = 3;
			else if (x>225 && x<275 && y>75 && y<125)
				kind1 = 4;
		}

		//Player1�� �������� ���� �� Player2�� ������
		if (finish1 == true && finish2 == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (x>22.3 && x<81.7 && y>91 && y < 122)
				kind2 = 1;
			else if (x>90 && x<150 && y>70 && y<150)
				kind2 = 2;
			else if (x>165 && x<215 && y>75 && y<125)
				kind2 = 3;
			else if (x>225 && x<275 && y>75 && y<125)
				kind2 = 4;
			finish2 = true;
		}

		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x>120 && x<190 && y>290 && y<310)
		{
			stage = 1;
		}
	}
	else if (stage == 5)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x>20 && x<90 && y>310 && y<330)
		{
			stage = 1;
		}
	}
}

/*
������ ��������, ���� �̰���� ��Ʈ�� �������� �˷��ִ� �Լ�
*/
void DrawString(void *font, const char s[], float x, float y)
{
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i<strlen(s); i++)
	{
		glutBitmapCharacter(font, s[i]);
	}
}

/*
������ ���� �׸�
*/
void DrawLines()
{
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(100, 50);
	glVertex2f(100, 340);

	glVertex2f(200, 340);
	glVertex2f(200, 50);

	glVertex2f(0, 150);
	glVertex2f(300, 150);

	glVertex2f(0, 250);
	glVertex2f(300, 250);
	glEnd();
}

/*
�� ��� �带 �׸�
*/
void Triangle(int x, int y, int r)
{

	glBegin(GL_POLYGON);
	glVertex2f(x, y + r + size);
	glVertex2f(x + r*cos(330 * PI / 180) - size, y + r*sin(330 * PI / 180) - size);
	glVertex2f(x + r*cos(210 * PI / 180) + size, y + r*sin(210 * PI / 180) - size);
	glEnd();
}

/*
�� ��� �Ḧ �׸�
*/
void Rectangular(int x, int y, int r)
{
	glBegin(GL_POLYGON);
	glVertex2f(x + r, y + r);
	glVertex2f(x - r, y + r);
	glVertex2f(x - r, y - r);
	glVertex2f(x + r, y - r);
	glEnd();
}


/*
�� ��� X�� �׸�
*/
void DrawCross(float cx, float cy)
{
	glBegin(GL_LINES);
	glVertex2f(cx - 25, cy - 25);
	glVertex2f(cx + 25, cy + 25);
	glVertex2f(cx - 25, cy + 25);
	glVertex2f(cx + 25, cy - 25);
	glEnd();
}

/*
�� ����� O�� �׸�
*/
void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++)
	{
		float theta;
		theta = 2.0f * PI* float(i);
		theta = theta / float(num_segments);//���� ������ ���� 
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();
}

/*
������ �ȿ� �� �÷��̾��� ���� �׸��� �Լ�
*/
void Draw()
{
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if (board[i][j] == 1)
			{
				if (kind1 == 1)
				{
					Triangle(50 + j * 100, 100 + i * 100, 30);
				}
				else if (kind1 == 2)
				{
					Rectangular(50 + j * 100, 100 + i * 100, 30);
				}
				else if (kind1 == 3)
				{
					DrawCross(50 + j * 100, 100 + i * 100);
				}
				else if (kind1 == 4)
				{
					DrawCircle(50 + j * 100, 100 + i * 100, 25, 15);
				}
			}
			else if (board[i][j] == 2)
			{
				if (kind2 == 1)
				{
					Triangle(50 + j * 100, 100 + i * 100, 30);
				}
				else if (kind2 == 2)
				{
					Rectangular(50 + j * 100, 100 + i * 100, 30);
				}
				else if (kind2 == 3)
				{
					DrawCross(50 + j * 100, 100 + i * 100);
				}
				else if (kind2 == 4)
				{
					DrawCircle(50 + j * 100, 100 + i * 100, 25, 15);
				}
			}
		}
	}
}

/*
��Ģ�� �ǰ��� �¸��� �˻��ϴ� �Լ�
*/
bool CheckWinner()
{
	int i, j;

	// ���η� ���� ���� �̾������� �˻�  
	for (i = 0; i<3; i++)
	{
		for (j = 1; j<3; j++)
		{
			if (board[i][0] != 0 && board[i][0] == board[i][j])
			{
				if (j == 2)
				{
					return true;//���� �˻縦 �����ϸ� �¸��ڰ� �ִ� ������ true�� ��ȯ��
				}
			}
			else
				break;
		}
	}

	//���η� ���� ���� �̾������� �˻� 
	for (i = 0; i<3; i++)
	{
		for (j = 1; j<3; j++)
		{
			if (board[0][i] != 0 && board[0][i] == board[j][i])
			{
				if (j == 2)
					return true;//���� �˻縦 �����ϸ� �¸��ڰ� �ִ� ������ true�� ��ȯ��
			}
			else
				break;
		}
	}

	// �밢������ ���� ���� �̾������� �˻�
	if ((board[0][0] != 0 && board[0][0] == board[1][1] && board[0][0] == board[2][2])
		|| (board[2][0] != 0 && board[2][0] == board[1][1] && board[2][0] == board[0][2]))
	{
		return true;//���� �˻縦 �����ϸ� �¸��ڰ� �ִ� ������ true�� ��ȯ��
	}

	return false;//���� �˻縦 �������� ������ �¸��ڰ� ���� ������ false�� ��ȯ��
}

/*
���º� ������ �˻��ϴ� �Լ�
*/
bool CheckIfDraw()
{
	int i, j;
	for (i = 0; i<3; i++)
	{
		for (j = 0; j<3; j++)
		{
			if (board[i][j] == 0)
				return false;//�������� �� ���� �������� �ʾ����� ���ºΰ� �������� �����Ƿ� false�� ��ȯ
		}
	}
	return true;//�������� ��� ���� ���� á�⿡ ���º��̹Ƿ� true�� ��ȯ��	
}

/*
ȭ�鿡 ��ü�� ���� �Լ�
*/
void Display()
{
	//���� ȭ�� �϶� 
	if (stage == 1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.7, 0.4, 0.7, 1);
		Select(0, 0, 0);
		Rule(0, 0);
		StartButton();
	}

	//���� ȭ�� �϶�
	else if (stage == 2)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);
		glColor3f(0, 0, 0);
		if (turn == 1)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's turn", 100, 30);
		else
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's turn", 100, 30);

		DrawLines();
		Draw();

		//�¸��� �˻� 
		if (CheckWinner() == true)
		{
			if (turn == 1)
			{
				over = true;
				result = 2;
			}
			else
			{
				over = true;
				result = 1;
			}
		}

		//���º� �˻�
		else if (CheckIfDraw() == true)
		{
			over = true;
			result = 0;
		}
		if (over == true)
		{
			stage = 3;

		}
	}

	//���� ȭ�� �϶�
	else if (stage == 3)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.7, 0.4, 0.7, 1);
		DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 100, 160);
		if (result == 0)
			DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw!", 110, 185);
		if (result == 1)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins!", 95, 185);
		if (result == 2)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins!", 95, 185);

		DrawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue? (y/n)", 40, 210);
	}
	else if (stage == 4)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.7, 0.4, 0.7, 1);
		DrawString(GLUT_BITMAP_HELVETICA_18, "CHOOSE", 120, 30);
		Triangle(50, 90, 30);
		Rectangular(120, 100, 30);
		DrawCross(190, 100);
		DrawCircle(250, 100, 25, 15);

		DrawString(GLUT_BITMAP_HELVETICA_18, "PLAYER1", 45, 180);
		DrawString(GLUT_BITMAP_HELVETICA_18, "PLAYER2", 200, 180);
		DrawString(GLUT_BITMAP_HELVETICA_18, "CLOSE", 120, 300);
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
			DrawCross(50, 230);
			break;
		case 4:
			DrawCircle(50, 230, 30, 15);
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
			DrawCross(250, 230);
			break;
		case 4:
			DrawCircle(250, 230, 30, 15);
			break;
		}
	}
	else if (stage == 5)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.7, 0.4, 0.7, 1);
		DrawString(GLUT_BITMAP_HELVETICA_18, "A game that wins when my three", 20, 30);
		DrawString(GLUT_BITMAP_HELVETICA_18, "symbols are placed side by side.", 20, 50);
		DrawString(GLUT_BITMAP_HELVETICA_18, "Players should not have", 20, 80);
		DrawString(GLUT_BITMAP_HELVETICA_18, "the same symbol shape.", 20, 100);
		DrawString(GLUT_BITMAP_HELVETICA_18, "The player who won more", 20, 130);
		DrawString(GLUT_BITMAP_HELVETICA_18, "games in 9 games is the winner.", 20, 150);
		DrawString(GLUT_BITMAP_HELVETICA_18, "Please select the sign and start", 20, 180);
		DrawString(GLUT_BITMAP_HELVETICA_18, "the game!", 20, 200);
		DrawString(GLUT_BITMAP_HELVETICA_18, "Select the symbol for player1,", 20, 230);
		DrawString(GLUT_BITMAP_HELVETICA_18, "press the 'o' key, and select", 20, 250);
		DrawString(GLUT_BITMAP_HELVETICA_18, "the player2 symbol.", 20, 270);
		DrawString(GLUT_BITMAP_HELVETICA_18, "CLOSE", 20, 320);
	}
	glutSwapBuffers();
}

/*
ȭ�� ũ�Ⱑ ����ɶ� ��ü�� ������ �����ǵ��� �ϴ� �Լ�
*/
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
	Intialize();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(550, 200);
	glutInitWindowSize(450, 500);
	glutCreateWindow("Tic Tac Toe");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(OnKeyPress);
	glutMouseFunc(OnMouseClick);
	glutIdleFunc(Display);
	glutMainLoop();
	return 0;
}