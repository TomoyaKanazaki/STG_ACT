//==========================================
//
//  �Q�[���S�ʂ̐���(main.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MAIN_H_
#define _MAIN_H_
#include <Windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800) //�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"
#include <stdio.h>
#include "xaudio2.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define CHECK_MEM_LEAK
#endif // _DEBUG

//���i�g�p�֎~
#ifdef CHECK_MEM_LEAK
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif // CHECK_MEM_LEAK

//==========================================
//  ���C�u�����̃����N
//==========================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

//==========================================
//  �}�N����`
//==========================================
#define SCREEN_WIDTH (1280) //�E�B���h�E�̕�
#define SCREEN_HEIGHT (720) //�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "C++�n�܂���!!!"

//==========================================
//  ���_���W[2D]�̍\���̂��`
//==========================================
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;

//==========================================
//  ���_���W[3D]�̍\���̂��`
//==========================================
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_3D;

#endif
