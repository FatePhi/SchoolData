//======================================================================
//!	@file	polygon.h
//!	@brief	
//!	@note	Polygon�`��
//!	@author	�d�C��	2018-06-22
//======================================================================
#pragma once
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include	<d3dx9.h>
// ���_�f�[�^�t�H�[�}�b�g
typedef struct tagVERTEX2D
{
	float x, y, z;
	float u, v;
}VERTEX2D;


void Draw2dPolygon(LPDIRECT3DDEVICE9 lpdevice,  LPDIRECT3DTEXTURE9* tex);
LPDIRECT3DTEXTURE9* LoadTexture(LPDIRECT3DDEVICE9 lpdevice,LPCWSTR, LPDIRECT3DTEXTURE9 *);
bool ReleaseTexture(LPDIRECT3DTEXTURE9 *);

void MovePolygon(float x, float y, float angle, float sx, float sy);
#endif

