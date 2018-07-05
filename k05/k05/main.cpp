#pragma warning (disable:4996)
#define _MAIN_MODULE

#include <time.h>
#include "DblBuffer.h"
#include "conioex.h"

//**********************************************************************
//	��̒�`
//**********************************************************************
#define  PI			3.1415926f			//	�~����
#define  CON_WIDTH	(SCREEN_SIZE_X)		//	�R���\�[����
#define  CON_HEIGHT (SCREEN_SIZE_Y/2)	//	�R���\�[������

#define  AIR_REGIST 0.95f				//	��C��R�l
#define  GRAVITY	0.3					//	�������x
#define  MIN_LIFE_CNT (100)			//	�ŒZ��������
#define  RAND_LIFE_CNT 10				//	�������ԗ�����
#define  EXP_SPEED	5.5f

#define  MAX_FIREWORKS 60				//�@���q�̐�
#define  MAX_TREE 128

#define  POSX		(CON_WIDTH/2)		//	�p�[�e�B�N�������ʒuX���W
#define  POSY		(CON_HEIGHT/2)		//	�p�[�e�B�N�������ʒuY���W
//**********************************************************************
//	�\���̒�`
//**********************************************************************
typedef struct _TFirework
{
	int bAvctive;
	float fPosX, fPosY;		  //	���ݍ��W
	float fDirection;		  //	�ړ�����
	float angle;
	float fVx, fVy;				
	int nLifeCnt;			  //	��������
}TFIREWORK;

typedef struct TagFractalTree
{
	int bAvctive;
	int level;
	float fPosX, fPosY;		  //	���ݍ��W
	float fDirection;		  //	�ړ�����
	float fVx, fVy;
	float angle;
	int fStart, fEnd;
	int nLifeCnt;			  //	��������
}FractalTree;
//**********************************************************************
//	�O���[�o���ϐ�
//**********************************************************************
//	�p�[�e�B�N���p�\���̕ϐ�
TFIREWORK g_fireworks[MAX_FIREWORKS];
TFIREWORK g_fireworks1[MAX_FIREWORKS*3];
TFIREWORK g_snow[MAX_FIREWORKS];
FractalTree g_tree[MAX_TREE];
int g_nTimeCount = 0;
int g_fireCnt = 0;

//**********************************************************************
//	�v���g�^�C�v�錾
//**********************************************************************
int Init(int);
int InitFire(int);
int InitTree(int);
int InitSnow(int);
void Draw(int,int,int);
int Move(void);
float FractalBinaryTree(int, int, float);
//**********************************************************************
//	�v���O����
//**********************************************************************
int main()
{
	DblBufferObject()->CreatHandle();
	//	��ʏ�����
	CLS();							//	��ʃN���A
	CUROFF();						//	�J�[�\����\��

	//	�����l�ݒ�
	srand((unsigned)time(NULL));	//	����������
	int nColor = Init(0);			//	�e�p�[�e�B�N����������
	int fColor = InitFire(g_fireCnt);
	int tColor = InitTree(0);
	InitSnow(0);
	int cnt = 0;
	//	���C�����[�v
	while (1)
	{
		//CLS();						//	��ʃN���A
		DblBufferObject()->ClearScreen(BLACK);

		if (!Move())
		{
			g_fireCnt++;
			if (g_fireCnt==3)
			{
				g_fireCnt = 0;
			}
			fColor = InitFire(g_fireCnt);
		}
	    Draw(nColor,fColor, tColor);
		if ((g_nTimeCount % 2) == 0) {
			for (int i = 0; i < MAX_FIREWORKS; i++) {
				if (g_fireworks[i].bAvctive == false) {
					if (i == 0)
					{
						nColor = Init(i);
					}
					else
					{
						Init(i);
					}
					break;
				}
			}
			for (int i = 0; i < MAX_FIREWORKS; i++) {
				if (g_snow[i].bAvctive == false) {
					InitSnow(i);
					break;
				}
			}
			for (int i = 0; i < MAX_TREE; i++) {
				if (g_tree[i].bAvctive == false) {
					if (i == 0)
					{
						tColor = InitTree(i);
					}
					else
					{
						InitTree(i);
					}
					break;
				}
			}
		}
		g_nTimeCount++;
		
		if (kbhit())
		{
			if (getch()==0x1b)		//	ESC�L�[�ŏI��
				break;
		}
		DblBufferObject()->Swap();
		cnt++;
		//WAIT(20);
	}
	//	��ʂ̕��A
	LOCATE(1, 24);	//	�J�[�\���ʒu��ݒ�
	//COLOR(WHITE);
	CURON();
	DblBufferObject()->Close();
	return EXIT_SUCCESS;
}

//======================================================================
//	�p�[�e�B�N���̏�����
//�@����:i	�z��̃C���f�N�X
//	�߂�l:�\���F(�ԍ�)
//======================================================================
int Init(int i)
{
	float fposX = POSX;
	float fposY = CON_HEIGHT - 10;
	float fRand_r, fRand_t;
	g_fireworks[i].fPosX = fposX;
	g_fireworks[i].fPosY = fposY;
	g_fireworks[i].bAvctive = true;
	fRand_r = sqrtf(-2.0f * logf((float)(rand() + 1) / (RAND_MAX + 1)));
	fRand_t = 2.0f * PI * (float)rand() / RAND_MAX;
	g_fireworks[i].fVx = (fRand_r * cosf(fRand_t)) * 3;
	g_fireworks[i].fVy = (fRand_r * sinf(fRand_t)) - 9;
	g_fireworks[i].nLifeCnt = MIN_LIFE_CNT;

	return rand() % 6 + 9;
}

//======================================================================
//	�p�[�e�B�N���̏�����
//�@����:n	��
//	�߂�l:�\���F(�ԍ�)
//======================================================================
int InitFire(int n)
{
	float fposX = POSX;
	float fposY = CON_HEIGHT - 10;
	float fRand_r, fRand_t;
	for (int i = MAX_FIREWORKS*n; i < MAX_FIREWORKS*(n + 1); i++)
	{
		g_fireworks1[i].fPosX = fposX;
		g_fireworks1[i].fPosY = fposY;
		g_fireworks1[i].bAvctive = true;
		fRand_r = sqrtf(-2.0f * logf((float)(rand() + 1) / (RAND_MAX + 1)));
		fRand_t = 2.0f * PI * (float)rand() / RAND_MAX;
		g_fireworks1[i].fVx = (fRand_r * cosf(fRand_t)) * 3;
		g_fireworks1[i].fVy = (fRand_r * sinf(fRand_t)) - 8;
		g_fireworks1[i].nLifeCnt = MIN_LIFE_CNT;

	}
	return rand() % 6 + 9;
}

//======================================================================
//	�p�[�e�B�N���̏�����
//�@����:i	�z��̃C���f�N�X
//	�߂�l:�\���F(�ԍ�)
//======================================================================
int InitTree(int i)
{
	float fposX = POSX;
	float fposY = CON_HEIGHT - 10;
	g_tree[i].level = 0;
	g_tree[i].fPosX = fposX;
	g_tree[i].fPosY = fposY;
	g_tree[i].nLifeCnt = MIN_LIFE_CNT * 3;
	g_tree[i].fStart = 0;
	g_tree[i].fEnd = 64;
	g_tree[i].angle = 90;
	g_tree[i].fDirection = g_tree[i].angle*PI / 180;
	g_tree[i].fVx = cos(g_tree[i].fDirection) * 2;
	g_tree[i].fVy = sin(g_tree[i].fDirection);
	g_tree[i].bAvctive = true;
	return rand() % 6 + 9;
}

int InitSnow(int i)
{
	float fRand_r, fRand_t;
	g_snow[i].fPosX = rand() % (CON_WIDTH-3) + 3;
	
	g_snow[i].fPosY = 0 - rand() % 10;
	g_snow[i].bAvctive = true;
	g_snow[i].angle = 0;
	g_snow[i].fDirection = g_snow[i].angle*PI / 180;
	g_snow[i].fVx = cosf(g_snow[i].fDirection) * 1.5;
	g_snow[i].fVy = 1;
	g_snow[i].nLifeCnt = MIN_LIFE_CNT-10;

	return 15;
}

//======================================================================
//	�p�[�e�B�N���̕`��
//�@����:nColor�@fColor �@tColor�@�\���F(�O�`�P�T)
//	�߂�l:�Ȃ�
//======================================================================
void Draw(int nColor,int fColor,int tColor)
{
	
	int nPosX, nPoxY, oPosX, oPosY;
	
	//	��������
	for (int i = 0; i < MAX_FIREWORKS; i++)
	{
		nPosX = (int)g_fireworks[i].fPosX;
		nPoxY = (int)g_fireworks[i].fPosY;
	
		if (nPosX < 1 || nPosX >= CON_WIDTH-1 || nPoxY < 0 || nPoxY >= CON_HEIGHT-1)
		{
			continue;
		}
		DblBufferObject()->SetColor(nColor, BLACK);
		DblBufferObject()->SetCursorPos(nPosX, nPoxY);
		DblBufferObject()->Write("M");
		DblBufferObject()->SetCursorPos(nPosX-1, nPoxY+1);
		DblBufferObject()->Write("MMM");
		
	}

	//	�񕪖�
	for (int i = 0; i < MAX_TREE; i++)
	{
		nPosX = (int)g_tree[i].fPosX;
		nPoxY = (int)g_tree[i].fPosY;

		if (nPosX < 0 || nPosX >= CON_WIDTH || nPoxY < 0 || nPoxY >= CON_HEIGHT)
		{
			continue;
		}
		DblBufferObject()->SetColor(tColor, tColor);
		DblBufferObject()->SetCursorPos(nPosX, nPoxY);
		DblBufferObject()->Write("  ");
	}

	//	���e
	for (int i = 0; i < MAX_FIREWORKS*(g_fireCnt+1); i++)
	{
		nPosX = (int)g_fireworks1[i].fPosX;
		nPoxY = (int)g_fireworks1[i].fPosY;

		if (nPosX < 0 || nPosX >= CON_WIDTH || nPoxY < 0 || nPoxY >= CON_HEIGHT)
		{
			continue;
		}
		DblBufferObject()->SetColor(fColor, BLACK);
		DblBufferObject()->SetCursorPos(nPosX, nPoxY);
		DblBufferObject()->Write("-oOMOo-");
	}

	//	��
	for (int i = 0; i < MAX_FIREWORKS; i++)
	{
		nPosX = (int)g_snow[i].fPosX;
		nPoxY = (int)g_snow[i].fPosY;


		if (nPosX < 0 || nPosX >= CON_WIDTH - 1 || nPoxY < 0 || nPoxY >= CON_HEIGHT - 2)
		{
			continue;
		}
		DblBufferObject()->SetColor(WHITE, BLACK);
		DblBufferObject()->SetCursorPos(nPosX, nPoxY);
		DblBufferObject()->Write("*");
		DblBufferObject()->SetCursorPos(nPosX - 1, nPoxY + 1);
		DblBufferObject()->Write("* *");
		DblBufferObject()->SetCursorPos(nPosX, nPoxY + 2);
		DblBufferObject()->Write("*");

	}
}

//======================================================================
//	�p�[�e�B�N���̈ړ�����
//�@����:�Ȃ�
//	�߂�l:�������Ă���p�[�e�B�N���̐�
//======================================================================
int Move()
{
	int nLife = MAX_FIREWORKS;
	for (int i = 0; i < MAX_FIREWORKS; i++)
	{
		////////////////////////////////////	
		if (g_fireworks[i].bAvctive)
		{
			if (g_fireworks[i].fVy < 3)
			{
				g_fireworks[i].fPosX += g_fireworks[i].fVx;
				g_fireworks[i].fPosY += g_fireworks[i].fVy;
				g_fireworks[i].fVy += GRAVITY;
			}
			g_fireworks[i].nLifeCnt--;
			if (g_fireworks[i].nLifeCnt == 0)
			{
				g_fireworks[i].bAvctive = false;

			}
		}
		/////////////////////////////////////
		if (g_snow[i].bAvctive)
		{
			g_snow[i].angle += 10;
			g_snow[i].fPosX += cosf(g_snow[i].angle*PI / 180) * 1.5;
				g_snow[i].fPosY += g_snow[i].fVy;
				//g_snow[i].fVy += GRAVITY;
			g_snow[i].nLifeCnt--;
			if (g_snow[i].nLifeCnt == 0)
			{
				g_snow[i].bAvctive = false;

			}
		}
	}
	for (int i = 0; i < MAX_TREE; i++)
	{
		////////////////////////////////////
		if (g_tree[i].bAvctive)
		{
			if (g_tree[i].fStart == g_tree[i].fEnd)
			{
				g_tree[i].fEnd = g_tree[i].fEnd / 2;
				g_tree[i].fStart = 0;
				g_tree[i].level++;
				g_tree[i].angle = FractalBinaryTree(i, g_tree[i].level, g_tree[i].angle);
				g_tree[i].fDirection = g_tree[i].angle*PI / 180;
				g_tree[i].fVx = cos(g_tree[i].fDirection)*2;
				g_tree[i].fVy = sin(g_tree[i].fDirection);
			}
			g_tree[i].fPosX -= g_tree[i].fVx;
			g_tree[i].fPosY -= g_tree[i].fVy;
			g_tree[i].fStart++;

			g_tree[i].nLifeCnt--;
			if (g_tree[i].nLifeCnt == 0)
			{
				g_tree[i].bAvctive = false;

			}
		}
	}
	for (int i = MAX_FIREWORKS*g_fireCnt; i < MAX_FIREWORKS*(g_fireCnt + 1); i++)
	{
		////////////////////////////////////	
		if (!g_fireworks1[i].nLifeCnt)
		{
			nLife--;
			continue;
		}
		if (g_fireworks1[i].fVy < 2)
		{

			g_fireworks1[i].fPosX += g_fireworks1[i].fVx;
			g_fireworks1[i].fPosY += g_fireworks1[i].fVy;
			g_fireworks1[i].fVy += GRAVITY;
		}
		g_fireworks1[i].nLifeCnt--;
	}
	return nLife > 0;
}

//======================================================================
//	�񕪖�
//�@����:n		���q�̃C���f�N�X
//		 lv		�[��
//		 angle�@�p�x
//	�߂�l:���̊p�x
//======================================================================
float FractalBinaryTree(int n, int lv,float angle)
{
	//	������
	int tmpi = n &(1 << lv - 1);
	if (tmpi==0)
	{
		angle -= 45;
	}
	else
	{ 
		angle += 45;
	}
	return angle;
}

