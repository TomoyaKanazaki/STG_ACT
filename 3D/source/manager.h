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
class CPause;
class CScore;
class CTimer;
class CSound;
class CCamera;
class CLight;
class CPlayer;
class CTexture;
class CField;
class CObject_Fan;

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
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CKeyboard *GetKeyboard(void) { return m_pKeyboard; }
	static CMouse *GetMouse(void) { return m_pMouse; }
	static CJoyPad *GetJoyPad(void) { return m_pJoyPad; }
	static CDebugProc *GetDebugProc(void) { return m_pDebugProc; }
	static CPause *GetPause(void) { return m_pPause; }
	static CScore *GetScore(void) { return m_pScore; }
	static CTimer *GetTimer(void) { return m_pTimer; }
	static CSound *GetSound(void) { return m_pSound; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CTexture *GetTexture(void) { return m_pTexture; }
	static CField *GetField(void) { return m_pField; }
	static CObject_Fan *GetFan(void) { return m_pFan; }

private:

	//静的メンバ変数
	static CRenderer *m_pRenderer;
	static CKeyboard *m_pKeyboard;
	static CMouse *m_pMouse;
	static CJoyPad *m_pJoyPad;
	static CDebugProc *m_pDebugProc;
	static CPause *m_pPause;
	static CScore *m_pScore;
	static CTimer *m_pTimer;
	static CSound *m_pSound;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CPlayer *m_pPlayer;
	static CTexture *m_pTexture;
	static CField *m_pField;
	static CObject_Fan *m_pFan;

};

#endif
