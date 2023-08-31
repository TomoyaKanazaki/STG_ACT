//==========================================
//
//  �V���h�[�N���X(shadow.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object_fan.h"
#include "gamemanager.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CShadow::CShadow(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CShadow::~CShadow()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CShadow::Init(void)
{
	//������
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//�^�C�v�̐ݒ�
	SetType(TYPE_SHADOW);

	//���ɓ\��t����
	m_pos.y = 0.01f;

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CShadow::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CShadow::Update(void)
{
	m_pos.y = CGameManager::GetFan()->GetPos().y + 0.5f;

	//�X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CShadow::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�`��
	CObject3D::Draw();

	//�A���t�@�u�����f�B���O�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CShadow *CShadow::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CShadow *pShadow = NULL;

	//NULL�`�F�b�N
	if (pShadow == NULL)
	{
		//���������m��
		pShadow = new CShadow;
	}

	if (pShadow == NULL)
	{
		return NULL;
	}

	//�l��ݒ�
	pShadow->m_pos = pos;
	pShadow->m_size = size;
	pShadow->m_rot = rot;

	//������
	pShadow->Init();

	//�e�N�X�`�������蓖�Ă�
	pShadow->BindTexture(CManager::GetTexture()->GetAddress(CTexture::EFFECT));

	//�|�C���^��Ԃ�
	return pShadow;
}

//==========================================
//  ���̐ݒ菈��
//==========================================
void CShadow::SetTransform(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos.x = pos.x;
	m_pos.z = pos.z;
	m_rot = rot;
}
