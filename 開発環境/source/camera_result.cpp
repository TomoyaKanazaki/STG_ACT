//==========================================
//
//  ���U���g�J�����N���X(camera_result.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_result.h"
#include "manager.h"
#include "debugproc.h"
#include "object_fan.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CCameraResult::CCameraResult()
{
	m_fAngle = 0.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CCameraResult::~CCameraResult()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCameraResult::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return CCamera::Init();
}

//==========================================
//  �X�V����
//==========================================
void CCameraResult::Update(void)
{
	FirstPerson();
}
