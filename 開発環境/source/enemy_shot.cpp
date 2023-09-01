//==========================================
//
//  �e�����G�̃N���X(enemy_shot.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_shot.h"
#include "gamemanager.h"
#include "player.h"
#include "bullet.h"
#include "manager.h"
#include "input.h"
#include "model.h"
#include "motion.h"
#include "manager.h"
#include "camera.h"
#include "target.h"
#include "rockon.h"

//==========================================
//  �}�N����`
//==========================================
#define SPEED (3.0f) //�e�̑��x
#define INTERVAL (60) //�e�̔��ˊԊu

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyShot::CEnemyShot()
{
	m_nInterval = 0;
	m_pRockon = NULL;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyShot::~CEnemyShot()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyShot::Init(void)
{
	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::ENEMY_SHOT_LAYER);

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

	CEnemy::Init();
	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemyShot::Uninit(void)
{
	if (m_pRockon != NULL)
	{
		m_pRockon->Uninit();
	}
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyShot::Update(void)
{
	//�e�̔��ˎ��Ԃ��X�V
	m_nInterval++;

	//�e�̔��˂Ɋւ��鏈��
	Shot();

	//�_����
	Targeted();

	//���[�V�������X�V����
	if (m_pMotion != NULL)
	{
		m_pMotion->Update();
	}

	//�X�V
	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemyShot::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  �e��������
//==========================================
void CEnemyShot::Shot(void)
{
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//��������v���C���[�Ɍ������x�N�g�����Z�o
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;

	//�Z�o�����x�N�g������p�x���Z�o
	float rotVector = atan2f(vecToPlayer.z, -vecToPlayer.x);

	//�Z�o�����p�x�������̕����ɂ���
	m_rot.y = rotVector;

	//�Z�o�����x�N�g���𐳋K������
	vecToPlayer.y = 0.0f;
	D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

	//�v���C���[�ւ̃x�N�g���ɔ{���^����
	vecToPlayer *= SPEED;

	//������^����
	D3DXVECTOR3 pos = m_pos;
	pos.y += 10.0f;

	//�e������
	if (m_nInterval % INTERVAL == 0)
	{
		CBullet::Create(pos, D3DXVECTOR3(25.0f, 25.0f, 0.0f), vecToPlayer, CBullet::ENEMY, CBullet::NORMAL_BULLET);
	}
}

//==========================================
//  �_���鏈��
//==========================================
void CEnemyShot::Targeted(void)
{
	//��������t���O
	bool bIn = false;

	//�r���[�|�[�g�̐ݒ�
	D3DVIEWPORT9 vp = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f };

	//�v�Z�p�ϐ��錾
	D3DXMATRIX mtxView = CGameManager::GetCamera()->CreateViewMatrix(); //�r���[�}�g���b�N�X
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�G�̃X�N���[�����W���Z�o
	D3DXVECTOR3 screenPos;
	D3DXMATRIX mtxProjection = CGameManager::GetCamera()->GetMtxPro();
	D3DXVec3Project
	(
		&screenPos,
		&m_pos,
		&vp,
		&mtxProjection,
		&mtxView,
		&mtxWorld
	);

	//�͈͓��̔���
	if (screenPos.x < CGameManager::GetTarget()->GetPos().x + CGameManager::GetTarget()->GetSize().x * 0.5f && !bIn)
	{
		if (screenPos.x > CGameManager::GetTarget()->GetPos().x - CGameManager::GetTarget()->GetSize().x * 0.5f && !bIn)
		{
			if (screenPos.y < CGameManager::GetTarget()->GetPos().y + CGameManager::GetTarget()->GetSize().y * 0.5f && !bIn)
			{
				if (screenPos.y > CGameManager::GetTarget()->GetPos().y - CGameManager::GetTarget()->GetSize().y * 0.5f && !bIn)
				{
					if (m_pRockon == NULL)
					{
						m_pRockon = CRockon::Create(m_pos);
					}
					bIn = true;
				}
			}
		}
	}

	if(!bIn)
	{
		if (m_pRockon != NULL)
		{
			m_pRockon->Uninit();
			m_pRockon = NULL;
		}
	}
}
