//==========================================
//
//  �e�N���X(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "object2D_anim.h"
#include "debugproc.h"

//==========================================
//  �}�N����`
//==========================================
#define BULLET_SPEED (5.0f) //�e�̑��x
#define BULLET_LIFE (120) //�e�̎���

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;
int CBullet::m_nNum = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CBullet::CBullet()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpeed = BULLET_SPEED;
	m_nLife = BULLET_LIFE;
	m_nNum++;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBullet::~CBullet()
{
	m_nNum--;
}

//==========================================
//  ����������
//==========================================
HRESULT CBullet::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	m_move.x = -sinf(m_rot.z) * BULLET_SPEED;
	m_move.y = -cosf(m_rot.z) * BULLET_SPEED;

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CBullet::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBullet::Update(void)
{
	//���������炷
	m_nLife--;

	//�ړ�
	m_pos += m_move;

	//��]
	m_rot.z += 0.3f;

	//��]�p�x�̕␳
	if (m_rot.z > D3DX_PI || m_rot.z < -D3DX_PI)
	{
		if (m_rot.z > D3DX_PI)
		{
			m_rot.z += (-D3DX_PI * 2);
		}
		else if (m_rot.z < -D3DX_PI)
		{
			m_rot.z += (D3DX_PI * 2);
		}
	}

	//�X�V����
	CObject2D::Update();

	//�ړ�����
	if (
		m_pos.x - (m_size.x * 0.5f) > SCREEN_WIDTH ||
		m_pos.x + (m_size.x * 0.5f) < 0.0f ||
		m_pos.y - (m_size.y * 0.5f) > SCREEN_HEIGHT ||
		m_pos.y + (m_size.y * 0.5f) < 0.0f
		)
	{
		this->Release();
	}
	else if (m_nLife <= 0)
	{
		this->Release();
		CObject2D_Anim::Create(m_pos, D3DXVECTOR3(m_size.x * 1.5f, m_size.y * 1.5f, 0.0f), 8, m_rot);
	}
}

//==========================================
//  �`�揈��
//==========================================
void CBullet::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  �e�N�X�`���̓ǂݍ���
//==========================================
HRESULT CBullet::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/explosion.png", &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  �e�N�X�`���̔j��
//==========================================
void CBullet::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==========================================
//  �I�u�W�F�N�g��������
//==========================================
CBullet *CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CBullet *pPlayer = NULL;

	//NULL�`�F�b�N
	if (pPlayer == NULL)
	{
		//���������m��
		pPlayer = new CBullet;
	}

	//������
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, size, rot);
	}

	//�e�N�X�`�������蓖�Ă�
	pPlayer->BindTexture(m_pTexture);

	//�|�C���^��Ԃ�
	return pPlayer;
}
