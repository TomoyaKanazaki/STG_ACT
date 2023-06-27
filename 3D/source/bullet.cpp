//==========================================
//
//  �o���b�g�N���X(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �}�N����`
//==========================================
#define BULLET_SPEED (20.0f) //�e��

//==========================================
//  �R���X�g���N�^
//==========================================
CBullet::CBullet()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
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
	//���������炷
	m_nLife--;

	//�������Ȃ��Ȃ�����폜����
	if (m_nLife <= 0)
	{
		this->Release();
		return;
	}

	//�ړ��ʂ����Z����
	m_pos += m_move;

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
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nLife)
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
	pBullet->m_nLife = nLife;
	pBullet->m_rot.x = D3DX_PI * 0.5f;

	//������
	pBullet->Init();

	//�e�N�X�`�������蓖�Ă�
	pBullet->BindTexture(CManager::GetTexture()->GetAddress(4));

	//�|�C���^��Ԃ�
	return pBullet;
}
