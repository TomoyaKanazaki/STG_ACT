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
	static CJoyPad *GetJoyPad(int nNum) { return m_pJoyPad[nNum]; }
	static CDebugProc *GetDebugProc(void) { return m_pDebugProc; }

private:

	//�ÓI�����o�ϐ�
	static CRenderer *m_pRenderer;
	static CKeyboard *m_pKeyboard;
	static CMouse *m_pMouse;
	static CJoyPad *m_pJoyPad[MAX_PLAYER];
	static CDebugProc *m_pDebugProc;
};

#endif
