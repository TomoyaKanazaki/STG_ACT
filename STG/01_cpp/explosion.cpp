//==========================================
//
//  �����N���X(explosion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "explosion.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  �}�N����`
//==========================================
#define UPDATECOUNT (5) //�X�V�Ԋu
#define ANIM_PATTERN (8) //�A�j���[�V�����p�^�[����

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//==========================================
//  �R���X�g���N�^
//==========================================
CExplosion::CExplosion()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CExplosion::~CExplosion()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CExplosion::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D_Anim::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//�A�j���[�V�������̓o�^
	SetAnim(ANIM_PATTERN, UPDATECOUNT, false, TYPE_U);

	//�^�C�v�̐ݒ�
	SetType(TYPE_EXPLOSION);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CExplosion::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CExplosion::Update(void)
{
	CObject2D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CExplosion::Draw(void)
{
	CObject2D_Anim::Draw();
}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
HRESULT CExplosion::Load(void)
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
//  �j������
//==========================================
void CExplosion::UnLoad(void)
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
CExplosion *CExplosion::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CExplosion *pExplosion = NULL;

	//NULL�`�F�b�N
	if (pExplosion == NULL)
	{
		//���������m��
		pExplosion = new CExplosion;
	}

	//������
	if (pExplosion != NULL)
	{
		pExplosion->Init(pos, size, rot);
	}

	//�e�N�X�`�������蓖�Ă�
	pExplosion->BindTexture(m_pTexture);

	//�|�C���^��Ԃ�
	return pExplosion;
}
