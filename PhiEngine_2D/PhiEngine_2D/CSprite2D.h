//*****************************************************************************
//!	@file	CSprite2D.cpp
//!	@brief	2DSprite�����N���X
//!	@note	
//!	@author	�d�C��	2018-07-09
//*****************************************************************************
#pragma once
#ifndef _CSPRITE2D_H_
#define _CSPRITE2D_H_

#include	"GameUtil.h"



class CSprite2D
{
private:
	D3DXMATRIX		m_Mat;				//	�ϊ��s��
	D3DXMATRIX		m_MatTotal;			//	�ώZ�s��

	D3DXVECTOR3		m_angle;			//	��]�p�x
	D3DXVECTOR3		m_trans;			//	�ړ���

	LPDIRECT3DTEXTURE9* m_tex;			//	�e�N�X�`��
	bool			m_isActive;			//	

public:
	CSprite2D(LPCWSTR filename);
	~CSprite2D();

	void Init(LPDIRECT3DDEVICE9 lpdev);

	void Update(LPDIRECT3DDEVICE9 lpdev);

	void Draw(LPDIRECT3DDEVICE9 lpdev);
	
	void Exit();

};



#endif