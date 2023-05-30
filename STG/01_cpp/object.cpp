//==========================================
//
//  �I�u�W�F�N�g�N���X(object.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object.h"
#include "renderer.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CObject *CObject::m_apObject[MAX_OBJECT] = {};
int CObject::m_nNumObject = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CObject::CObject()
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = this;
			m_nID = nCntObject;
			m_nNumObject++;
			break;
		}
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================
//  �f�X�g���N�^
//==========================================
CObject::~CObject()
{

}

//==========================================
//  �S�I�u�W�F�N�g�̔j��
//==========================================
void CObject::ReleaseAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Uninit();
		}
	}
}

//==========================================
//  �S�I�u�W�F�N�g�̍X�V
//==========================================
void CObject::UpdateAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Update();
		}
	}
}

//==========================================
//  �S�I�u�W�F�N�g�̕`��
//==========================================
void CObject::DrawAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Draw();
		}
	}
}

//==========================================
//  �P�̂̔j��
//==========================================
void CObject::Release(void)
{
	//�C���f�b�N�X��ۑ�
	int nIdx = m_nID;

	if (m_apObject[nIdx] != NULL)
	{
		delete m_apObject[nIdx];
		m_apObject[nIdx] = NULL;
		m_nNumObject--;
	}
}
