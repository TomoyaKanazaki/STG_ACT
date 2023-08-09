//==========================================
//
//  �t���Ă���G�̃N���X(enemy_approach.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_approach.h"
#include "gamemanager.h"
#include "player.h"

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
}
