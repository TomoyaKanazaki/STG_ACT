//==========================================
//
//  �}�l�[�W���N���X(manager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"

//==========================================
//  �}�N����`
//==========================================
#define MAX_PLAYER (4) //�v���C���[�̍ő吔

//==========================================
//  �O���錾
//==========================================
class CRenderer;
class CKeyboard;
class CMouse;
class CJoyPad;
class CDebugProc;
class CPause;
class CSound;
class CTexture;
class CSceneManager;

//==========================================
//  �}�l�[�W���N���X��`
//==========================================
class CManager
{
public:
	CManager(); //�R���X�g���N�^
	~CManager(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CKeyboard *GetKeyboard(void) { return m_pKeyboard; }
	static CMouse *GetMouse(void) { return m_pMouse; }
	static CJoyPad *GetJoyPad(void) { return m_pJoyPad; }
	static CDebugProc *GetDebugProc(void) { return m_pDebugProc; }
	static CPause *GetPause(void) { return m_pPause; }
	static CSound *GetSound(void) { return m_pSound; }
	static CTexture *GetTexture(void) { return m_pTexture; }
	static CSceneManager *GetSceneManager(void) { return m_pSceneManager; }
	static int GetFPS(void) { return m_nFPS; }
	static void SetFPS(int nFPS) { m_nFPS = nFPS; }

private:

	//�ÓI�����o�ϐ�
	static CRenderer *m_pRenderer;
	static CKeyboard *m_pKeyboard;
	static CMouse *m_pMouse;
	static CJoyPad *m_pJoyPad;
	static CDebugProc *m_pDebugProc;
	static CPause *m_pPause;
	static CSound *m_pSound;
	static CTexture *m_pTexture;
	static CSceneManager *m_pSceneManager;
	static int m_nFPS;

	//�����o�ϐ�
	HINSTANCE m_Instance; HWND m_Wnd; BOOL m_Window;

};

#endif
