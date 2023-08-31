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
#include "texture.h"

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

	if (FAILED(CObject3D::Init()))
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
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CObject3D::Draw();

	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
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

	//�|�C���^��Ԃ�
	return pField;
}
