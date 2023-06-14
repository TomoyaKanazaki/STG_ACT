//==========================================
//
//  �I�u�W�F�N�g�N���X(object.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "pause.h"
#include "camera.h"
#include "debugproc.h"
#include "effect.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CObject *CObject::m_apObject[PRIORITY_NUM][MAX_OBJECT] = {};
int CObject::m_nNumObject = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CObject::CObject(int nPriority)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == NULL)
		{
			m_apObject[nPriority][nCntObject] = this;
			m_nID = nCntObject;
			m_nNumObject++;
			break;
		}
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nPriority = nPriority;
	m_type = TYPE_NONE;
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
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Uninit();
			}
		}
	}
}

//==========================================
//  �S�I�u�W�F�N�g�̍X�V
//==========================================
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				if (CManager::GetPause()->GetState() == false || m_apObject[nCntPriority][nCntObject]->m_type == CObject::TYPE_TIMER)
				{
					m_apObject[nCntPriority][nCntObject]->Update();
				}
			}
		}
	}
}

//==========================================
//  �S�I�u�W�F�N�g�̕`��
//==========================================
void CObject::DrawAll(void)
{
	//�J�����̎擾
	CCamera *pCamera = CManager::GetCamera();

	//�J�����̐ݒ�
	pCamera->SetCamera();

	CManager::GetDebugProc()->Print("�I�u�W�F�N�g�� : %d\n", m_nNumObject);
	CManager::GetDebugProc()->Print("�G�t�F�N�g�� : %d\n", CEffect::GetNum());

	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Draw();
			}
		}
	}
}

//==========================================
//  �P�̂̔j��
//==========================================
void CObject::Release(void)
{
	//�D�揇�ʂ�ۑ�
	int nPriority = m_nPriority;

	//�C���f�b�N�X��ۑ�
	int nIdx = m_nID;

	if (m_apObject[nPriority][nIdx] != NULL)
	{
		delete m_apObject[nPriority][nIdx];
		m_apObject[nPriority][nIdx] = NULL;
		m_nNumObject--;
	}
}
