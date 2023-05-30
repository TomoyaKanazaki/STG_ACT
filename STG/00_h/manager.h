//==========================================
//
//  マネージャクラス(manager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"

//==========================================
//  マクロ定義
//==========================================
#define MAX_PLAYER (4) //プレイヤーの最大数

//==========================================
//  前方宣言
//==========================================
class CRenderer;
class CKeyboard;
class CMouse;
class CJoyPad;
class CDebugProc;

//==========================================
//  マネージャクラス定義
//==========================================
class CManager
{
public:
	CManager(); //コンストラクタ
	~CManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static CRenderer *GetRenderer() { return m_pRenderer; }
	static CKeyboard *GetKeyboard() { return m_pKeyboard; }
	static CMouse *GetMouse() { return m_pMouse; }
	static CJoyPad *GetJoyPad(int nNum) { return m_pJoyPad[nNum]; }
	static CDebugProc *GetDebugProc(void) { return m_pDebugProc; }

private:

	//静的メンバ変数
	static CRenderer *m_pRenderer;
	static CKeyboard *m_pKeyboard;
	static CMouse *m_pMouse;
	static CJoyPad *m_pJoyPad[MAX_PLAYER];
	static CDebugProc *m_pDebugProc;
};

#endif
