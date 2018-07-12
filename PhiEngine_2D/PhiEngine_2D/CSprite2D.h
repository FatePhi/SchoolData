//*****************************************************************************
//!	@file	CSprite2D.cpp
//!	@brief	2DSprite�����N���X
//!	@note	
//!	@author	�d�C��	2018-07-09
//*****************************************************************************
#pragma once
#ifndef _CSPRITE2D_H_
#define _CSPRITE2D_H_

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include	"GameUtil.h"
#include	"MathUtil.h"

//-----------------------------------------------------------------------------
//	�\���̒�`
//-----------------------------------------------------------------------------

// ���_�f�[�^�t�H�[�}�b�g
typedef struct tagVERTEX2D
{
	float x, y, z;
	float u, v;
}VERTEX2D;

//=============================================================================
//!	@class	CSprite2D
//!	@brief	CSprite2D�N���X
//=============================================================================
class CSprite2D
{
private:
	VERTEX2D			m_v[4];			//	

	D3DXMATRIX			m_Mat;			//	�ϊ��s��
	D3DXMATRIX			m_MatTotal;		//	�ώZ�s��

	D3DXVECTOR3			m_rotation;		//	��]�p�x
	D3DXVECTOR3			m_position;		//	�ړ���
	D3DXVECTOR3			m_scale;		//	�X�P�[����

	LPDIRECT3DTEXTURE9*	m_tex;			//	�e�N�X�`��
	bool				m_isActive;		//	

public:
	CSprite2D(){}						//	�R���X�g���N�^
	~CSprite2D(){}						//	�f�X�g���N�^

	void Init(LPDIRECT3DDEVICE9 lpdev, LPCWSTR filename, D3DXVECTOR3& position, D3DXVECTOR3& rotation, D3DXVECTOR3& scale);

	void Update(LPDIRECT3DDEVICE9 lpdev);

	void Draw(LPDIRECT3DDEVICE9 lpdev);
	
	void Exit();

};


//*****************************************************************************
//	End of file.
//*****************************************************************************
#endif