//==========================================
//
//  �G�t�F�N�g�N���X(effect.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture;
int CEffect::m_nNum;

//==========================================
//  �R���X�g���N�^
//==========================================
CEffect::CEffect()
{
	m_nLife = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEffect::~CEffect()
{
	
}

//==========================================
//  ����������
//==========================================
HRESULT CEffect::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//�^�C�v�̐ݒ�
	SetType(TYPE_EFFECT);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEffect::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEffect::Update(void)
{
	//���������炷
	m_nLife--;

	//�������Ȃ��Ȃ�����폜����
	if (m_nLife <= 0)
	{
		this->Release();
		return;
	}

	//�T�C�Y������������
	m_size.x -= m_vecDeffSize.x * m_fLifeRatio;
	m_size.y -= m_vecDeffSize.y * m_fLifeRatio;

	//�X�V
	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEffect::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�`��
	CObject2D::Draw();

	//�A���t�@�u�����f�B���O���̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
HRESULT CEffect::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/effect.jpg", &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  �e�N�X�`���̏I������
//==========================================
void CEffect::UnLoad(void)
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
CEffect *CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nLife)
{
	//�C���X�^���X����
	CEffect *pEffect = NULL;

	//NULL�`�F�b�N
	if (pEffect == NULL)
	{
		//���������m��
		pEffect = new CEffect;
	}

	//������
	if (pEffect != NULL)
	{
		pEffect->Init(pos, size, rot);
	}

	//�e�N�X�`�������蓖�Ă�
	pEffect->BindTexture(m_pTexture);

	//�f�t�H���g�T�C�Y��ۑ�����
	pEffect->m_vecDeffSize = size;

	//������ݒ肷��
	pEffect->m_nLife = nLife;
	pEffect->m_fLifeRatio = 1.0f / nLife;

	//�|�C���^��Ԃ�
	return pEffect;
}
