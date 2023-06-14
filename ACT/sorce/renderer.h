//==========================================
//
//  �����_���[�N���X(renderer.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

//==========================================
//  �����_���[�N���X��`
//==========================================
class CRenderer
{
public:
	CRenderer(); // �R���X�g���N�^
	~CRenderer();// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:

	// �����o�ϐ�
	LPDIRECT3D9 m_pD3D; // Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice; // Direct3D�f�o�C�X�ւ̃|�C���^

};

#endif