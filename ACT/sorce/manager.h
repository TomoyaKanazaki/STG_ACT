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
class CScore;
class CTimer;
class CSound;

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
	static CRenderer *GetRenderer() { return m_pRenderer; }
	static CKeyboard *GetKeyboard() { return m_pKeyboard; }
	static CMouse *GetMouse() { return m_pMouse; }
	static CJoyPad *GetJoyPad(int m_nNum) { return m_pJoyPad[m_nNum]; }
	static CDebugProc *GetDebugProc(void) { return m_pDebugProc; }
	static CPause *GetPause(void) { return m_pPause; }
	static CScore *GetScore(void) { return m_pScore; }
	static CTimer *GetTimer(void) { return m_pTimer; }
	static CSound *GetSound(void) { return m_pSound; }

private:

	//�ÓI�����o�ϐ�
	static CRenderer *m_pRenderer;
	static CKeyboard *m_pKeyboard;
	static CMouse *m_pMouse;
	static CJoyPad *m_pJoyPad[MAX_PLAYER];
	static CDebugProc *m_pDebugProc;
	static CPause *m_pPause;
	static CScore *m_pScore;
	static CTimer *m_pTimer;
	static CSound *m_pSound;

};

#endif
