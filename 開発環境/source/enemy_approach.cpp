//==========================================
//
//  �t���Ă���G�̃N���X(enemy_approach.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_approach.h"
#include "gamemanager.h"
#include "player.h"
#include "model.h"
#include "motion.h"

//==========================================
//  �}�N����`
//==========================================
#define SPEED (2.0f) //�ړ����x
#define DETECTION (10000.0f) //���G�͈�

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyApproach::CEnemyApproach()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyApproach::~CEnemyApproach()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyApproach::Init(void)
{
	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::ENEMY_APPROACH_LAYER);

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
void CEnemyApproach::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyApproach::Update(void)
{
	//�ړ�
	Move();
	AvertEnemy();
	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemyApproach::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  �ړ�����
//==========================================
void CEnemyApproach::Move(void)
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

	//�Z�o�����x�N�g������p�x���Z�o
	float rotVector = atan2f(-posTarget.x, -posTarget.z);

	//�Z�o�����p�x�������̕����ɂ���
	m_rot.y = rotVector;
}
