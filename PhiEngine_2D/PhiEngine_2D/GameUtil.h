//======================================================================
//!	@file	GameUtil.h
//!	@brief	Utility
//!	@note	
//!	@author	�d�C��	2018-07-09
//======================================================================
#ifndef _GAMEUTIL_H
#define _GAMEUTIL_H
#pragma once

#include	<Windows.h>
#include	<stdio.h>
#include	<process.h>
#include	<thread>
#include	<crtdbg.h>
#include	<d3d9.h>
#include	<d3dx9.h>
#include	"input.h"

//**********************************************************************
//	�����N���C�u�����̐ݒ�
//**********************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")

//**********************************************************************
//	�}�N����`
//**********************************************************************
#define		SCREEN_WIDTH	640
#define		SCREEN_HEIGHT	480
#define		PI				3.14159265f

//	�V�[�����
typedef enum
{
	SceneTitle,		//	�^�C�g��
	SceneMenu,		//	���j���[
	SceneRun,		//	�Q�[��
	SceneEnd		//	�I��
}SceneType;

//SceneType g_GameState;

#endif