#ifndef _DBLBUFFER_H
#define _DBLBUFFER_H
#pragma once
//=============================================
//	C����@�_�u���o�b�t�@(DoubleBuffer)
//  �R���\�[���T�C�Y�� 160px * 100px
//�@�t�H���g�T�C�Y��18�A1������ 9px * 18px
//
//	OH_AT51A715_09_�d �C��(�z�E	�J�C�g�E)
//								2017-11-01
//	SuperDoubleBuffer		
//	��ʉ𑜓x���Œ肵���I�I�I
//								2017-11-17	
//=============================================
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

//	�}�N���̒�`
//	Windows�T�C�Y
#define SCREEN_SIZE_X 400
#define SCREEN_SIZE_Y 320
 
enum COLORSC {
	BLACK = 0,			//	��		
	BLUE = 1,			//	�Z����	
	GREEN = 2,			//	��		
	CYAN = 3, 			//	��		
	RED = 4,			//	�Z����	
	MAGENTA = 5,		//	��		
	BROWN = 6,			//	�Z����	
	LIGHTGRAY = 7,		//	25%�D�F	
	GRAY = 8,			//	50%�D�F	
	LIGHTBLUE = 9,		//	��		
	LIGHTGREEN = 10,	//	���邢��	
	LIGHTCYAN = 11,		//	���F		
	LIGHTRED = 12,		//	 ��		
	LIGHTMAGENTA = 13,	//	�}�[���^	
	YELLOW = 14,		//	��	
	WHITE = 15,			//	��		
	INTENSITY = 0x08,	//	���P�x�}�X�N
	RED_MASK = 0x04,
	GREEN_MASK = 0x02,
	BLUE_MASK = 0x01,
};
//	�_�u���o�b�t�@�̍\����
typedef struct tagDblBuffer
{
	void(*CreatHandle)();
	void(*Close)();

	void(*SetColor)(int, int);
	void(*SetCursorPos)(int, int);
	void(*Write)(const char *);
	void(*ClearScreen)(int);
	void(*Swap)();
	HANDLE(*GetHandle)();
}*DblBuffer;

DblBuffer DblBufferObject();
  
#endif // _DBLBUFFER_H