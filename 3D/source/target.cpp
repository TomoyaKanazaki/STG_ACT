//==========================================
//
//  �^�[�Q�b�g�N���X(target.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "target.h"
#include "manager.h"
#include "texture.h"

CTarget::CTarget()
{
}

CTarget::~CTarget()
{
}

HRESULT CTarget::Init(void)
{
	return E_NOTIMPL;
}

void CTarget::Uninit(void)
{
}

void CTarget::Update(void)
{
}

void CTarget::Draw(void)
{
}

CTarget * CTarget::Create(const D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CTarget *pTarget = NULL;

	//NULL�`�F�b�N
	if (pTarget == NULL)
	{
		//���������m��
		pTarget = new CTarget;
	}

	if (pTarget == NULL)
	{
		return NULL;
	}

	//������
	pTarget->Init();

	//�e�N�X�`�������蓖�Ă�
	pTarget->BindTexture(CManager::GetTexture()->GetAddress(1));

	//�|�C���^��Ԃ�
	return pTarget;
}
