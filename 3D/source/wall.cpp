//==========================================
//
//  ���N���X(field.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "wall.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CWall::CWall(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CWall::~CWall()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CWall::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_WALL);

	if (FAILED(CObject3D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CWall::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CWall::Update(void)
{
	//�X�V����
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CWall::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	CObject3D::Draw();

	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//==========================================
//  �I�u�W�F�N�g��������
//==========================================
CWall *CWall::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CWall *pField = NULL;

	//NULL�`�F�b�N
	if (pField == NULL)
	{
		//���������m��
		pField = new CWall;
	}

	//������
	if (pField != NULL)
	{
		pField->Init(pos, size, rot);
	}

	//�e�N�X�`�������蓖�Ă�
	//pField->BindTexture(CManager::GetTexture()->GetAddress(0));

	//�|�C���^��Ԃ�
	return pField;
}
