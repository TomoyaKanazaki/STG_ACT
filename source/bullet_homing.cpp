//==========================================
//
//  �ǔ��e�̃N���X(bullet_homing.cpp)
//  Author :Tomoya Kanazaki
//
//==========================================
#include "bullet_homing.h"
#include "collision.h"

//==========================================
//  �}�N����`
//==========================================
#define HOMING_LENGTH (200.0f) //�z�[�~���O���苗��
#define HOMING_POWER (0.3f) //�z�[�~���O�̋���
#define HOMING_TIMER (30) //�z�[�~���O����

//==========================================
//  �R���X�g���N�^
//==========================================
CBulletHoming::CBulletHoming()
{
	m_Target.pObj = NULL;
	m_Target.nCounter = 0;
	m_Target.bHoming = false;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBulletHoming::~CBulletHoming()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBulletHoming::Init(void)
{
	CBullet::Init();
	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CBulletHoming::Uninit(void)
{
	CBullet::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBulletHoming::Update(void)
{
	Follow();
	CBullet::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBulletHoming::Draw(void)
{
	CBullet::Draw();
}

//==========================================
//  �ǔ�����
//==========================================
void CBulletHoming::Follow(void)
{
	if (m_Target.bHoming)
	{
		if (m_Target.nCounter <= HOMING_TIMER)
		{
			if
				(
					m_Target.pObj->GetPos().x > -500.0f &&
					m_Target.pObj->GetPos().x < 500.0f &&
					m_Target.pObj->GetPos().z > -500.0f &&
					m_Target.pObj->GetPos().z < 500.0f
					)
			{
				//�z�[�~���O���[�u
				D3DXVECTOR3 move = m_Target.pObj->GetPos() - m_pos;
				move.y = 0.0f;

				//�ړ��ʂ̐��K��
				D3DXVec3Normalize(&move, &move);

				//�ړ��ʂ̓K��
				D3DXVECTOR3 moveDiff = m_move - move;

				//��莞�Ԍo�߂��Ă����璼������
				if (m_Target.nCounter > 20)
				{
					m_move -= moveDiff;
				}
				else
				{
					m_move -= moveDiff * HOMING_POWER;
				}

				//���Ԃ����Z����
				m_Target.nCounter++;
			}
			else
			{
				m_Target.bHoming = false;
			}
		}
	}
	else if (Collision::HomingEnemy(m_pos, HOMING_LENGTH, false, &m_Target.pObj) && m_Target.bHoming == false)
	{
		//�z�[�~���O���[�u
		D3DXVECTOR3 move = m_Target.pObj->GetPos() - m_pos;
		move.y = 0.0f;

		//�ړ��ʂ̐��K��
		D3DXVec3Normalize(&move, &move);

		//�ړ��ʂ̓K��
		D3DXVECTOR3 moveDiff = m_move - move;
		m_move -= moveDiff * HOMING_POWER;

		//�z�[�~���O���Ԃ̃��Z�b�g
		m_Target.nCounter = 0;

		//�z�[�~���O�σt���O�𗧂Ă�
		m_Target.bHoming = true;
	}
}
