//==========================================
//
//  �A�j���[�V�����I�u�W�F�N�g2D(object2D_anim.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object2D_anim.h"
#include "manager.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  �}�N����`
//==========================================
#define ANIM_UPDATE (5) //�p�^�[���X�V�t���[��

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
LPDIRECT3DTEXTURE9 CObject2D_Anim::m_pTexture = NULL;

//==========================================
//  �R���X�g���N�^
//==========================================
CObject2D_Anim::CObject2D_Anim()
{
	m_nNumPattern = 0;
	m_nCountAnim = 0;
	m_nPatternAnim = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CObject2D_Anim::~CObject2D_Anim()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CObject2D_Anim::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, const int nAnimPattern)
{
	if (FAILED(CObject2D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//�A�j���[�V�����p�^�[����ݒ�
	m_nNumPattern = nAnimPattern;

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	this->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * m_nPatternAnim, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * (m_nPatternAnim + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * m_nPatternAnim, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * (m_nPatternAnim + 1), 1.0f);

	//���_�o�b�t�@���A�����b�N
	this->GetBuff()->Unlock();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CObject2D_Anim::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CObject2D_Anim::Update(void)
{
	//�J�E���g�����Z
	m_nCountAnim++;

	if (m_nCountAnim % ANIM_UPDATE == 0)
	{
		//�e�N�X�`�����W�̐؂�ւ�
		m_nPatternAnim++;
	
		//�p�^�[���̐؂�ւ�
		m_nPatternAnim %= m_nNumPattern;
	
		//���_�o�b�t�@�̌Ăяo��
		VERTEX_2D *pVtx;
	
		//���_�o�b�t�@�����b�N
		this->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);
	
		//�e�N�X�`�����W�̍X�V
		pVtx[0].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * m_nPatternAnim, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * (m_nPatternAnim + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * m_nPatternAnim, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * (m_nPatternAnim + 1), 1.0f);
	
		//���_�o�b�t�@���A�����b�N
		this->GetBuff()->Unlock();
	}
}

//==========================================
//  �`�揈��
//==========================================
void CObject2D_Anim::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  �e�N�X�`���̓ǂݍ���
//==========================================
HRESULT CObject2D_Anim::Load(void)
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
void CObject2D_Anim::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==========================================
//  ��������
//==========================================
CObject2D_Anim * CObject2D_Anim::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const int nAnimPattern, const D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CObject2D_Anim *pObject2D_Anim = NULL;

	//NULL�`�F�b�N
	if (pObject2D_Anim == NULL)
	{
		//���������m��
		pObject2D_Anim = new CObject2D_Anim;
	}

	//������
	if (pObject2D_Anim != NULL)
	{
		pObject2D_Anim->Init(pos, size, rot, nAnimPattern);
	}

	//�e�N�X�`�������蓖�Ă�
	pObject2D_Anim->BindTexture(m_pTexture);

	//�|�C���^��Ԃ�
	return pObject2D_Anim;
}
