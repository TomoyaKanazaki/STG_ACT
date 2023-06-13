//==========================================
//
//  ���N���X(field.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "field.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
LPDIRECT3DTEXTURE9 CField::m_pTexture = NULL;

//==========================================
//  �R���X�g���N�^
//==========================================
CField::CField(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CField::~CField()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CField::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_FIELD);

	if (FAILED(CObject3D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CField::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CField::Update(void)
{
	//�X�V����
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CField::Draw()
{
	CObject3D::Draw();
}

//==========================================
//  �e�N�X�`���̓ǂݍ���
//==========================================
HRESULT CField::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Hokkaido.png", &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  �e�N�X�`���̔j��
//==========================================
void CField::UnLoad(void)
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
CField *CField::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CField *pField = NULL;

	//NULL�`�F�b�N
	if (pField == NULL)
	{
		//���������m��
		pField = new CField;
	}

	//������
	if (pField != NULL)
	{
		pField->Init(pos, size, rot);
	}

	//�e�N�X�`�������蓖�Ă�
	pField->BindTexture(m_pTexture);

	//�|�C���^��Ԃ�
	return pField;
}
