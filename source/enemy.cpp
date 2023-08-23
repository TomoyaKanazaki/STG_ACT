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

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CEnemy::m_nCntEnemy = 0;

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
	m_nCntEnemy++;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy::~CEnemy()
{
	m_nCntEnemy--;
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

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	//�ړ��ʂ̓K�p
	m_pos += m_move;

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
