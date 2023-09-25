//==========================================
//
//  ���ʂ̓G(enemy_normal.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_normal.h"
#include "model.h"
#include "motion.h"
#include "input.h"
#include "collision.h"
#include "gamemanager.h"
#include "object_fan.h"
#include "player.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy_Normal::CEnemy_Normal(int nPriority) : CEnemy(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy_Normal::~CEnemy_Normal()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy_Normal::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(CObject::TYPE_NORMAL_ENEMY);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::NORMAL_LAYER);

	//���f���p�̃������̊m��
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
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
	}

	CEnemy::Init();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemy_Normal::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy_Normal::Update(void)
{
	//�ړ��̏���
	if (CGameManager::GetFan()->OnMesh(m_pos))
	{
		if (this->GetType() == CObject::TYPE_NORMAL_ENEMY) //�v���C���[�ǂ�����
		{
			//�ړ�
			Move();

			//�v���C���[��e��
			if (Collision::CollisionPlayer(m_pos, 30.0f))
			{
				CGameManager::GetPlayer()->SetMove(m_move * 10.0f);
			}
		}
		else
		{
			//�����ɂ��ړ��̒�~
			m_move.x += (0.0f - m_move.x) * 0.1f;
			m_move.z += (0.0f - m_move.z) * 0.1f;

			//�A���̔���
			Chain();

			//���Ԃ̃J�E���g
			m_nCntBullet++;

			//��莞�Ԍo�߂œG�ɖ߂�
			if (m_nCntBullet >= 30 || (fabsf(m_move.x) <= 0.1f && fabsf(m_move.z) <= 0.1f))
			{
				m_nCntBullet = 0;
				this->SetType(CObject::TYPE_NORMAL_ENEMY);
			}
		}
	}

	//�����痎����
	if (!CGameManager::GetFan()->OnMesh(m_pos))
	{
		m_move.y -= 1.0f;
	}

	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy_Normal::Draw(void)
{
	CEnemy::Draw();
}
