//==========================================
//
//  ゲーム全般の制御(main.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MAIN_H_
#define _MAIN_H_
#include <Windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800) //ビルド時の警告対処用マクロ
#include "dinput.h"
#include <stdio.h>
#include "xaudio2.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define CHECK_MEM_LEAK
#endif // _DEBUG

//普段使用禁止
#ifdef CHECK_MEM_LEAK
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif // CHECK_MEM_LEAK

//==========================================
//  ライブラリのリンク
//==========================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

//==========================================
//  マクロ定義
//==========================================
#define SCREEN_WIDTH (1280) //ウィンドウの幅
#define SCREEN_HEIGHT (720) //ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "C++始まった!!!"

//==========================================
//  頂点座標[2D]の構造体を定義
//==========================================
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;

//==========================================
//  頂点座標[3D]の構造体を定義
//==========================================
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	D3DXVECTOR3 nor; //法線ベクトル
	D3DCOLOR col; //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
}VERTEX_3D;

#endif
