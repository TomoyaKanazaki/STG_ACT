//==========================================
//
//  �G�l�~�[�N���X(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <windows.h>
#include "enemy.h"
#include "player.h"
#include "gamemanager.h"
#include "renderer.h"
#include "effect.h"
#include "sound.h"
#include "debugproc.h"
#include "model.h"
#include "shadow.h"
#include "motion.h"
#include "item.h"
#include "motion.h"
#include "enemy_approach.h"
#include "enemy_shot.h"
#include "particle.h"
#include "boss.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CEnemy::m_nDead = 0;
const float CEnemy::mc_fSize = 75.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_fSpeed = 0.0f;
	m_ppModel = NULL;
	m_pLayer = NULL;
	m_pShadow = NULL;
	m_pMotion = NULL;
	m_bRand = true;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(CObject::TYPE_ENEMY);

	//�e�𐶐�
	if (m_pShadow == NULL)
	{
		m_pShadow = CShadow::Create(m_pos, m_size, m_rot);
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemy::Uninit(void)
{
	//���f���̃|�C���^��j��
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->Uninit();
				m_ppModel[nCnt] = NULL;
			}
		}
		delete[] m_ppModel;
		m_ppModel = NULL;
	}

	//�e�̃|�C���^��j��
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
	}

	//�p�[�e�B�N�����Ăяo��
	CParticle::Create(m_pos, D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(0.98f, 0.87f, 0.28f, 0.5f), 10, 30, 10, 5);

	//�������g�̔j��
	Release();

	//���j�������Z
	m_nDead++;
}

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	//���̂��ړ�����
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				if (m_ppModel[nCnt]->GetParent() == NULL)
				{
					m_ppModel[nCnt]->SetTransform(m_pos, m_rot);
				}
			}
		}
	}

	//�e�̏����X�V����
	if (m_pShadow != NULL)
	{
		m_pShadow->SetTransform(m_pos, m_rot);
	}
	else
	{
		//�Đ���
		m_pShadow = CShadow::Create(m_pos, m_size, m_rot);
	}

	//�ړ��ʂ̓K�p
	m_pos += m_move;
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy::Draw()
{

}

//==========================================
//  �I�u�W�F�N�g��������
//==========================================
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, CEnemy::TYPE type)
{
	//�C���X�^���X����
	CEnemy *pEnemy = NULL;

	//NULL�`�F�b�N
	if (pEnemy == NULL)
	{
		//���������m��
		switch (type)
		{
		case CEnemy::TYPE_NORMAL:

			pEnemy = new CEnemyApproach;
			break;

		case CEnemy::TYPE_SHOT:

			pEnemy = new CEnemyShot;
			break;

		case CEnemy::TYPE_BOSS:

			pEnemy = new CBoss;
			break;

		default:
			return NULL;
			break;
		}
	}

	//�e����̕ۑ�
	pEnemy->m_pos = pos;
	pEnemy->m_size = size;
	pEnemy->m_rot = rot;

	//������
	if (pEnemy != NULL)
	{
		pEnemy->Init();
	}

	//�|�C���^��Ԃ�
	return pEnemy;
}

//==========================================
//  �G���m���Ԃ��锻��
//==========================================
void CEnemy::AvertEnemy(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�����̃A�h���X���擾
		CObject *pObj = this->GetNext();

		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject *pNext = pObj->GetNext();

			if (pObj->GetType() != CObject::TYPE_ENEMY) //�G�̏ꍇ
			{
				pObj = pNext;
				continue;
			}

			//���݂̓G�Ǝ��������ԃx�N�g�����擾����
			D3DXVECTOR3 posObj = pObj->GetPos();
			D3DXVECTOR3 vecToObj = m_pos - posObj;

			//�x�N�g���̑傫�����Z�o
			float fLength = (vecToObj.x * vecToObj.x) + (vecToObj.z * vecToObj.z);

			//�ڐG�͈͓��ɂ����ꍇ
			if (fLength < mc_fSize * mc_fSize)
			{
				//�ړ_���W�����߂�
				D3DXVECTOR3 contact = (posObj + m_pos) * 0.5f;

				//�x�N�g���̊p�x�����߂�
				float rotVector = atan2f(vecToObj.x, vecToObj.z);

				//x,z�̕␳�l�����߂�
				D3DXVECTOR2 correction = { sinf(rotVector), cosf(rotVector) };

				//���W��␳����
				m_pos.x = correction.x * (mc_fSize * 0.5f) + contact.x;
				m_pos.z = correction.y * (mc_fSize * 0.5f) + contact.z;
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}
}
