//==========================================
//
//  �w�i�N���X(bg.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bg.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  �}�N����`
//==========================================
#define SCROLL_ROUND (1000) //�X�N���[������x

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CBg::m_nNum = 0;
LPDIRECT3DTEXTURE9 CBg::m_pTexture[BG_NUM] = {};

//==========================================
//  �R���X�g���N�^
//==========================================
CBg::CBg()
{
	m_nID = m_nNum;
	m_nNum++;
	m_nSpeed = SCROLL_ROUND * m_nNum;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBg::~CBg()
{
	m_nNum--;
}

//==========================================
//  ����������
//==========================================
HRESULT CBg::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D_Anim::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//�A�j���[�V�������̓o�^
	SetAnim(m_nSpeed, 1, true, TYPE_V);

	//�^�C�v�̐ݒ�
	SetType(TYPE_BG);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CBg::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBg::Update(void)
{
	CObject2D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBg::Draw(void)
{
	CObject2D_Anim::Draw();
}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
HRESULT CBg::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/bg100.png", &m_pTexture[0])))
	{
		return E_FAIL;
	}
	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/bg101.png", &m_pTexture[1])))
	{
		return E_FAIL;
	}
	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/bg102.png", &m_pTexture[2])))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  �j������
//==========================================
void CBg::UnLoad(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < BG_NUM; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//==========================================
//  ��������
//==========================================
void CBg::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	for (int nCnt = 0; nCnt < BG_NUM; nCnt++)
	{
		//�C���X�^���X����
		CBg *pBg = NULL;

		//NULL�`�F�b�N
		if (pBg == NULL)
		{
			//���������m��
			pBg = new CBg;
		}

		//������
		if (pBg != NULL)
		{
			pBg->Init(pos, size, rot);
		}

		//�e�N�X�`�������蓖�Ă�
		pBg->BindTexture(m_pTexture[nCnt]);
	}
}
