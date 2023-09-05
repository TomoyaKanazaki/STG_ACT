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
//  �_���鏈��
//==========================================
void CEnemyShot::Targeted(void)
{
	//��������t���O
	bool bIn = false;

	//�J�[�\���ʒu���擾����
	D3DXVECTOR3 posTarget = CGameManager::GetTarget()->GetPos();

	//�J�[�\���܂ł̋����𔻒�
	float fLength =
		(posTarget.x - m_pos.x) * (posTarget.x - m_pos.x) + (posTarget.z - m_pos.z) * (posTarget.z - m_pos.z);

	//�͈͓��̔���
	if (CGameManager::GetTarget()->GetSize().x * CGameManager::GetTarget()->GetSize().x * 0.64f > fLength)
	{
		if (m_pRockon == NULL)
		{
			m_pRockon = CRockon::Create(m_pos);
		}
		bIn = true;
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
