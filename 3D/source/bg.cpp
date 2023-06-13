//==========================================
//
//  �w�i�N���X(bg.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bg.h"
#include "object2D_Anim.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  �}�N����`
//==========================================
#define SCROLL_ROUND (1000) //�X�N���[������x

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};

//==========================================
//  �R���X�g���N�^
//==========================================
CBg::CBg(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apObject[nCnt] = NULL;
	}
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBg::~CBg()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBg::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�I�u�W�F�N�g����
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//NULL�`�F�b�N
		if (m_apObject[nCnt] == NULL)
		{
			if (FAILED(m_apObject[nCnt] = CObject2D_Anim::Create(pos, size, rot, SCROLL_ROUND * nCnt, 1, true, CObject2D_Anim::TYPE_V)))
			{
				return E_FAIL;
			}
		}

		if (m_apObject[nCnt] != NULL)
		{
			//�e�N�X�`���̐ݒ�
			m_apObject[nCnt]->BindTexture(m_apTexture[nCnt]);

			//�^�C�v�̐ݒ�
			m_apObject[nCnt]->SetType(CObject::TYPE_BG);
		}
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CBg::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			m_apObject[nCnt]->Uninit();
			m_apObject[nCnt] = NULL;
		}
	}
}

//==========================================
//  �X�V����
//==========================================
void CBg::Update(void)
{

}

//==========================================
//  �`�揈��
//==========================================
void CBg::Draw(void)
{

}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
HRESULT CBg::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg100.png", &m_apTexture[0])))
	{
		return E_FAIL;
	}
	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTexture[1])))
	{
		return E_FAIL;
	}
	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &m_apTexture[2])))
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
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//==========================================
//  ��������
//==========================================
CBg *CBg::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
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

	return pBg;
}
