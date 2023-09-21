//==========================================
//
//  �^�C�g���J�����N���X(camera_title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_title.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CCameraTitle::CCameraTitle()
{
	m_fAngle = 0.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CCameraTitle::~CCameraTitle()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCameraTitle::Init(void)
{
	return CCamera::Init();
}

//==========================================
//  �X�V����
//==========================================
void CCameraTitle::Update(void)
{
	//�p�x���X�V
	m_fAngle += 0.01f;


	//�p�x�̕␳
	if (m_fAngle > D3DX_PI)
	{
		m_fAngle = -D3DX_PI;
	}
	if (m_fAngle < -D3DX_PI)
	{
		m_fAngle = D3DX_PI;
	}

}
