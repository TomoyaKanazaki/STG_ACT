//==========================================
//
//  �o���b�g�N���X(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "texture.h"
#include "effect.h"
#include "collision.h"
#include "object.h"
#include "bullet_normal.h"
#include "bullet_homing.h"

//==========================================
//  �}�N����`
//==========================================
#define BULLET_SPEED (10.0f) //�e��
#define BULLET_LIFE (256) //����
#define HIT_LENGTH (20.0f) //�q�b�g���苗��

//==========================================
//  �R���X�g���N�^
//==========================================
CBullet::CBullet(int nPriority) : CObject3D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = BULLET_LIFE;
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
	//���ŏ���
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	//�G�Ƃ̐ڐG
	if (m_user == CBullet::PLAYER)
	{
		if (Collision::CollisionEnemy(m_pos, HIT_LENGTH, true))
		{
			Uninit();
			return;
		}
	}

	//���������炷
	m_nLife--;

	//�ړ��ʂ����Z����
	D3DXVec3Normalize(&m_move, &m_move);
	m_pos += m_move * BULLET_SPEED;

	//�G�t�F�N�g���Ă�
	CEffect::Create(m_pos, m_size, D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f), 10);

	//�X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBullet::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�`��
	CObject3D::Draw();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, USER user, TYPE type)
{
	//�C���X�^���X����
	CBullet *pBullet = NULL;

	//NULL�`�F�b�N
	if (pBullet == NULL)
	{
		//���������m��
		switch (type)
		{
		case NORMAL_BULLET:

			pBullet = new CBulletNormal;
			break;

		case HOMING_BULLET:

			pBullet = new CBulletHoming;
			break;

		default:
			break;
		}
	}

	if (pBullet == NULL)
	{
		return NULL;
	}

	//�l��ݒ�
	pBullet->m_user = user;
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
