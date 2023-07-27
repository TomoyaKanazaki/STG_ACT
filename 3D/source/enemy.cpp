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

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CEnemy::m_nCntEnemy = 0;

//==========================================
//  �}�N����`
//==========================================
#define SPEED (2.0f) //�ړ����x
#define DETECTION (700.0f) //���G�͈�

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

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	if (m_ppModel == NULL)
	{
		m_ppModel = new CModel*[m_pLayer->nNumModel];
	}

	//�K�v�ȃ��f���𐶐�
	for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
	{
		//��ɂ���
		m_ppModel[nCnt] = NULL;

		//�e�����݂��Ȃ��ꍇ
		if (m_pLayer->pParentID[nCnt] == -1)
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt]);
		}
		else
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt], m_ppModel[m_pLayer->pParentID[nCnt]]);
		}
	}

	//���[�V�������̐���
	while (1)
	{
		if (m_pMotion == NULL)
		{
			m_pMotion = new CMotion;

			//���[�V�������Ƀ��f����ǉ�����
			m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_SHOT);
		}
		else
		{
			break;
		}
	}

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

	//���[�V�����̃|�C���^��j��
	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	//�ړ��̏���
	Move();

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

	//���[�V�������X�V����
	if (m_pMotion != NULL)
	{
		m_pMotion->Update();
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
		pEnemy = new CEnemy;
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
//  �ړ�����
//==========================================
void CEnemy::Move(void)
{
	//�����ɂ��ړ��̒�~
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 posTarget = CGameManager::GetPlayer()->GetPos();

	//�v���C���[�Ɍ������x�N�g�����Z�o
	posTarget -= m_pos;

	//�v���C���[�Ƃ̋������߂��ꍇ
	if (posTarget.x * posTarget.x + posTarget.z * posTarget.z < DETECTION * DETECTION)
	{
		//Y���W�ւ̕␳���폜����
		posTarget.y = 0.0f;

		//�x�N�g���̐��K��
		D3DXVec3Normalize(&posTarget, &posTarget);

		//�ړ��ʂ�␳���ēK�p
		m_move = posTarget * SPEED;
	}
}
