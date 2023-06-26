//==========================================
//
//  プリコンパイルヘッダ(precompile.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PRECOMPILE_H_
#define _PRECOMPILE_H_

#include <Windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800) //ビルド時の警告対処用マクロ
#include "dinput.h"
#include <stdio.h>
#include "xaudio2.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
//#define CHECK_MEM_LEAK
#endif // _DEBUG

//普段使用禁止
#ifdef CHECK_MEM_LEAK
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif // CHECK_MEM_LEAK

#endif
