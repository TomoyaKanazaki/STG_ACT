//==========================================
//
//  �o���b�g�N���X(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "debugproc.h"
#include "texture.h"
#include "effect.h"
#include "collision.h"

//==========================================
//  �}�N����`
//==========================================
#define BULLET_SPEED (10.0f) //�e��
#define BULLET_LIFE (256) //����
#define HOMING_LENGTH (200.0f) //�z�[�~���O���苗��
#define HOMING_POWER (0.2f) //�z�[�~���O�̋���
#define HOMING_TIMER (30) //�z�[�~���O����
#define HIT_LENGTH (20.0f) //�q�b�g���苗��

//==========================================
//  �R���X�g���N�^
//==========================================
CBullet::CBullet()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = BULLET_LIFE;
	m_nHomingCounter = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBullet::~CBullet()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBullet::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//�^�C�v�̐ݒ�
	SetType(TYPE_BULLET);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CBullet::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBullet::Update(void)
{
	//�z�[�~���O�^�[�Q�b�g�̈ʒu��ۑ�����ϐ�
	D3DXVECTOR3 Target;

	//�z�[�~���O����
	if (Collision::CollisionEnemy(m_pos, HOMING_LENGTH, false, &Target))
	{
		if (m_nHomingCounter <= HOMING_TIMER)
		{
			//�z�[�~���O���[�u
			D3DXVECTOR3 move = Target - m_pos;

			//�ړ��ʂ̐��K��
			D3DXVec3Normalize(&move, &move);

			//�ړ��ʂ̓K��
			D3DXVECTOR3 moveDiff = m_move - move;
			m_move -= moveDiff * HOMING_POWER;

			//���Ԃ����Z����
			m_nHomingCounter++;
		}
	}

	//���ŏ���
	if (m_nLife <= 0 || Collision::CollisionEnemy(m_pos, HIT_LENGTH, true))
	{
		Uninit();
		return;
	}

	//���������炷
	m_nLife--;

	//�ړ��ʂ����Z����
	D3DXVec3Normalize(&m_move, &m_move);
	m_pos += m_move * BULLET_SPEED;

	//�G�t�F�N�g���Ă�
	CEffect::Create(m_pos, m_size, m_rot, D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f), 10);

	//�X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBullet::Draw(void)
{
	//�`��
	CObject3D::Draw();
}

//==========================================
//  ��������
//==========================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	//�C���X�^���X����
	CBullet *pBullet = NULL;

	//NULL�`�F�b�N
	if (pBullet == NULL)
	{
		//���������m��
		pBullet = new CBullet;
	}

	if (pBullet == NULL)
	{
		return NULL;
	}

	//�l��ݒ�
	pBullet->m_pos = pos;
	pBullet->m_size = size;
	pBullet->m_move = move;
	pBullet->m_move.x = move.x * BULLET_SPEED;
	pBullet->m_move.z = move.z * BULLET_SPEED;
	pBullet->m_rot.x = D3DX_PI * 0.5f;

	//������
	pBullet->Init();

	//�e�N�X�`�������蓖�Ă�
	pBullet->BindTexture(CManager::GetTexture()->GetAddress(4));

	//�|�C���^��Ԃ�
	return pBullet;
}
