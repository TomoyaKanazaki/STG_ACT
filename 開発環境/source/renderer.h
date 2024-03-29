//==========================================
//
//  レンダラークラス(renderer.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

//==========================================
//  前方宣言
//==========================================
class CUi;

//==========================================
//  レンダラークラス定義
//==========================================
class CRenderer
{
public:
	CRenderer(); // コンストラクタ
	~CRenderer();// デストラクタ

	// メンバ関数
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }
	
	//静的メンバ関数
	static CUi *GetUi(void) { return m_pUi; }

private:

	// メンバ変数
	LPDIRECT3D9 m_pD3D; // Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice; // Direct3Dデバイスへのポインタ

	//静的メンバ変数
	static CUi *m_pUi;

};

#endif
