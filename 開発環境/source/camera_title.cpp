//==========================================
//
//  �^�C�g���J�����N���X(camera_title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_title.h"
#include "manager.h"
#include "debugproc.h"
#include "object_fan.h"

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
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return CCamera::Init();
}

//==========================================
//  �X�V����
//==========================================
void CCameraTitle::Update(void)
{
	FirstPerson();
}
