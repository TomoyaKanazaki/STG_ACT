//==========================================
//
//  �e�N���X(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "explosion.h"

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
	m_nSpeed = BULLET_SPEED;
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

	//�^�C�v�̐ݒ�
	SetType(TYPE_BULLET);

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

	//���S����
	if (CollisionEnemy())
	{
		return;
	}
	else if (
		m_pos.x - (m_size.x * 0.5f) > SCREEN_WIDTH ||
		m_pos.x + (m_size.x * 0.5f) < 0.0f ||
		m_pos.y - (m_size.y * 0.5f) > SCREEN_HEIGHT ||
		m_pos.y + (m_size.y * 0.5f) < 0.0f
		)
	{
		this->Release();
		return;
	}
	else if (m_nLife <= 0)
	{
		CExplosion::Create(m_pos, m_size, m_rot);
		this->Release();
		return;
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
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/bullet.png", &m_pTexture)))
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
	CBullet *pBullet = NULL;

	//NULL�`�F�b�N
	if (pBullet == NULL)
	{
		//���������m��
		pBullet = new CBullet;
	}

	//������
	if (pBullet != NULL)
	{
		pBullet->Init(pos, size, rot);
	}

	//�e�N�X�`�������蓖�Ă�
	pBullet->BindTexture(m_pTexture);

	//�|�C���^��Ԃ�
	return pBullet;
}

//==========================================
//  �G�Ƃ̓����蔻��
//==========================================
bool CBullet::CollisionEnemy(void)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = GetObject(nCntObj);

		//NULL�`�F�b�N
		if (pObj == NULL)
		{
			continue;
		}

		if (pObj->GetType() != TYPE_ENEMY) //�G�̏ꍇ
		{
			continue;
		}

		//�G�̊e�����擾����
		D3DXVECTOR3 pos = pObj->GetPos();
		D3DXVECTOR3 size = pObj->GetSize();

		//�G�ƒe�̋������擾
		float fLength = (pos.x - m_pos.x) * (pos.x - m_pos.x) + (pos.y - m_pos.y) * (pos.y - m_pos.y);

		//���苗�����擾
		float fOutLine = (size.x - m_size.x * 0.3f) * (size.x - m_size.x * 0.3f) + (size.y - m_size.y * 0.3f) * (size.y - m_size.y * 0.3f);

		if (fLength < fOutLine)
		{
			CExplosion::Create(m_pos, m_size, m_rot);
			pObj->Uninit();
			this->Release();
			return true;
		}
	}

	//�������Ă��Ȃ�
	return false;
}
